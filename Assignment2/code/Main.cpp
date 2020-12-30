/*
Name: --
Date: Feb 29, 2020
Program: Assignment 2, scheduling of doctors
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>

#include "unsorted.h"

using namespace std;

int main(void) {

	ifstream inFile;
	ofstream outFile;

	int choice = 0;
	bool found = 0;
	bool available = 0;
	string name;
	string scode;
	string doc;
	ItemType itemName;
	ItemType itemScode;
	ItemType itemRoom;
	ItemType itemDoc;
	int room;
	string sroom;
	int age = 0;
	UnsortedType rooms;
	UnsortedType doctors;
	UnsortedType scodes;
	UnsortedType waitlist;
	string appointment;

	//Rooms load
	inFile.open("Rooms.txt");
	while (inFile >> room) {
		sroom = to_string(room);
		itemRoom.Initialize(sroom);
		rooms.PutItem(itemRoom);
	}
	inFile.close();
	
	//Labels load
	inFile.open("Codes.txt");
	while (inFile) {
		getline(inFile, scode);
		itemScode.Initialize(scode);
		scodes.PutItem(itemScode);
	}
	inFile.close();

	//Banner
	cout << "---------------------------------------- \n";
	cout << "Welcome to doctor Scheduling Program! \n";
	cout << "Please, choose one of the options below: \n";
	cout << "---------------------------------------- \n";

	//Interface
	while (choice != 5) {
		cout << "1.Doctor check-in \n";
		cout << "2.Doctor check-out \n";
		cout << "3.Patient check-in \n";
		cout << "4.Patient check-out \n";
		cout << "5.Exit \n";
		cin >> choice;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		//1.Check-in
		if (choice == 1)
		{
			cout << "Option 1 selected, Doctor check-in \n";
			cout << "Please, enter your name: \n";
			cin >> doc;
			cout << "Please, enter the room number you prefer: \n";
			cin >> room;
			sroom = to_string(room);
			cout << "Please, enter your specialty code: \n";
			cin >> scode;
			itemDoc.Initialize(doc);
			itemScode.Initialize(scode);
			itemRoom.Initialize(sroom);
			itemName.Initialize("");

			rooms.GetItem(itemRoom, found);
			//Sign in doctor
			if (found == true) {
				scodes.GetItem(itemScode, found);
				if (found == true) {
					doctors.PutItemAll(itemDoc,itemRoom,itemScode,itemName);
					rooms.DeleteItem(itemRoom);
					scodes.DeleteItem(itemScode);
					cout << doc + " signs in room " + sroom + " spec: (" + scode + ")\n";
				}
				else {
					//error with label
					cout << "Sorry, there is no such speciality as " + scode + " or it there already is a doctor with it\n";
					cout << "Please, try again \n";
				}
			} else {
				//error with room
				cout << "Sorry, this room must be occupied or does not exist \n";
				cout << "Please, try again \n";
			}
		}

		//2.Sign out doctor
		if (choice == 2)
		{
			cout << "Option 2 selected, Doctor check-out \n";
			cout << "Please, enter your name: \n";
			cin >> doc;
			itemDoc.Initialize(doc);
			doctors.GetItem(itemDoc, found);

			//checks if there is a doctor with entered name
			if (found == true) {
				doctors.GetDoctorW(itemDoc, itemRoom, itemScode, itemName, found);
				sroom = itemRoom.PrintString();
				scode = itemScode.PrintString();
				name = itemName.PrintString();
				if (name != "") {
					//signs out
					cout << "The session of doctor " + doc + " in room " + sroom + " with " + name + " has ended\n";
					cout << "Have a nice day, doctor " + doc + "\n";
					scodes.PutItem(itemScode);
					rooms.PutItem(itemRoom);
					doctors.DeleteWL(itemDoc, itemRoom, itemScode, itemName);
					//rescheduling
					waitlist.GetItem(itemDoc, found);
					if (found == true) {
						cout << "Rescheduling clients from waitlist to other available doctors\n";
						
						int i = 0;
						int j = 0;
						ItemType temp;
						string tempS;
						waitlist.ResetList();
						doctors.ResetList();
						while (i <= waitlist.GetLength()) {
							found = waitlist.findD(itemDoc, i);
							if (found == true) {
								itemName = waitlist.findP(itemName, i);
								name = itemName.PrintString();
								while (j <= doctors.GetLength()) {
									temp = doctors.GetNextItem();
									j++;
									tempS = temp.PrintString();
									available = doctors.isAvailable(temp, found);
									if (tempS != "" && available == true) {
										doctors.ScheduleP(itemName, j);
										cout << "rescheduled " + name + " to doctor " + tempS + " \n";
										break;
									}
									else if (j >= doctors.GetLength()) {
										cout << "There are no available doctors for reschedule of " + name + "\n";
										cout << "Please, come back later for manual reschedule\n";
										break;
									}
								}
							}
							i++;
						}

					}
				} else {
				//signout
				cout << "Have a nice day, doctor " + doc + "\n";
				scodes.PutItem(itemScode);
				rooms.PutItem(itemRoom);
				doctors.DeleteWL(itemDoc, itemRoom, itemScode, itemName);
				//rescheduling
				waitlist.GetItem(itemDoc, found);
				if (found == true) {
					cout << "Rescheduling clients from waitlist to other available doctors\n";
					int i = 0;
					int j = 0;
					ItemType temp;
					string tempS;
					waitlist.ResetList();
					doctors.ResetList();
					while (i <= waitlist.GetLength()) {
						found = waitlist.findD(itemDoc, i);
						if (found == true) {
							itemName = waitlist.findP(itemName, i);
							name = itemName.PrintString();
							while (j <= doctors.GetLength()) {
								temp = doctors.GetNextItem();
								tempS = temp.PrintString();
								available = doctors.isAvailable(temp, found);
								if (tempS != "" && available == true) {
									doctors.ScheduleP(itemName, j);
									cout << "rescheduled " + name + " to doctor " + tempS + " \n";
									break;
								}
								else if ( j == doctors.GetLength() && available == false) {
									cout << "There are no available doctors for reschedule\n";
									cout << "Please, come back later for manual reschedule\n";
									break;
								}
								j++;
							}
						}
						i++;
					}
				}
			}
				/*
				if (name != "") {
					cout << "The session of doctor " + doc + " in room " + sroom + " with " + name + " has ended\n";
					cout << "Have a nice day, doctor " + doc + "\n";
					scodes.PutItem(itemScode);
					rooms.PutItem(itemRoom);
					doctors.DeleteWL(itemDoc, itemRoom, itemScode, itemName);
					//rescheduling
					waitlist.GetItem(itemDoc, found);
					if (found == true) {
						cout << "Rescheduling clients from waitlist to other available doctors\n";
						int i = 0;
						int j = 0;
						string temp = itemDoc.PrintString();
						//temp holds the doctor who left
						//doc holdsthe doctor from waitlist
						//sub holds the doctor from doctors list
						string sub;
						waitlist.ResetList();								
						doctors.ResetList();
						while (i <= waitlist.GetLength()) {
							itemDoc = waitlist.GetNextItem();
							i++;
							doc = itemDoc.PrintString();
							if (doc == temp) {
								waitlist.findP(itemName, i);
								name = itemName.PrintString();
								cout << name + " needs a reschedule\n";
								while (j <= doctors.GetLength()) {
									itemDoc = doctors.GetNextItem();
									j++;
									sub = itemDoc.PrintString();
									available = doctors.isAvailable(itemDoc, found);
									if ((sub != "") && (available == true)) {
										doctors.ScheduleP(itemName, j);
										sub = itemDoc.PrintString();
										sroom = itemRoom.PrintString();
										scode = itemScode.PrintString();
										name = itemName.PrintString();
										cout << name + " rescheduled with " + sub + " in room #" + sroom + "\n";
										break;
									}
									else if (j == doctors.GetLength() && available == false) {
										cout << "There are no available doctors for a reschedule \n";
										cout << "Please, come back later and reschedule manually \n";
										break;
									}
								}
							}
						}
					}
				}
				else {
					cout << "Have a nice day, doctor " + doc + "\n";
					scodes.PutItem(itemScode);
					rooms.PutItem(itemRoom);
					doctors.DeleteWL(itemDoc, itemRoom, itemScode, itemName);
					//rescheduling
					waitlist.GetItem(itemDoc, found);
					if (found == true) {
						cout << "Rescheduling clients from waitlist to other available doctors\n";

					}
				} */
			} else {
				//error if there is no such doctor
				cout << "There is no such doctor present at the moment \n";
				cout << "Please try again\n";
			}
			
		}

		//3.Patient check in
		if (choice == 3)
		{
			cout << "Option 3 selected, Patient check-in \n";
			cout << "Please, enter your name: \n";
			cin >> name;
			cout << "Please, enter your age: \n";
			cin >> age;
			itemName.Initialize(name);
			if (age < 16) {
				scode = "PED";
				itemScode.Initialize(scode);
				//appoint kid to pediatrist
				doctors.GetItemCode(itemScode, found);
				if (found == true) {
					doctors.GetDoctorByCode(itemDoc, itemScode, found);
					available = doctors.isAvailable(itemDoc, found);
					if (available == true) {
						doctors.GetDoctor(itemDoc, itemRoom, itemScode, itemName, found);
						scode = itemScode.PrintString();
						sroom = itemRoom.PrintString();
						doc = itemDoc.PrintString();
						cout << "The doctor is ready to take you right now \n";
						appointment = name + ' ' + scode + ' ' + sroom + ' ' + doc + "\n";
						cout << appointment;
					}
					else {
						cout << "The doctor is busy with another patient at the moment. \n";
						cout << "Please, wait\n";
						//waitlist
						doctors.GetDoctorInfo(itemDoc, itemRoom, itemScode, found);
						waitlist.PutItemAll(itemDoc, itemRoom, itemScode, itemName);

						scode = itemScode.PrintString();
						sroom = itemRoom.PrintString();
						doc = itemDoc.PrintString();
						appointment = name + ' ' + scode + ' ' + sroom + ' ' + doc + " on waitlist\n";
						cout << appointment;
					}
				}
				else {
					cout << "The specified specialization is not available today, checking for General doctors availability... \n";
					scode = "GEN";
					itemScode.Initialize(scode);
					doctors.GetItemCode(itemScode, found);
					if (found == true) {
						//appoint GEN if no needed doc
						doctors.GetDoctorByCode(itemDoc, itemScode, found);
						available = doctors.isAvailable(itemDoc, found);
						if (available == true) {
							doctors.GetDoctor(itemDoc, itemRoom, itemScode, itemName, found);
							scode = itemScode.PrintString();
							sroom = itemRoom.PrintString();
							doc = itemDoc.PrintString();
							cout << "The doctor is ready to take you right now \n";
							appointment = name + ' ' + scode + ' ' + sroom + ' ' + doc + "\n";
							cout << appointment;
						}
						else {
							cout << "The doctor is busy with another patient at the moment. \n";
							cout << "Please, wait\n";
							//waitlist
							doctors.GetDoctorInfo(itemDoc, itemRoom, itemScode, found);
							waitlist.PutItemAll(itemDoc, itemRoom, itemScode, itemName);

							scode = itemScode.PrintString();
							sroom = itemRoom.PrintString();
							doc = itemDoc.PrintString();
							appointment = name + ' ' + scode + ' ' + sroom + ' ' + doc + " on waitlist\n";
							cout << appointment;
						}
					}
					else {
						cout << "There are no General doctors available. Appointing any other available doctor \n";
						//appoint anyone available
						doctors.ResetList();
						itemDoc = doctors.GetNextItem();
						doc = itemDoc.PrintString();
						if (doc == "") {
							cout << "Sorry, there are no doctors available at the moment, come back later \n";
						}
						else {
							doctors.GetDoctorByCode(itemDoc, itemScode, found);
							available = doctors.isAvailable(itemDoc, found);
							if (available == true) {
								doctors.GetDoctor(itemDoc, itemRoom, itemScode, itemName, found);
								scode = itemScode.PrintString();
								sroom = itemRoom.PrintString();
								doc = itemDoc.PrintString();
								cout << "The doctor is ready to take you right now \n";
								appointment = name + ' ' + scode + ' ' + sroom + ' ' + doc + "\n";
								cout << appointment;
							}
							else {
								cout << "The doctor is busy with another patient at the moment. \n";
								cout << "Please, wait\n";
								//waitlist
								doctors.GetDoctorInfo(itemDoc, itemRoom, itemScode, found);
								waitlist.PutItemAll(itemDoc, itemRoom, itemScode, itemName);

								scode = itemScode.PrintString();
								sroom = itemRoom.PrintString();
								doc = itemDoc.PrintString();
								appointment = name + ' ' + scode + ' ' + sroom + ' ' + doc + " on waitlist\n";
								cout << appointment;
							}
						}
					}
				}

			}
			else {
				cout << "Please, specify the specialization of the doctor you would like to meet: \n";
				cin >> scode;
				itemScode.Initialize(scode);
				doctors.GetItemCode(itemScode, found);
				if (found == true) {
					//appoint non-child (above 16);
					doctors.GetDoctorByCode(itemDoc, itemScode, found);
					available = doctors.isAvailable(itemDoc, found);
					if (available == true) {
						doctors.GetDoctor(itemDoc, itemRoom, itemScode, itemName, found);
						scode = itemScode.PrintString();
						sroom = itemRoom.PrintString();
						doc = itemDoc.PrintString();
						cout << "The doctor is ready to take you right now \n";
						appointment = name + ' ' + scode + ' ' + sroom + ' ' + doc + "\n";
						cout << appointment;
					}
					else {
						cout << "The doctor is busy with another patient at the moment. \n";
						cout << "Please, wait\n";
						//waitlist
						doctors.GetDoctorInfo(itemDoc, itemRoom, itemScode, found);
						waitlist.PutItemAll(itemDoc, itemRoom, itemScode, itemName);

						scode = itemScode.PrintString();
						sroom = itemRoom.PrintString();
						doc = itemDoc.PrintString();
						appointment = name + ' ' + scode + ' ' + sroom + ' ' + doc + " on waitlist\n";
						cout << appointment;
					}
				}
				else {
					cout << "The specified specialization is not available today, checking for General doctors availability... \n";
					scode = "GEN";
					itemScode.Initialize(scode);
					doctors.GetItemCode(itemScode, found);
					if (found == true) {
						//appoint gen if not available
						doctors.GetDoctorByCode(itemDoc, itemScode, found);
						available = doctors.isAvailable(itemDoc, found);
						if (available == true) {
							doctors.GetDoctor(itemDoc, itemRoom, itemScode, itemName, found);
							scode = itemScode.PrintString();
							sroom = itemRoom.PrintString();
							doc = itemDoc.PrintString();
							cout << "The doctor is ready to take you right now \n";
							appointment = name + ' ' + scode + ' ' + sroom + ' ' + doc + "\n";
							cout << appointment;
						}
						else {
							cout << "The doctor is busy with another patient at the moment. \n";
							cout << "Please, wait\n";
							//waitlist
							doctors.GetDoctorInfo(itemDoc, itemRoom, itemScode, found);
							waitlist.PutItemAll(itemDoc, itemRoom, itemScode, itemName);

							scode = itemScode.PrintString();
							sroom = itemRoom.PrintString();
							doc = itemDoc.PrintString();
							appointment = name + ' ' + scode + ' ' + sroom + ' ' + doc + " on waitlist\n";
							cout << appointment;
						}
					}
					else {
						cout << "There are no General doctors available. Appointing any other available doctor \n";
						//appoint anyone
						doctors.ResetList();
						int i = 0;
						while (i <= doctors.GetLength()) {
							itemDoc = doctors.GetNextItem();
							doc = itemDoc.PrintString();
							if (doc == "") {
								cout << "Sorry, there are no doctors available at the moment, come back later \n";
								break;
							}
							else {
								available = doctors.isAvailable(itemDoc, found);
								if (available == true) {
									doctors.GetDoctorD(itemDoc, itemRoom, itemScode, itemName, found);
									doctors.ScheduleP(itemName, i);
									scode = itemScode.PrintString();
									sroom = itemRoom.PrintString();
									doc = itemDoc.PrintString();
									cout << "The doctor is ready to take you right now \n";
									appointment = name + ' ' + scode + ' ' + sroom + ' ' + doc + "\n";
									cout << appointment;
									break;
								}
								else {
									cout << "The doctor is busy with another patient at the moment. \n";
									cout << "Please, wait\n";
									//waitlist
									doctors.GetDoctorInfo(itemDoc, itemRoom, itemScode, found);
									waitlist.PutItemAll(itemDoc, itemRoom, itemScode, itemName);

									scode = itemScode.PrintString();
									sroom = itemRoom.PrintString();
									doc = itemDoc.PrintString();
									appointment = name + ' ' + scode + ' ' + sroom + ' ' + doc + " on waitlist\n";
									cout << appointment;
								}
							}
							i++;
						}
					}
				}
			}
		}

		//4.Patient check out
		if (choice == 4)
		{
			cout << "Option 4 selected, Patient check-out \n";
			cout << "Please, enter your name: \n";
			cin >> name;
			itemName.Initialize(name);
			doctors.GetPatient(itemName, found);

			//checkout without waitlists
			if (found == true) {
				doctors.GetDoctorByPatient(itemDoc, itemName, found);
				doctors.DeletePatient(itemName,found);
				cout << "Have a nice day, " + name + "!\n";

				doc = itemDoc.PrintString();
				waitlist.GetItem(itemDoc, found);
				//waitlist swap
				if (found == true) {
					cout << "Waitlisted appointment for " + doc + " found\n";
					waitlist.GetDoctorW(itemDoc, itemRoom, itemScode, itemName, found);
					sroom = itemRoom.PrintString();
					doc = itemDoc.PrintString();
					name = itemName.PrintString();
					doctors.GetDoctor(itemDoc, itemRoom, itemScode, itemName, found);
					cout << name + ' ' + "is now being checked by " + doc + " in room number " + sroom + "\n";
					waitlist.DeleteWL(itemDoc, itemName, itemScode, itemName);
				}
			}
			else {
				//error if name not found
				cout << "There is no such patient at the moment\n";
				cout << "Please, try again\n";
			}

		//exit
		}
		if (choice == 5) {
			cout << "Option 5 selected, exiting the program. \n";
			break;
		}
	}

	return 0;
}