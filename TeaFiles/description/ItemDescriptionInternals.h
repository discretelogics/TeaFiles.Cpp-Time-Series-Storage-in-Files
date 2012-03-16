#ifndef TEATIME_TEAFILE_DESCRIPTION_ITEMDESCRIPTIONINTERNALS
#define TEATIME_TEAFILE_DESCRIPTION_ITEMDESCRIPTIONINTERNALS

#include "ItemDescription.h"

#include <vector>
using std::vector;

namespace teatime {

class ItemDescription::State
{
public:
    
  vector<shared_ptr<Field>> fields_;
  string                    itemName_;
  int                       itemSize_;
};

} // namespace teatime

#endif // TEATIME_TEAFILE_DESCRIPTION_ITEMDESCRIPTIONINTERNALS
