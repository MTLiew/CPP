/*
CECS 328 Programming Assignment 1: Algorithms
@file Source.cpp
@author Max Liew
@version 9/11/20
**/

#define USING_MAIN_1 //Comment this line out to use the test cases
#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <initializer_list>
using namespace std;
using namespace std::chrono;

int * randArray(int seed, int arraySize, mt19937 randNumGen, uniform_int_distribution<int> range);
int freshmanAlgorithm(int *array, int size);
int sophomoreAlgorithm(int *array, int size);
int juniorAlgorithm(int *array, int left, int right);
int seniorAlgorithm(int *array, int size);

#ifdef USING_MAIN_1
int main()
{
	int option, seed, size;
	int max, thisSum = 0;
	
	do
	{
		cout << "1: Quit the program" << endl;
		cout << "2: Time Freddy's algorithm" << endl;
		cout << "3: Time Sophie's algorithm" << endl;
		cout << "4: Time Johnny's algorithm" << endl;
		cout << "5: Time Sally's algorithm" << endl;
		cin >> option;

		if (option == 1)
			return 0;
		else
		{
			cout << "Please input a seed value: ";
			cin >> seed;

			cout << "Please input an input size: ";
			cin >> size;
		}

		mt19937 randNumGen(seed);
		uniform_int_distribution<int> range(-100, 100);
		int *iArray = randArray(seed, size, randNumGen, range);

		if (option == 2)
		{
			auto begin = high_resolution_clock::now();
			freshmanAlgorithm(iArray, size);
			auto end = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(end - begin);
			cout << duration.count() << " microseconds elapsed." << endl << endl;
		}

		else if (option == 3)
		{
			auto begin = high_resolution_clock::now();
			sophomoreAlgorithm(iArray, size);
			auto end = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(end - begin);
			cout << duration.count() << " microseconds elapsed." << endl << endl;
		}

		else if (option == 4)
		{
			auto begin = high_resolution_clock::now();
			juniorAlgorithm(iArray, 0, size - 1);
			auto end = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(end - begin);
			cout << duration.count() << " microseconds elapsed." << endl << endl;
		}

		else if (option == 5)
		{
			auto begin = high_resolution_clock::now();
			seniorAlgorithm(iArray, size);
			auto end = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(end - begin);
			cout << duration.count() << " microseconds elapsed." << endl << endl;
		}

		else
			cout << "Invalid input." << endl << endl;
	} while (true);
}
#else

int main()
{
	int array1[] = { 5, 7, 19, -2, 4, 6, -3, -3, 1, 10 };
	int array2[] = { 3, -24, 2, -15, -17, 9, 8, 10, 1, -18, 4};
	int * array3 = new int[0];
	int array4[] = { -2, -8, -5, -3, -20, -10, -14, -7, -9, -13};
	int array5[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int array6[] = { 2, 17, 4, 1, 1, 6, 10, 5, 3, 14 };

	cout << freshmanAlgorithm(array1, 10) << endl;
	cout << freshmanAlgorithm(array2, 11) << endl;
	cout << freshmanAlgorithm(array3, 0) << endl;
	cout << freshmanAlgorithm(array4, 10) << endl;
	cout << freshmanAlgorithm(array5, 10) << endl;
	cout << freshmanAlgorithm(array6, 10) << endl << endl;

	cout << sophomoreAlgorithm(array1, 10) << endl;
	cout << sophomoreAlgorithm(array2, 11) << endl;
	cout << sophomoreAlgorithm(array3, 0) << endl;
	cout << sophomoreAlgorithm(array4, 10) << endl;
	cout << sophomoreAlgorithm(array5, 10) << endl;
	cout << sophomoreAlgorithm(array6, 10) << endl << endl;

	cout << juniorAlgorithm(array1, 0, 9) << endl;
	cout << juniorAlgorithm(array2, 0, 10) << endl;
	cout << juniorAlgorithm(array3, 0, 0) << endl;
	cout << juniorAlgorithm(array4, 0, 9) << endl;
	cout << juniorAlgorithm(array5, 0, 9) << endl;
	cout << juniorAlgorithm(array6, 0, 9) << endl << endl;

	cout << seniorAlgorithm(array1, 10) << endl;
	cout << seniorAlgorithm(array2, 11) << endl;
	cout << seniorAlgorithm(array3, 0) << endl;
	cout << seniorAlgorithm(array4, 10) << endl;
	cout << seniorAlgorithm(array5, 10) << endl;
	cout << seniorAlgorithm(array6, 10) << endl << endl;

	system("pause");
	return 0;
}
#endif

int * randArray(int seed, int arraySize, mt19937 randNumGen, uniform_int_distribution<int> range)
{
	int* array = new int[arraySize];
	for (int i = 0; i < arraySize; i++)
	{
		array[i] = range(randNumGen);
	}
	return array;
}

int freshmanAlgorithm(int *array, int size)
{
	int max = 0;
	for (int i = 0; i < size; i++)
		for (int j = i; j < size; j++)
		{
			int thisSum = 0;
			for (int k = i; k <= j; k++)
				thisSum = thisSum + array[k];
			if (thisSum > max)
				max = thisSum;
		}
	return max;
}

int sophomoreAlgorithm(int *array, int size)
{
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		int thisSum = 0;
		for (int j = i; j < size; j++)
		{
			thisSum = thisSum + array[j];
			if (thisSum > max)
				max = thisSum;
		}
	}
	return max;
}

int juniorAlgorithm(int * array, int left, int right)
{
	if (left == right)
	{
		if (array[left] > 0)
			return array[left];
		return 0;
	}

	int center = (left + right) / 2;
	int maxLeftSum = juniorAlgorithm(array, left, center);
	int maxRightSum = juniorAlgorithm(array, center + 1, right);

	int maxLeftBorder = 0;
	int leftBorder = 0;
	for (int i = center; i >= left; i--)
	{
		leftBorder = leftBorder + array[i];
		if (leftBorder > maxLeftBorder)
			maxLeftBorder = leftBorder;
	}
		
	int maxRightBorder = 0;
	int rightBorder = 0;
	for (int i = center + 1; i <= right; i++)
	{
		rightBorder = rightBorder + array[i];
		if (rightBorder > maxRightBorder)
			maxRightBorder = rightBorder;
	}

	return max({ maxLeftSum, maxRightSum, maxLeftBorder + maxRightBorder});
}

int seniorAlgorithm(int *array, int size)
{
	int max = 0;
	int thisSum = 0;
	for (int i = 0; i < size; i++)
	{
		thisSum = thisSum + array[i];
		if (thisSum > max)
			max = thisSum;
		else if (thisSum < 0)
			thisSum = 0;
	}
	return max;
}