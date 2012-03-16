#ifdef WIN32

#include "WinUtils.h"
#include "../base/Exceptions.h"

#include <sstream>
using std::stringstream;

namespace teatime {

string WinUtils::GetWindowsErrorMessage(unsigned messageid)
{
  char* buffer = 0;
  DWORD result = FormatMessage(
    FORMAT_MESSAGE_ALLOCATE_BUFFER |
    FORMAT_MESSAGE_FROM_SYSTEM |
    FORMAT_MESSAGE_IGNORE_INSERTS,
    0,
    messageid,
    0,
    reinterpret_cast<char*>(&buffer),
    0,
    NULL);
  if (result > 0) // If FormatMessage fails, the return value is zero. otherwise it is the number of TCHARs stored in buffer
  {
    string message(buffer);
    LocalFree(reinterpret_cast<HLOCAL>(buffer));
    return message;
  }
  else
  {
    stringstream os;
    os << "Windows Error Code = " << messageid;
    return os.str();
  }
}

string WinUtils::GetWindowsErrorMessage()
{
  return GetWindowsErrorMessage(GetLastError());
}

CheckException::CheckException(const char *message)
{
  this->message = message;
}

void CheckException::operator=(BOOL result)
{
  if(result != TRUE)
  {
    string message(this->message);
    message += ":" + WinUtils::GetWindowsErrorMessage();
    throw Exception(message);
  }
}

} // namespace teatime

#endif