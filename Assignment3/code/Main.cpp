/*
Name: --
Date: Apr 11, 2020
Program: Assignment 3, n skip m grams
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>
#include "unsorted.h"

using namespace std;

string getWord(UnsortedType& list, string& sentence, int n);
//gets a word from the n-th place of linked list and appends it to the sentence

int main(void) {
	
	ifstream inFile;
	ofstream outFile;
	int n;
	int m;
	int current;
	string sentence;
	string word;
	ItemType itemWord;
	UnsortedType mix;
	bool found;

	cout << "Please, enter the number of words to be skipped (n)\n";
	cin >> n;

	cout << "Please, enter the number of words to be picked from the sentence (m)\n";
	cin >> m;

	cout << "\n";

	inFile.open("quotes.txt");
	outFile.open("nskipmgram_quotes.txt");

	while (inFile) {
		getline(inFile, sentence);
		//reads just 1 line
		
		if (!inFile) {
			break;
		}
		
		word = "";
		for (auto x : sentence)
		{
			if (x == ' ')
			{
				itemWord.Initialize(word);
				mix.PutItem(itemWord);
				word = "";
			}
			else
			{
				word = word + x;
			}
		}
		//breaks into words and puts them on the list

		mix.ResetList();

		int length;
		length = mix.GetLength();
		sentence = "";


		int iterator = 0;
		int skip = n+1;
		if (n % 2 == 0) {
			while (skip + n <= length) {
				getWord(mix, sentence, iterator);

				skip = iterator;
				for (int i = 1; i < m; i++)
				{
					skip = skip + n + 1;
					word = getWord(mix, sentence, skip);

				}
				iterator++;

			}
		}
		else {
			while (skip + n <= length - 1) {
				getWord(mix, sentence, iterator);

				skip = iterator;
				for (int i = 1; i < m; i++)
				{
					skip = skip + n + 1;
					word = getWord(mix, sentence, skip);

				}
				iterator++;
			}
		}

		sentence += "\n";
		cout << sentence;

		outFile << sentence << endl;

		mix.MakeEmpty();
		//empties the list for the next sentence
		
	}
	inFile.close();



	outFile.close();

	return 0;
}

string getWord(UnsortedType& list, string& sentence, int n) {
	string word;
	ItemType itemWord;
	int length;

	list.ResetList();
	
	int j = 0;
	length = list.GetLength();

	for (j; j <  length - n; j++) {
		itemWord = list.GetNextItem();
	}
	//finds n-th word
	word = itemWord.PrintString();
	sentence += word + " ";
	//apends to the final sentence string

	return word;
}