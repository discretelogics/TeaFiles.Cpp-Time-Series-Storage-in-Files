#include "Exceptions.h"

#include <sstream>
using std::stringstream;

namespace teatime {

const char *ArgumentException::what() const throw()
{
  stringstream os;
  os << "Invalid argument: "
     << this->argumentName_ << " = " << argumentValue_;
  return os.str().c_str();     
}

} // namespace teatime
