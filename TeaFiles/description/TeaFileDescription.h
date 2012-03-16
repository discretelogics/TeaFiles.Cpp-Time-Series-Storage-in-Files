#ifndef TEATIME_TEAFILE_DESCRIPTION_TEAFILEDESCRIPTION
#define TEATIME_TEAFILE_DESCRIPTION_TEAFILEDESCRIPTION

#include "../base/Common.h"
#include "../base/Pointer.h"
#include "../time/TimeScale.h"
#include <string>
using std::string;

namespace teatime {

class ItemDescription;
class NameValueCollection;
class TimeScale;

/// <summary>
/// A TeaFile holds a description about the type of Items stored in it and about the content that these items hold. All these descriptions are held 
/// in a <see cref="TeaFileDescription"/>.
/// </summary>
class TeaFileDescription
{
public:

  TeaFileDescription() {}

  // item description
  shared_ptr<ItemDescription> Item() const;
	void Item(shared_ptr<ItemDescription>);

  // content description
  const string Content() const;
  void Content(string);

  // name values
  shared_ptr<NameValueCollection> NameValues() const;
  void NameValues(shared_ptr<NameValueCollection>);

  // time scale. to avoid name collision with the class name, we use Scale instead of TimeScale
  TimeScale Scale() const;
  void Scale(TimeScale);

  /// <summary>
  /// Opens a TeaFile, reads its description and closes it. Requires the file ot be read,
  /// so if the file is opened by someone else and sharing for reading was not permitted,
  /// this method will fail.
  /// </summary>
  /// <param name="fileName"></param>
  /// <returns></returns>
  static TeaFileDescription *FromFile(string fileName);

private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(TeaFileDescription);

  shared_ptr<ItemDescription> itemDescription_;
  shared_ptr<NameValueCollection> nameValues_;
  string contentDescription_;
  TimeScale timeScale_;
};

} // namespace teatime

#endif // TEATIME_TEAFILE_DESCRIPTION_TEAFILEDESCRIPTION
