#include "TextUtils.h"

#include "../base/Common.h"
#include "../base/Pointer.h"
#include "../base/Exceptions.h"

#ifdef WIN32
#include "windows.h"
#include "assert.h"
#else
// todo: #include <iconv.h>
// implement UTF8 <> locale conversion
#endif

namespace teatime {

string TextUtils::ConvertToUTF8(const string localText)
{
#ifdef WIN32
  unique_ptr<wchar_t[]> utf16(new wchar_t[localText.size()]);
  ::MultiByteToWideChar(CP_ACP, 0, localText.c_str(), (int)localText.size(), utf16.get(), (int)localText.size());
  
  int utf8BufferSize = (int)(localText.size() * 4); // each character occupies up to 4 bytes per character
  unique_ptr<char[]> utf8(new char[utf8BufferSize]);
  int n = ::WideCharToMultiByte(CP_UTF8, 0, utf16.get(), (int)localText.size(), utf8.get(), utf8BufferSize, 0, 0);
  if(n > 0)
  {      
    return string(utf8.get(), n);
  }
  if(n == 0 && GetLastError() != ERROR_INSUFFICIENT_BUFFER)
  {
    throw Exception(strerror(errno));
  }  
  throw Exception("utf8 conversion failed.");
#else
  // conversion tbd.
  // for now, users of this api have to restrict themselves to 7 bit ASCII in which case (ascii value == utf8 value)
  return localText;
#endif
}

string TextUtils::ConvertFromUTF8(const string utf8Text)
{
#if WIN32
  unique_ptr<wchar_t[]> utf16(new wchar_t[utf8Text.size()]);
  int n16 = ::MultiByteToWideChar(CP_UTF8, 0, utf8Text.c_str(), (int)utf8Text.size(), utf16.get(), (int)utf8Text.size());
  
  int ansiBufferSize = (int)utf8Text.size(); // ansi will be smaller than utf8
  unique_ptr<char[]> ansi(new char[ansiBufferSize]);
  int n = ::WideCharToMultiByte(CP_ACP, 0, utf16.get(), n16, ansi.get(), ansiBufferSize, 0, 0);
  if(n > 0)
  {      
    string s(ansi.get(), n);    
    return s;
  }
  if(n == 0 && GetLastError() != ERROR_INSUFFICIENT_BUFFER)
  {    
    throw Exception(strerror(errno));
  }  
  throw Exception("utf8 conversion failed.");
#else
  // conversion tbd.
  // for now, users of this api have to restrict themselves to 7 bit ASCII in which case (ascii value == utf8 value)
  return utf8Text;
#endif
}

} // namespace teatime
