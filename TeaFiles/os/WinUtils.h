#ifdef WIN32

#ifndef TEATIME_OS_WINUTILS
#define TEATIME_OS_WINUTILS

#include <windows.h>
#include <string>

namespace teatime {

using std::string;

class WinUtils
{
public:

  static string GetWindowsErrorMessage(unsigned messageid);
  static string GetWindowsErrorMessage();
};

class CheckException {
public:

  // constructs CheckException
  CheckException(const char *msg);
  void operator=(BOOL result);

private:

  const char *message;
};

} // namespace teatime

#endif // TEATIME_OS_WINUTILS

#endif // WIN32