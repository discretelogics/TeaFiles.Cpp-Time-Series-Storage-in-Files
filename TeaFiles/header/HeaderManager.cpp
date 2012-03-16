#include "HeaderManager.h"

#include "ReadContext.h"
#include "WriteContext.h"
#include "sections/ItemSectionFormatter.h"
#include "sections/ContentSectionFormatter.h"
#include "sections/NameValueSectionFormatter.h"
#include "sections/TimeSectionFormatter.h"

#include "../description/ItemDescription.h"
#include "../description/TeaFileDescription.h"
#include "../file/FormattedReader.h"
#include "../file/FormattedWriter.h"
#include "../file/Streams.h"
#include "../base/Exceptions.h"
#include "../base/NameValue.h"

namespace teatime {

HeaderManager::HeaderManager()
{
  this->formatters_.emplace_back(new ItemSectionFormatter());
  this->formatters_.emplace_back(new ContentSectionFormatter());
  this->formatters_.emplace_back(new NameValueSectionFormatter());
  this->formatters_.emplace_back(new TimeSectionFormatter());
}

SectionFormatter *HeaderManager::GetFormatter(int sectionId)
{
  static ItemSectionFormatter isf;
  static ContentSectionFormatter csf;
  static NameValueSectionFormatter nvsf;
  static TimeSectionFormatter tsf;

  if(sectionId == isf.Id()) return &isf;
  if(sectionId == csf.Id()) return &csf;
  if(sectionId == nvsf.Id()) return &nvsf;
  if(sectionId == tsf.Id()) return &tsf;

  return 0;
}

shared_ptr<ReadContext> HeaderManager::ReadHeader(FormattedReader *r)
{
  shared_ptr<ReadContext> rc(new ReadContext(r));
  try
  {
    int64 bom = r->ReadInt64();
    if (bom != 0x0d0e0a0402080500) throw new FileFormatException("Expected Signature not found. Either this file is not a TeaFile or the byte order (endianness) differs between the machine were the file was written and the local machine.");
    rc->ItemAreaStart(r->ReadInt64());
    rc->ItemAreaEnd(r->ReadInt64());
    rc->SectionCount(r->ReadInt64());

    // read sections
    for (int i = 0; i < rc->SectionCount(); i++)
    {
      int sectionId = r->ReadInt32();
      int nextSectionOffset = r->ReadInt32();
      int nextSectionStart = (int) r->Position() + nextSectionOffset;
      if (nextSectionStart > rc->ItemAreaStart()) throw new FileFormatException("NextSectionOffset of section number {0} is wrong: Next Section Start would be beyond ItemStart.");

      SectionFormatter *sectionFormatter = this->GetFormatter(sectionId);
      if (sectionFormatter != 0)
      {
        sectionFormatter->Read(rc.get());
        if (r->Position() > nextSectionStart) throw new FileFormatException("Section read too many bytes from the stream. SectionId:{0} SectionName:{1}"); //.Formatted(sectionId, sectionFormatter->GetType().Name.Replace("Formatter", "")));
      }

      int bytesToSkip = nextSectionStart - (int) r->Position();
      if (bytesToSkip < 0) throw new FileFormatException("Reading sections from the file header failed. Section with id {0} reads more bytes than reserved for that section"); // .Formatted(sectionId));
      r->SkipBytes(bytesToSkip);
    }

    // skip forward to begin of item area
    if (r->Position() > rc->ItemAreaStart()) throw FileFormatException("Stream position is behind start of item area.");
    r->SkipBytes(static_cast<int>(rc->ItemAreaStart() - r->Position()));
    if (rc->ItemAreaStart() != r->Position()) throw new FileFormatException("Stream Position could not be set to start of item area.");

    return rc;
  }
  catch(FileFormatException)
  {
    throw;
  }
}

void HeaderManager::WriteHeader(FormattedWriter* w, const TeaFileDescription* const description)
{
  WriteContext wc(w, description);
  string sectionBytes = CreateSections(&wc);

  w->WriteInt64(0x0d0e0a0402080500);
  w->WriteInt64(wc.ItemAreaStart());
  w->WriteInt64(0);
  w->WriteInt64(wc.SectionCount());
  w->WriteRaw((byte*)sectionBytes.c_str(), static_cast<int32>(sectionBytes.size()));
}

string HeaderManager::CreateSections(WriteContext* wc)
{  
  if(wc->Description() == 0) return "";

  FormattedWriter *saved = wc->Writer();

  MemoryStream allSectionsStream;
  FormattedWriter allSectionsWriter(&allSectionsStream);

  int pos = 32; // sections start at byte position 32
  for(auto it = this->formatters_.begin(); it != this->formatters_.end(); ++it)
  {
    SectionFormatter *formatter = it->get();

    MemoryStream sectionStream;
    FormattedWriter sectionWriter(&sectionStream);

    wc->Writer(&sectionWriter);
    formatter->Write(wc);
    int size = (int)sectionStream.Size();
    if (size > 0)
    {
      // section id
      allSectionsWriter.WriteInt32(formatter->Id());
      pos += 4;

      // nextSectionOffset
      allSectionsWriter.WriteInt32(size);
      pos += 4;

      // section payload
      string sectionBytes = sectionStream.ToString();
      allSectionsWriter.WriteRaw((byte*)sectionBytes.c_str(), size);
      pos += size; // no padding or spacing done between sections

      wc->IncrementSectionCount();
    }
  }

  // padding
  int paddingBytes = (8 - pos % 8);
  if (paddingBytes == 8) paddingBytes = 0;
  allSectionsWriter.WriteZeroBytes(paddingBytes);
  wc->ItemAreaStart(pos + paddingBytes); // first item starts padded on 8 byte boundary. no spacing here

  wc->Writer(saved);
  return allSectionsStream.ToString();
}

// singleton
HeaderManager &HeaderManager::Instance()
{
  static HeaderManager instance;
  return instance;
}

} // namespace teatime
