#ifndef TEATIME_TEAFILES_EXCEPTIONS
#define TEATIME_TEAFILES_EXCEPTIONS

#include <exception>
using std::exception;
#include <string>
using std::string;

namespace teatime {

class ArgumentException : public exception
{
public:

  ArgumentException(const char *argumentName, const char *argumentValue=0) :
    argumentName_(argumentName),
    argumentValue_(argumentValue) {}
        
  virtual const char *what() const throw();

private:

  const char * argumentName_;
  const char * argumentValue_;
};

class Exception : public exception
{
public:
  Exception(string message) : message_(message) {}
  ~Exception() throw() {}
  virtual const char *what() const throw() { return this->message_.c_str(); }

private:
  string message_;
};

class OperationException : public Exception
{
public:
  OperationException(const char *message) : Exception(message) {}  
};

class EndOfFileException : public Exception
{
public:
  EndOfFileException() : Exception("End of file has been reached.") {}
};

class TimeScaleMismatchException : public Exception
{
public:
  TimeScaleMismatchException() : Exception("The file has a TimeScale that is different from the master time scale.") {}
};

class FileFormatException : public OperationException
{
public:
  FileFormatException(const char *message) : OperationException(message) {}
  FileFormatException(const std::string message) : OperationException(message.c_str()) {}
};

} // namespace teatime

#endif // TEATIME_TEAFILES_EXCEPTIONS
