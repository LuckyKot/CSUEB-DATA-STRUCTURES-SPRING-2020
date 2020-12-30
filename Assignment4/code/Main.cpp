/*
Name: --
Date: Apr 11, 2020
Program: Assignment 4, statistical summary
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>
#include <algorithm>
#include "unsorted.h"

using namespace std;

int main(void) {

	string entry;
	ifstream inFile;
	ofstream outFile;
	string line;
	string word;
	ItemType itemWord;
	UnsortedType wordList;
	UnsortedType duplicates;
	bool found;
	
	int dupe = 0;
	//counter of dupes of 1 word
	int letters = 0;
	//counter of letters for each word
	int bigWords = 0;
	//counter for words with letters >4
	int total = 0;
	//total words in the file
	int length = 0;
	//length of list of unique words
	char chars[] = ".,:";
	//chars to be deleted from words

	string summary;
	summary = "Summary";
	int version = 1;
	//some name variables for output files

	while (entry != "exit") {
		bool exist = true;
		cout << "Please, enter the name of the file:\n";
		cout << "Or type exit to exit\n";
		cin >> entry;
		if (entry == "exit") {
			break;
		}
		entry += ".txt";
		cout << "Opening " + entry + "\n";

		inFile.open(entry);
		if (!inFile) {
			cout << "The specified file does not exist or bugged out\n";
			cout << "Please, try again\n";
			cout << "\n";
			exist = false;
			//error in case of wrong file name
		}
		else {
			while (!inFile.eof()) {
				getline(inFile, line);

				word = "";
				for (auto x : line)
				{
					if (x == ' ' || x == '-')
					{
						if (word != " ") {
							for (unsigned int i = 0; i < strlen(chars); ++i) {
								word.erase(remove(word.begin(), word.end(), chars[i]), word.end());
							}
							//deletes . ' : from words
							itemWord.Initialize(word);
							wordList.GetItem(itemWord, found);
							if (found == true) {
								duplicates.PutItem(itemWord);
								//adds to dupes  list if there is such word in unique words list
							}
							else {
								wordList.PutItem(itemWord);
								//adds unique words if there are no dupes yet
							}

							word = "";
							if (letters > 4) {
								bigWords++;
								//counter of words with more than 4 letters
							}
							total++;
							//counter of total words increment
							letters = 0;
						}
						else {
							word = "";
						}

					}
					else if (word== "<eof>") {
						break;
						//detector of end of file mark
					}
					else {
						word = word + x;
						letters++;
						//word assembly and letter number incrementation
					}
				}

			}
		}
		inFile.close();


		length = wordList.GetLength();
		//# of all unique words
		if (exist == true) {
			outFile.open(summary + ".txt");
			cout << "File name: ";
			cout << entry + "\n";
			cout << "Number of words over 4 letters: ";
			cout << bigWords;
			cout << "\n";
			cout << "Number of unique words: ";
			cout << length;
			cout << "\n";
			cout << "Total words in the text: ";
			cout << total;
			cout << "\n";

			cout << "list of duplicate words:\n";

			for (int i = 0; i <= duplicates.GetLength(); i++) {
				dupe = 0;
				duplicates.ResetList();
				itemWord = duplicates.GetNextItem();
				word = itemWord.PrintString();
				cout << word + ": ";
				outFile << word + ": ";
				dupe++;
				duplicates.DeleteItem(itemWord);
				for (int j = 0; j <= duplicates.GetLength(); j++) {
					duplicates.GetItem(itemWord, found);
					if (found == true) {
						dupe++;
						duplicates.DeleteItem(itemWord);
						j = 0;
					}
				}
				i = 0;
				cout << to_string(dupe) + "\n";
				outFile << to_string(dupe) + "\n";
			}

			outFile << "File name: ";
			outFile << entry + "\n";
			outFile << "Number of words over 4 letters: ";
			outFile << bigWords;
			outFile << "\n";
			outFile << "Number of unique words: ";
			outFile << length;
			outFile << "\n";
			outFile << "Total words in the text: ";
			outFile << total;
			outFile << "\n";

			summary = "Summary";
			version++;
			summary = summary + to_string(version);


			outFile.close();
		}

		total = 0;
		length = 0;
		bigWords = 0;
		duplicates.MakeEmpty();
		wordList.MakeEmpty();


	}


	return 0;
}