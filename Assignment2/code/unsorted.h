#include "ItemType.h" 
// File ItemType.h must be provided by the user of this class. 
//  ItemType.h must contain the following definitions: 
//  MAX_ITEMS:     the maximum number of items on the list 
//  ItemType:      the definition of the objects on the list 
//  RelationType:  {LESS, GREATER, EQUAL}
//  Member function ComparedTo(ItemType item) which returns 
//       LESS, if self "comes before" item 
//       GREATER, if self "comes after" item 
//       EQUAL, if self and item are the same 

class UnsortedType 
{
public:
  UnsortedType();
  // Constructor
  
  void MakeEmpty();
  // Function: Returns the list to the empty state.
  // Post:  List is empty.
  
  bool IsFull() const;
  // Function:  Determines whether list is full.
  // Pre:  List has been initialized.
  // Post: Function value = (list is full)

  int GetLength() const;
  // Function: Determines the number of elements in list.
  // Pre:  List has been initialized.
  // Post: Function value = number of elements in list

  ItemType GetItem(ItemType, bool&);
  // Function: Retrieves list element whose key matches item's key (if
  //           present).
  // Pre:  List has been initialized.
  //       Key member of item is initialized.
  // Post: If there is an element someItem whose key matches
  //       item's key, then found = true and someItem is returned.
  // 	 otherwise found = false and item is returned.
  //       List is unchanged.

  void GetPatient(ItemType itemP, bool& found);
  //gets patient info

  void GetDoctorW(ItemType itemD, ItemType& itemR, ItemType& itemC, ItemType& itemP, bool& found);
  //gets room, label, patient info just from doctor name

  void GetDoctorByCode(ItemType& itemD, ItemType itemC, bool& found);
  //gets just doctor's name just from label

  void GetDoctorByPatient(ItemType& itemD, ItemType itemP, bool& found);
  //gets only doc's name from patient name

  void GetDoctorInfo(ItemType& itemD, ItemType& itemR, ItemType& itemC, bool& found);
  //gets info about doctor just from label

  bool isAvailable(ItemType itemD, bool& found);
  //checks if doctor is busy at the moment 

  ItemType GetItemCode(ItemType itemC, bool& found);
  //gets doctor's label

  void GetDoctor(ItemType& itemD, ItemType& itemR, ItemType& itemC, ItemType itemP, bool& found);
  //schedules a doctor

  void GetDoctorD(ItemType& itemD, ItemType& itemR, ItemType& itemC, ItemType itemP, bool& found);
  //gets doctor info from only patient
  
  void DeletePatient(ItemType itemP, bool& found);
  //deletes just patient, leaves everything else

  void DeleteWL(ItemType itemD, ItemType itemR, ItemType itemC, ItemType itemP);
  //delete all data in position

  void ScheduleP(ItemType itemP, int i);
  //schedule patient to doctoer

  ItemType findP(ItemType itemP, int i);
  //find patient by i (position in list)

  bool findD(ItemType itemD, int i);
  //find doctor by i (position in list)

  void PutItem(ItemType item);
  // Function: Adds item to list.
  // Pre:  List has been initialized.
  //       List is not full.
  //       item is not in list.
  // Post: item is in list.

  void PutItemAll(ItemType itemD, ItemType itemR, ItemType itemC, ItemType itemP);
  // Function: Adds all items to the list
  // Post: all the items are on the list at length

  void DeleteItem(ItemType item);
  // Function: Deletes the element whose key matches item's key.
  // Pre:  List has been initialized.
  //       Key member of item is initialized.
  //       One and only one element in list has a key matching item's key.
  // Post: No element in list has a key matching item's key.

  void ResetList();
  // Function: Initializes current position for an iteration through the list.
  // Pre:  List has been initialized.
  // Post: Current position is prior to list.

  ItemType GetNextItem();
  // Function: Gets the next element in list.
  // Pre:  List has been initialized and has not been changed since last call.
  //       Current position is defined.
  //       Element at current position is not last in list.
  //	     
  // Post: Current position is updated to next position.
  //       item is a copy of element at current position.

private:
  int length;
  ItemType infod[MAX_ITEMS];
  ItemType infor[MAX_ITEMS];
  ItemType infoc[MAX_ITEMS];
  ItemType infop[MAX_ITEMS];
  int currentPos;
};

