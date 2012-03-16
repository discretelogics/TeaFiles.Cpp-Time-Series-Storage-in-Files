#include "MemoryAccess.h"

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
using namespace boost::interprocess;

namespace teatime {

class FileMappingRaw::State
{
public:  
  State(const char* filename, int64 itemAreaStart, int64 itemAreaSize) : 
    mapping_(filename, read_only),
    region_(mapping_, read_only, itemAreaStart, (size_t)itemAreaSize) {}
  
  file_mapping  mapping_;
  mapped_region region_;
};

FileMappingRaw::FileMappingRaw(const char* filename, int64 itemAreaStart, int64 itemAreaSize) :
  state_(new State(filename, itemAreaStart, itemAreaSize))
{
  this->begin_ = (byte*)this->state_->region_.get_address();
  this->end_ = this->begin_ + this->state_->region_.get_size();
}

FileMappingRaw::~FileMappingRaw()
{  
  delete(this->state_);
}

} // namespace teatime
