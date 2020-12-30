// Implementation file for Unsorted.h

#include "unsorted.h"
#include <string>

UnsortedType::UnsortedType()
{
  length = 0;
}
bool UnsortedType::IsFull() const
{
  return (length == MAX_ITEMS);
}
int UnsortedType::GetLength() const
{
  return length;
}

ItemType UnsortedType::GetItem(ItemType item, bool& found) 
// Pre:  Key member(s) of item is initialized. 
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been returned;
//       otherwise, item is returned. 
{
  bool moreToSearch;
  int location = 0;
  found = false;

  moreToSearch = (location < length);

  while (moreToSearch && !found) 
  {
    switch (item.ComparedTo(infod[location]))
    {
      case LESS    : 
      case GREATER : location++;
                     moreToSearch = (location < length);
                     break;
      case EQUAL   : found = true;
                     item = infod[location];
                     break;
    }
  }
  return item;
}

void UnsortedType::GetPatient(ItemType itemP, bool& found)
// Pre:  Key member(s) of item is initialized. 
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been returned;
//       otherwise, item is returned. 
{
	bool moreToSearch;
	int location = 0;
	found = false;

	moreToSearch = (location < length);

	while (moreToSearch && !found)
	{
		switch (itemP.ComparedTo(infop[location]))
		{
		case LESS:
		case GREATER: location++;
			moreToSearch = (location < length);
			break;
		case EQUAL: found = true;
			itemP = infop[location];
			break;
		}
	}
}

void UnsortedType::GetDoctorByCode(ItemType& itemD, ItemType itemC, bool& found)
// Pre:  Key member(s) of item is initialized. 
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been returned;
//       otherwise, item is returned. 
{
	bool moreToSearch;
	int location = 0;
	found = false;

	moreToSearch = (location < length);

	while (moreToSearch && !found)
	{
		switch (itemC.ComparedTo(infoc[location]))
		{
		case LESS:
		case GREATER: location++;
			moreToSearch = (location < length);
			break;
		case EQUAL: found = true;
			itemC = infoc[location];
			itemD = infod[location];
			break;
		}
	}
}

void UnsortedType::GetDoctorByPatient(ItemType& itemD, ItemType itemP, bool& found)
// Pre:  Key member(s) of item is initialized. 
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been returned;
//       otherwise, item is returned. 
{
	bool moreToSearch;
	int location = 0;
	found = false;

	moreToSearch = (location < length);

	while (moreToSearch && !found)
	{
		switch (itemP.ComparedTo(infop[location]))
		{
		case LESS:
		case GREATER: location++;
			moreToSearch = (location < length);
			break;
		case EQUAL: found = true;
			itemP = infop[location];
			itemD = infod[location];
			break;
		}
	}
}

ItemType UnsortedType::GetItemCode(ItemType itemC, bool& found)
// Pre:  Key member(s) of item is initialized. 
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been returned;
//       otherwise, item is returned. 
{
	bool moreToSearch;
	int location = 0;
	found = false;

	moreToSearch = (location < length);

	while (moreToSearch && !found)
	{
		switch (itemC.ComparedTo(infoc[location]))
		{
		case LESS:
		case GREATER: location++;
			moreToSearch = (location < length);
			break;
		case EQUAL: found = true;
			itemC = infoc[location];
			break;
		}
	}
	return itemC;
}

bool UnsortedType::isAvailable(ItemType itemD, bool& found)
// Pre:  Key member(s) of item is initialized. 
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been returned;
//       otherwise, item is returned. 
{
	bool moreToSearch;
	int location = 0;
	found = false;
	ItemType itemP;
	std::string patient;

	moreToSearch = (location < length);

	while (moreToSearch && !found)
	{
		switch (itemD.ComparedTo(infod[location]))
		{
		case LESS:
		case GREATER: location++;
			moreToSearch = (location < length);
			break;
		case EQUAL: found = true;
			itemD = infod[location];
			itemP = infop[location];
			break;
		}
	}
	patient = itemP.PrintString();
	if (patient == "") {
		return true;
	}
	else {
		return false;
	}
}

void UnsortedType::GetDoctor(ItemType& itemD, ItemType& itemR, ItemType& itemC, ItemType itemP, bool& found)
// Pre:  Key member(s) of item is initialized. 
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been returned;
//       otherwise, item is returned. 
{
	bool moreToSearch;
	int location = 0;
	found = false;

	moreToSearch = (location < length);

	while (moreToSearch && !found)
	{
		switch (itemC.ComparedTo(infoc[location]))
		{
		case LESS:
		case GREATER: location++;
			moreToSearch = (location < length);
			break;
		case EQUAL: found = true;
			itemC = infoc[location];
			itemR = infor[location];
			itemD = infod[location];
			infop[location] = itemP;
			break;
		}
	}
	
}

void UnsortedType::GetDoctorInfo(ItemType& itemD, ItemType& itemR, ItemType& itemC, bool& found)
// Pre:  Key member(s) of item is initialized. 
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been returned;
//       otherwise, item is returned. 
{
	bool moreToSearch;
	int location = 0;
	found = false;

	moreToSearch = (location < length);

	while (moreToSearch && !found)
	{
		switch (itemC.ComparedTo(infoc[location]))
		{
		case LESS:
		case GREATER: location++;
			moreToSearch = (location < length);
			break;
		case EQUAL: found = true;
			itemC = infoc[location];
			itemR = infor[location];
			itemD = infod[location];
			break;
		}
	}

}

void UnsortedType::GetDoctorW(ItemType itemD, ItemType& itemR, ItemType& itemC, ItemType& itemP, bool& found)
// Pre:  Key member(s) of item is initialized. 
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been returned;
//       otherwise, item is returned. 
{
	bool moreToSearch;
	int location = 0;
	found = false;

	moreToSearch = (location < length);

	while (moreToSearch && !found)
	{
		switch (itemD.ComparedTo(infod[location]))
		{
		case LESS:
		case GREATER: location++;
			moreToSearch = (location < length);
			break;
		case EQUAL: found = true;
			itemC = infoc[location];
			itemR = infor[location];
			itemD = infod[location];
			itemP = infop[location];
			break;
		}
	}

}

void UnsortedType::ScheduleP(ItemType itemP, int i) {
	infop[i] = itemP;
}

ItemType UnsortedType::findP(ItemType itemP, int i) {
	
	itemP = infop[i];
	return itemP;
}

bool UnsortedType::findD(ItemType itemD, int i) {

	std::string temp;
	std::string item;
	ItemType infoD;

	infoD = infod[i];
	temp = infoD.PrintString();
	item = itemD.PrintString();

	if (temp == item) {
		return true;
	}
	else {
		return false;
	}
}

void UnsortedType::GetDoctorD(ItemType& itemD, ItemType& itemR, ItemType& itemC, ItemType itemP, bool& found)
// Pre:  Key member(s) of item is initialized. 
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been returned;
//       otherwise, item is returned. 
{
	bool moreToSearch;
	int location = 0;
	found = false;

	moreToSearch = (location < length);

	while (moreToSearch && !found)
	{
		switch (itemD.ComparedTo(infod[location]))
		{
		case LESS:
		case GREATER: location++;
			moreToSearch = (location < length);
			break;
		case EQUAL: found = true;
			itemC = infoc[location];
			itemR = infor[location];
			itemD = infod[location];
			infop[location] = itemP;
			break;
		}
	}

}

void UnsortedType::MakeEmpty()
// Post: list is empty.
{
  length = 0;
}
void UnsortedType::PutItem(ItemType item)
// Post: item is in the list.
{
  infod[length] = item;
  length++;
}

void UnsortedType::PutItemAll(ItemType itemD, ItemType itemR, ItemType itemC, ItemType itemP)
// Post: all items are in the list.
{
	infod[length] = itemD;
	infor[length] = itemR;
	infoc[length] = itemC;
	infop[length] = itemP;
	length++;
}

void UnsortedType::DeleteItem(ItemType item)
// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
{
  int location = 0;

  while (item.ComparedTo(infod[location]) != EQUAL)
    location++;

  infod[location] = infod[length - 1];
  length--;
}

void UnsortedType::DeletePatient(ItemType itemP, bool& found)
// Pre:  Key member(s) of item is initialized. 
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been returned;
//       otherwise, item is returned. 
{
	bool moreToSearch;
	int location = 0;
	found = false;
	std::string item;

	moreToSearch = (location < length);

	while (moreToSearch && !found)
	{
		switch (itemP.ComparedTo(infop[location]))
		{
		case LESS:
		case GREATER: location++;
			moreToSearch = (location < length);
			break;
		case EQUAL: found = true;
			item == "";
			itemP.Initialize(item);
			infop[location] = itemP;
			break;
		}
	}
}

void UnsortedType::DeleteWL(ItemType itemD, ItemType itemR, ItemType itemC, ItemType itemP)
// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
{
	std::string empty = "";
	int location = 0;

	while (itemP.ComparedTo(infop[location]) != EQUAL)
		location++;

	itemD.Initialize(empty);
	infod[location] = itemD;


	itemR.Initialize(empty);
	infor[location] = itemR;


	itemC.Initialize(empty);
	infoc[location] = itemC;


	itemP.Initialize(empty);
	infop[location] = itemP;

}

void UnsortedType::ResetList()
// Post: currentPos has been initialized.
{
  currentPos = -1;
}

ItemType UnsortedType::GetNextItem()
// Pre:  ResetList was called to initialized iteration.
//       No transformer has been executed since last call.
//       currentPos is defined.
// Post: item is current item.
//       Current position has been updated.
{
  currentPos++;
  return infod[currentPos];
}

