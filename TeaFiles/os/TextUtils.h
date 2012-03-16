#ifndef TEATIME_TEXTUTILS
#define TEATIME_TEXTUTILS

#include <string>
using std::string;

namespace teatime {

// Converts a string between utf8 and the current locale.
class TextUtils
{
public:
  
  //  characters above 127 will be converted. For instance the € symbol convert into 3 bytes.
  static string ConvertToUTF8(const string text);
  
  //  Converts a UTF8 string into a string in the current locale. This reverses a ConvertToUTF8 operation.
  static string ConvertFromUTF8(const string text);
};

} // namespace teatime

#endif // TEATIME_TEXTUTILS
