#include "ItemSectionFormatter.h"

#include "../ReadContext.h"
#include "../WriteContext.h"
#include "../../file/FormattedReader.h"
#include "../../file/FormattedWriter.h"
#include "../../description/Field.h"
#include "../../description/ItemDescriptionInternals.h"
#include "../../description/TeaFileDescription.h"

namespace teatime {

void ItemSectionFormatter::Read(ReadContext *rc)
{
  auto r = rc->Reader();
  shared_ptr<ItemDescription> id(new ItemDescription()); // todo mark as source=file
  rc->Description()->Item(id);

  id->ItemSize(r->ReadInt32());
  id->ItemName(r->ReadText());

  int fieldCount = r->ReadInt32();
  while (fieldCount-- > 0)
  {
    shared_ptr<Field> f(new Field());
    f->Type(static_cast<FieldType>(r->ReadInt32()));
    f->Offset(r->ReadInt32());
    f->Name(r->ReadText());
    id->AddField(f);
  }
}

void ItemSectionFormatter::Write(WriteContext *wc)
{
  auto w = wc->Writer();
  auto id = wc->Description()->Item();

  w->WriteInt32(id->ItemSize());
  w->WriteText(id->ItemName());

  int n = id->FieldCount();
  w->WriteInt32(n);

  for (int i=0; i < n; i++)
  {
    auto f = id->GetField(i);
    w->WriteInt32(static_cast<int>(f->Type()));
    w->WriteInt32(f->Offset());
    w->WriteText(f->Name());
  }
}

} // namespace teatime
