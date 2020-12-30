/*
Name: --
Date: Feb 8, 2020
Program: Assignment 1, scheduling of magicians
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>

#include "unsorted.h"

using namespace std;


int main(void) {
	int choice = 0;
	ifstream inFile;
	ofstream outFile;

	string customer;
	string holiday;
	string magician;
	ItemType itemM;
	ItemType itemC;
	ItemType itemH;
	UnsortedType magicianlist;
	UnsortedType holidaylist;
	UnsortedType schedule;
	UnsortedType waitlist;
	bool found;
	int length;


	inFile.open("Magician.txt");
	while (inFile) {
		getline(inFile, magician);
		itemM.Initialize(magician);
		magicianlist.PutItemM(itemM);
	}
	inFile.close();

	inFile.open("Holidays.txt");
	while (inFile) {
		getline(inFile, holiday);
		itemM.Initialize(holiday);
		holidaylist.PutItemM(itemM);
	}
	inFile.close();

	outFile.open("Magic.txt");

	/*
	string test;
	test = itemM.PrintString();
		cout << test;

	customer = "Joe";
	holiday = "B-day";
	magician = "Harry";

	itemC.Initialize(customer);
	itemH.Initialize(holiday);
	itemM.Initialize(magician);
	magicianslist.PutItem(itemC, itemH, itemM);

	customer = "";
	holiday = "";
	magician = "Harry";

	itemC.Initialize(customer);
	itemH.Initialize(holiday);
	itemM.Initialize(magician);
	magicianslist.PutItem(itemC, itemH, itemM);

	magicianslist.GetItem(itemC, itemH, itemM, found);
	customer = itemC.PrintString();
	holiday = itemH.PrintString();
	magician = itemM.PrintString();
	cout << customer + ' ' + holiday + " " + magician;
*/

	cout << "--------------------------------------- \n";
	cout << "Welcome to Magician Scheduling Program! \n";
	cout << "Please, choose on of the options below: \n";
	cout << "--------------------------------------- \n";

	while (choice != 6) {
		cout << "1.Schedule \n";
		cout << "2.Cancel \n";
		cout << "3.Sign up \n";
		cout << "4.Drop out \n";
		cout << "5.Status \n";
		cout << "6.Exit \n";
		cin >> choice;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (choice == 1)
		{
			cout << "You chose option 1, schedule. \n";
			cout << "Please, enter the customer's name: \n";
			cin >> customer;
			outFile << "Option 1\n";
			outFile << customer + "\n";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Please, enter the holiday you would like to book a magician for: \n";
			getline(cin,holiday);
			outFile << holiday + "\n";
			itemH.Initialize(holiday);
			itemC.Initialize(customer);
			holidaylist.GetItemM(itemH, found);
			if (found == true) {
				bool both;
				cout << holiday + " found. Searching for available magicians...\n";
				schedule.ResetList();
				magicianlist.ResetList();
				for (int j = 0; j < MAX_ITEMS; j++) {
					itemM = magicianlist.GetNextItem();
					magician = itemM.PrintString();
					if (magician == "") {
						itemM.Initialize("");
							waitlist.ScheduleH(itemM, itemH, itemC);
							cout << "There are no magicians available, you've been added on waitlist\n";
							outFile << holiday + ' ' + customer + " were put in waitlist\n";
							break;
					}
					for (int i = 0; i < MAX_ITEMS; i++) {
						schedule.GetScheduleM(itemM, itemH, i, both);
						if (both == true) {
							break;
						}
					}
					if (both != true) {
						magician = itemM.PrintString();
						schedule.ScheduleH(itemM, itemH, itemC);
						cout << magician + ' ' + holiday + ' ' + customer + " scheduled!\n";
						outFile << magician + ' ' + holiday + ' ' + customer + " scheduled!\n";
						break;
					}
				}
			}
			else {
				cout << "No such holiday\n";
			}
			
		}
		else if (choice == 2) {
			cout << "You chose option 2, cancel. \n";
			cout << "Please, enter customer's name: \n";
			cin >> customer;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			itemC.Initialize(customer);
			cout << "Please, enter the holiday: \n";
			getline(cin, holiday);
			outFile << "option 2 \n";
			outFile << customer + "\n";
			outFile << holiday + "\n";
			itemH.Initialize(holiday);
			holidaylist.GetItemM(itemH, found);
			if (found == true) {
				cout << holiday + ' ' + customer + " found. Searching for specified entries...\n";
				schedule.DeleteScheduleC(itemH, itemC);
				cout << holiday + ' ' + customer + " has been deleted from the list.\n";
				outFile << holiday + ' ' + customer + " has been deleted from the list.\n";
				waitlist.GetItemH(itemH, found);
				if (found == true) {
					bool both;
					for (int i = 0; i < MAX_ITEMS; i++) {
						waitlist.GetScheduleH(itemM, itemH, itemC, found);
						if (found == true) {
							schedule.ResetList();
							magicianlist.ResetList();
							for (int j = 0; j < MAX_ITEMS; j++) {
								itemM = magicianlist.GetNextItem();
								magician = itemM.PrintString();
								if (magician == "") {
									itemM.Initialize("");
									waitlist.ScheduleH(itemM, itemH, itemC);
									cout << "There are no magicians available, you're still on waitlist\n";
									outFile << holiday + ' ' + customer + " still in waitlist\n";
									break;
								}
								for (int i = 0; i < MAX_ITEMS; i++) {
									schedule.GetScheduleM(itemM, itemH, i, both);
									if (both == true) {
										break;
									}
								}
								if (both != true) {
									magician = itemM.PrintString();
									schedule.ScheduleH(itemM, itemH, itemC);
									waitlist.DeleteScheduleC(itemH, itemC);
									cout << magician + ' ' + holiday + ' ' + customer + " rescheduled from waitlist!\n";
									outFile << magician + ' ' + holiday + ' ' + customer + " rescheduled from waitlist!\n";
									break;
								}
							}
						}
					}
				}



				
			} else {
				cout << "No such holiday\n";
			}
		} 
		else if (choice == 3) {
			cout << "You chose option 3, sign up a magician. \n";
			outFile << "option 3 \n";
			if (magicianlist.IsFull() == 1) {
				cout << "The list is full, unable to add magician";
			}
			cout << "Please, enter the name of the new magician:";
			cin >> magician;
			outFile << magician + "\n";
			itemM.Initialize(magician);
			magicianlist.PutItemM(itemM);
			cout << magician + " was successfuly added\n";
			outFile << magician + " added\n";
		}
		else if (choice == 4) {
			bool both;
			cout << "You chose option 4, drop out a magician. \n";
			cout << "Please, enter the name of the magician you would like to drop:";
			getline(cin, magician);
			outFile << "option 4\n";
			outFile << magician + "\n";
			itemM.Initialize(magician);
			magicianlist.DeleteItemM(itemM);
			cout << magician + " was dropped\n";
			outFile << magician + " was dropped\n";
			schedule.GetSchedule(itemM, itemH, itemC, found);
			if (found == true) {
				schedule.DeleteSchedule(itemM, itemH, itemC);
				holiday = itemH.PrintString();
				if (holiday != "") {
					bool both;
					cout << holiday + " found. Searching for available magicians for reschedule...\n";
					schedule.ResetList();
					magicianlist.ResetList();
					for (int j = 0; j < MAX_ITEMS; j++) {
						itemM = magicianlist.GetNextItem();
						magician = itemM.PrintString();
						if (magician == "") {
							itemM.Initialize("");
							waitlist.ScheduleH(itemM, itemH, itemC);
							cout << "There are no magicians available, you've been added on waitlist\n";
							outFile << holiday + ' ' + customer + " were put in waitlist\n";
							break;
						}
						for (int i = 0; i < MAX_ITEMS; i++) {
							schedule.GetScheduleM(itemM, itemH, i, both);
							if (both == true) {
								break;
							}
						}
						if (both != true) {
							magician = itemM.PrintString();
							schedule.ScheduleH(itemM, itemH, itemC);
							cout << magician + ' ' + holiday + ' ' + customer + " rescheduled!\n";
							outFile << magician + ' ' + holiday + ' ' + customer + " rescheduled!\n";
							break;
						}
					}
				}
			}
				
		}
		else if (choice == 5) {
			string unid;
			ItemType temp;
			int length;
			length = schedule.GetLength();

			cout << "You chose option 5, status of magicians. \n";
			cout << "Please, enter name of magician or holiday to check status \n";
			outFile << "option 5\n";

			getline(cin, unid);
			itemM.Initialize(unid);
			outFile << unid + "\n";
			magicianlist.GetItemM(itemM, found);
			if (found == true) {
				schedule.ResetList();
				outFile << "determined that it's a magician\n";

				for (int counter = 0; counter <= length; counter++)
				{
					itemM = schedule.GetNextItem();
					itemH = schedule.GetNextItemHN();
					itemC = schedule.GetNextItemC();
					magician = itemM.PrintString();
					holiday = itemH.PrintString();
					customer = itemC.PrintString();
					if (magician == unid) {
						cout << magician + ' ' + holiday + ' ' + customer + "\n";
						outFile << magician + ' ' + holiday + ' ' + customer + "\n";
					}
				}
/*
				for (int i=0; i < MAX_ITEMS; i++) {
					temp = schedule.GetNextItem();
					magician = temp.PrintString();
					if (magician == unid) {
						schedule.GetSchedule(temp, itemH, itemC, found);
						magician = temp.PrintString();
						holiday = itemH.PrintString();
						customer = itemC.PrintString();
						cout << magician + ' ' + holiday + ' ' + customer + "\n";
					}
				}
				*/	
			}
			else {
				itemH = itemM;
				schedule.ResetList();
				outFile << "determined that it's a holiday \n";

				for (int counter = 0; counter <= length; counter++)
				{
					itemM = schedule.GetNextItem();
					itemH = schedule.GetNextItemHN();
					itemC = schedule.GetNextItemC();
					magician = itemM.PrintString();
					holiday = itemH.PrintString();
					customer = itemC.PrintString();
					if (holiday == unid) {
						cout << magician + ' ' + holiday + ' ' + customer + "\n";
						outFile << magician + ' ' + holiday + ' ' + customer + "\n";
					}
				}
				/*
				for (int i=0; i < MAX_ITEMS; i++) {
					temp = schedule.GetNextItemH();
					holiday = temp.PrintString();
					if (holiday == unid) {
						schedule.GetScheduleH(itemM, temp, itemC, found);
						magician = itemM.PrintString();
						holiday = temp.PrintString();
						customer = itemC.PrintString();
						cout << magician + ' ' + holiday + ' ' + customer + "\n";
					}
				}
				*/
			}


		}
		else {
		outFile << "option 6\n";
		outFile << "saving schedule.txt and exiting\n";
		outFile.close();
		cout << "You chose to exit, saving progress. \n";
		outFile.open("Schedule.txt");
		schedule.ResetList();
		int length;
		length = schedule.GetLength();
			for (int counter = 0; counter <= length; counter++)
			{
				itemM = schedule.GetNextItem();
				itemH = schedule.GetNextItemHN();
				itemC = schedule.GetNextItemC();
				magician = itemM.PrintString();
				holiday = itemH.PrintString();
				customer = itemC.PrintString();
				outFile << magician + ' ' + holiday + ' ' + customer + "\n";
				cout << magician + ' ' + holiday + ' ' + customer + "\n";
			}

			outFile.close();
		}


	}


	return 0;
}

