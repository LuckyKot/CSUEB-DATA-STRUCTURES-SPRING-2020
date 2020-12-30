// The following declarations and definitions go into file 
// ItemType.h. 

#include <fstream>
#include <string>
const int MAX_ITEMS = 20;
enum RelationType  {LESS, GREATER, EQUAL};

class ItemType 
{ 
public:
  ItemType();
  RelationType ComparedTo(ItemType) const;
  void Print(std::ostream&) const;
  void Initialize(std::string item);
  std::string PrintString();
private:
  std::string value;
};
 
