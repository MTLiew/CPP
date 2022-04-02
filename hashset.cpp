#include <iostream>
#include <fstream>
#include "hashset.h"
#include <algorithm>
#include <string>
using namespace std;

bool iAlnum(char c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return true;
	else 
		return false;
	
}

int main()
{
	string temp;
	HashSet<string> table(50);
	int counter = 0;

	ifstream inputFile;
	inputFile.open("trump_speech.txt");

	while (inputFile >> temp)
	{
		for (int i = 0; i < temp.size(); i++)
		{
			if (iAlnum(temp[i]))
			{
				temp[i] = tolower(temp[i]);
			}

			else temp.erase(i, 1);
		}

		if (temp.length() == 1 && !iAlnum(temp[0]));

		else table.add(temp);
	}

	cout << "There are " << table.count() << " distinct words in the hash set.";

	inputFile.close();
	return 0;
}