// Implementation file for Unsorted.h

#include "unsorted.h"

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

void UnsortedType::GetSchedule(ItemType& magician, ItemType& holiday, ItemType& customer, bool& found)
// Pre:  Key member(s) of item is initialized. 
// Post: Acts mostly on magician variable.
// if it's present on the schedule list - fills in the rest
{
	bool moreToSearch;
	int location = 0;
	found = false;

	moreToSearch = (location < length);

	while (moreToSearch && !found)
	{
		switch (magician.ComparedTo(infom[location]))
		{
		case LESS:
		case GREATER: location++;
			moreToSearch = (location < length);
			break;
		case EQUAL: found = true;
			magician = infom[location];
			holiday = infoh[location];
			customer = infoc[location];
			break;
		}
	}
}

void UnsortedType::GetScheduleH(ItemType& magician, ItemType& holiday, ItemType& customer, bool& found)
// Pre:  Key member(s) of item is initialized. 
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been returned;
//       like GetSchedule but works on holiday variable
//       H on the end stands for Holidays, made for convenience
{
	bool moreToSearch;
	int location = 0;
	found = false;

	moreToSearch = (location < length);

	while (moreToSearch && !found)
	{
		switch (holiday.ComparedTo(infoh[location]))
		{
		case LESS:
		case GREATER: location++;
			moreToSearch = (location < length);
			break;
		case EQUAL: found = true;
			magician = infom[location];
			holiday = infoh[location];
			customer = infoc[location];
			break;
		}
	}
}

void UnsortedType::GetScheduleM(ItemType& magician, ItemType& holiday, int& i, bool& both)
// Pre:  Key member(s) of item is initialized. 
// Post: Primarily created to control overlaps
//		 Checks if magician is already signed up on certain holiday
//       Returns "both" variable and works on iterator from main
{
	int location = i;
	bool foundm = false;
	bool foundh = false;
	both = 0;

		switch (holiday.ComparedTo(infoh[location])){
		case LESS:
		case GREATER:
		foundh = false;
			break;
		case EQUAL: foundh = true;
			holiday = infoh[location];
			break;
		}

		switch (magician.ComparedTo(infom[location])){
			case LESS:
			case GREATER:
				foundm = false;
				break;
			case EQUAL: 
				foundm = true;
				magician = infom[location];
				break;
		}

	if (foundm == true && foundh == true) {
		both = true;
	}
}


ItemType UnsortedType::GetItemM(ItemType magician, bool& found)
// Pre:  Key member(s) of item is initialized. 
// Post: function to get ONLY magician and his location
//       return ItemType

{
	bool moreToSearch;
	int location = 0;
	found = false;

	moreToSearch = (location < length);

	while (moreToSearch && !found)
	{
		switch (magician.ComparedTo(infom[location]))
		{
		case LESS:
		case GREATER: location++;
			moreToSearch = (location < length);
			break;
		case EQUAL: found = true;
			magician = infom[location];
			break;
		}
	}
	return magician;
}

ItemType UnsortedType::GetItemH(ItemType holiday, bool& found)
// Pre:  Key member(s) of item is initialized. 
// Post: same as previous but for holidays 
 
{
	bool moreToSearch;
	int location = 0;
	found = false;

	moreToSearch = (location < length);

	while (moreToSearch && !found)
	{
		switch (holiday.ComparedTo(infoh[location]))
		{
		case LESS:
		case GREATER: location++;
			moreToSearch = (location < length);
			break;
		case EQUAL: found = true;
			holiday = infoh[location];
			break;
		}
	}
	return holiday;
}


void UnsortedType::MakeEmpty()
// Post: list is empty.
{
  length = 0;
}
void UnsortedType::ScheduleH(ItemType magician, ItemType holiday, ItemType customer)
// Post: all 3 items are in the list.
// Primarily made for "schedule" list.
{
	infom[length] = magician;
	infoh[length] = holiday;
	infoc[length] = customer;
	length++;
}

void UnsortedType::DeleteSchedule(ItemType magician, ItemType holiday, ItemType customer)
// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
//		 Delets all the items m,h and c.
{
	int location = 0;
	ItemType empty;

	while (magician.ComparedTo(infom[location]) != EQUAL)
		location++;
	infom[location] = empty;
	infoh[location] = empty;
	infoc[location] = empty;

	infom[location] = infom[length - 1];
	infoh[location] = infoh[length - 1];
	infoc[location] = infoc[length - 1];
	length--;
}

void UnsortedType::DeleteScheduleC(ItemType holiday, ItemType customer)
// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
//       Much like the previous one, but works on holiday and
//       Customer. Created primarily for waitlist.
{
	int locationh = 0;
	int locationc = 0;

	while (holiday.ComparedTo(infoh[locationh]) != EQUAL)
		locationh++;
	while (customer.ComparedTo(infoc[locationc]) != EQUAL)
		locationc++;
	if (locationh == locationc) {
		infom[locationh] = infom[length - 1];
		infoh[locationh] = infoh[length - 1];
		infoc[locationh] = infoc[length - 1];
		length--;
	}
}

void UnsortedType::PutItemM(ItemType magician)
// Post: item is in the list.
//       Works only with magician and creates empty entry for the rest
{
	infom[length] = magician;
	infoh[length];
	infoc[length];
	length++;
}

ItemType UnsortedType::DeleteItemM(ItemType magician)
// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
// Deletes items based on magician.
{
	int location = 0;
	ItemType client;

	while (magician.ComparedTo(infom[location]) != EQUAL)
		location++;

	client = infoc[location];

	infom[location] = infom[length - 1];
	infoh[location] = infoh[length - 1];
	infoc[location] = infoc[length - 1];
	length--;
	return client;
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
//       Independent iterator for Magician only
{
  currentPos++;
  return infom[currentPos];
}

ItemType UnsortedType::GetNextItemH()
// Pre:  ResetList was called to initialized iteration.
//       No transformer has been executed since last call.
//       currentPos is defined.
// Post: item is current item.
//       Current position has been updated.
//		 Independent iterator for holiday only
{
	currentPos++;
	return infoh[currentPos];
}

ItemType UnsortedType::GetNextItemHN()
// Pre:  ResetList was called to initialized iteration.
//       No transformer has been executed since last call.
//       currentPos is defined.
// Post: item is current item.
//       Current position has been updated.
//		 Dependent iterator for holiday
{
	return infoh[currentPos];
}

ItemType UnsortedType::GetNextItemC()
// Pre:  ResetList was called to initialized iteration.
//       No transformer has been executed since last call.
//       currentPos is defined.
// Post: item is current item.
//       Current position has been updated.
//       Dependent iterator for customer
{
	return infoc[currentPos];
}