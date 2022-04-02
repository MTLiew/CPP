#include <iostream>
#include <fstream>
#include "RedBlackTreeMap.h"
#include <string>
using namespace std;

int main()
{
	string tempKey;
	string tempValue;
	int temp = 0;
	RedBlackTreeMap<string, int> tree;
	
	ifstream inputFile;
	inputFile.open("players_homeruns.csv");

	if (!inputFile.is_open()) throw runtime_error("Could not open file");

	for (int i = 1; i <= 10; i++)
	{
		getline(inputFile, tempKey, ',');

		getline(inputFile, tempValue);

		temp = stoi(tempValue);
		
		tree.insert(tempKey, temp);

		tree.printStructure();

		cout << "--------------------------" << endl;
	}

	//CURRENTLY FINISHED WITH 10TH INSERTION
	cout << tree.find("Stan Musial") << endl; //475 CURRENTLY A LEAF NODE
	cout << tree.find("Honus Wagner") << endl; //101 CURRENTLY ROOT
	cout << tree.find("Rogers Hornsby") << endl; //301 CURRENTLY HAS ONE NIL AND ONE NON-NIL CHILD
	cout << tree.find("Ted Williams") << endl; //521 CURRENTLY RED

	while (getline(inputFile, tempKey, ','))
	{
		getline(inputFile, tempValue);
		temp = stoi(tempValue);
		tree.insert(tempKey, temp);
	}

	tree.printStructure();

	cout << "--------------------------" << endl;

	//FINISHED WITH ALL INSERTIONS
	cout << tree.find("Stan Musial") << endl; //475
	cout << tree.find("Honus Wagner") << endl; //101
	cout << tree.find("Rogers Hornsby") << endl; //301
	cout << tree.find("Ted Williams") << endl; //521

	inputFile.close();
	return 0;
}