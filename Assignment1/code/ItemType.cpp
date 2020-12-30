// The following definitions go into file ItemType.cpp. 
#include <fstream>
#include <iostream>
#include <string>
#include "ItemType.h"

ItemType::ItemType()
{}

RelationType ItemType::ComparedTo(ItemType otherItem) const 
{
  if (value < otherItem.value)
    return LESS;
  else if (value > otherItem.value)
    return GREATER;
  else return EQUAL;
}

void ItemType::Initialize(std::string item) 
{
  value = item;
}

void ItemType::Print(std::ostream& out) const 
// pre:  out has been opened.
// post: value has been sent to the stream out.
{
  out << value;
}

std::string ItemType::PrintString()
// pre:  out has been opened.
// post: converts itemType to string.
{
	return value;
}
