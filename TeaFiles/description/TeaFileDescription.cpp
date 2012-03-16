#include "TeaFileDescription.h"

namespace teatime {

shared_ptr<ItemDescription> TeaFileDescription::Item() const
{
  return itemDescription_;
}

void TeaFileDescription::Item(shared_ptr<ItemDescription> id)
{
  this->itemDescription_ = id;
}

const string TeaFileDescription::Content() const
{
  return this->contentDescription_;
}

void TeaFileDescription::Content(string s)
{
  this->contentDescription_ = s;
}

shared_ptr<NameValueCollection> TeaFileDescription::NameValues() const
{
  return nameValues_;
}

void TeaFileDescription::NameValues(shared_ptr<NameValueCollection> nvc)
{
  nameValues_ = nvc;
}

TimeScale TeaFileDescription::Scale() const
{
  return timeScale_;
}

void TeaFileDescription::Scale(TimeScale scale)
{
  this->timeScale_ = scale;
}

} // namespace teatime
