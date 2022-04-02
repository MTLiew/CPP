#pragma warning(disable : 4996)
#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <ctime>
using namespace std;
using namespace std::chrono;

bool isOrdered(int array[])
{
	for (int i = 1; i < 50; i++)
	{
		if (array[i - 1] > array[i])
			return false;
	}

	return true;
}

void insertionSort(int a[], int left, int right)
{
	for (int i = left + 1; i <= right; i++)
	{
		int j, temp = a[i];

		for (j = i - 1; j >= left; j--)
		{
			if (a[j] > temp)
				a[j + 1] = a[j];
			else
				break;
		}

		a[j + 1] = temp;
	}
}

int medianOfThree(int array[], int left, int right)
{
	int middle = (right + left) / 2;

	if (array[left] >= array[middle] && array[left] <= array[right]) //middle, left, right
		return left;

	else if (array[right] >= array[middle] && array[right] <= array[left]) // middle, right, left
		return right;

	else if (array[middle] >= array[left] && array[middle] <= array[right]) // left, middle, right
		return middle;

	else if (array[right] >= array[left] && array[right] <= array[middle]) //left, right, middle
		return right;

	else if (array[middle] >= array[right] && array[middle] <= array[left]) //right, middle, left
		return middle;

	else if (array[left] >= array[right] && array[left] <= array[middle]) //right, left, middle
		return left;
}

void quickSort(int array[], int left, int right)
{
	if ((right - left + 1) <= 10)
		insertionSort(array, left, right);
	else
	{
		int median = medianOfThree(array, left, right);

		swap(array[median], array[right]);

		int store = left;

		for (int i = left; i < right; i++)
		{
			if (array[i] <= array[median])
			{
				swap(array[store], array[i]);
				store++;
			}
		}

		swap(array[right], array[store]);

		quickSort(array, left, store - 1);
		quickSort(array, store + 1, right);
	}
}

const int iSize = 100000;

int main()
{
	int option;

	int original[iSize];
	int	duplicate[iSize];

	do
	{	
		cout << "1: Quit the program" << endl;
		cout << "2: Sort a sorted array" << endl;
		cout << "3: Sort a random array" << endl;
		cout << "4: Sort a reverse array" << endl;

		cin >> option;

		if (option == 1)
			return 0;

		else if (option == 2)
		{
			for (int i = 0; i < iSize; i++)
				original[i] = i + 1;

			copy(begin(original), end(original), begin(duplicate));

			auto begin = high_resolution_clock::now();
			insertionSort(original, 0, iSize - 1);
			auto end = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(end - begin);
			cout << duration.count() << " microseconds elapsed for Insertion sort." << endl;
			if (isOrdered(original))
				cout << "The array has been sorted correctly." << endl;
			else
				cout << "There was an error sorting the array." << endl;

			begin = high_resolution_clock::now();
			quickSort(duplicate, 0, iSize - 1);
			end = high_resolution_clock::now();
			duration = duration_cast<microseconds>(end - begin);
			cout << duration.count() << " microseconds elapsed for Quicksort." << endl;
			if (isOrdered(duplicate))
				cout << "The array has been sorted correctly." << endl;
			else
				cout << "There was an error sorting the array." << endl << endl;
		}

		else if (option == 3)
		{
			mt19937 randNumGen(time(0));
			uniform_int_distribution<int> range(1, iSize);
			for (int i = 0; i < iSize; i++)
				original[i] = range(randNumGen);

			copy(begin(original), end(original), begin(duplicate));

			auto begin = high_resolution_clock::now();
			insertionSort(original, 0, iSize - 1);
			auto end = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(end - begin);
			cout << duration.count() << " microseconds elapsed for Insertion sort." << endl;
			if (isOrdered(original))
				cout << "The array has been sorted correctly." << endl;
			else
				cout << "There was an error sorting the array." << endl;

			begin = high_resolution_clock::now();
			quickSort(duplicate, 0, iSize - 1);
			end = high_resolution_clock::now();
			duration = duration_cast<microseconds>(end - begin);
			cout << duration.count() << " microseconds elapsed for Quicksort." << endl;
			if (isOrdered(duplicate))
				cout << "The array has been sorted correctly." << endl;
			else
				cout << "There was an error sorting the array." << endl << endl;
		}

		else if (option == 4)
		{
			for (int i = 0; i < iSize; i++)
				original[i] = iSize - i;

			copy(begin(original), end(original), begin(duplicate));

			auto begin = high_resolution_clock::now();
			insertionSort(original, 0, iSize - 1);
			auto end = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(end - begin);
			cout << duration.count() << " microseconds elapsed for Insertion sort." << endl;
			if (isOrdered(original))
				cout << "The array has been sorted correctly." << endl;
			else
				cout << "There was an error sorting the array." << endl;

			begin = high_resolution_clock::now();
			quickSort(duplicate, 0, iSize - 1);
			end = high_resolution_clock::now();
			duration = duration_cast<microseconds>(end - begin);
			cout << duration.count() << " microseconds elapsed for Quicksort." << endl;
			if (isOrdered(duplicate))
				cout << "The array has been sorted correctly." << endl;
			else
				cout << "There was an error sorting the array." << endl << endl;
		}

		else if (option == 5) //DEVELOPER TEST CASE
		{
			int testArray[50], testArray2[50];
			
			mt19937 randNumGen(time(0));
			uniform_int_distribution<int> range(1, 50);
			for (int i = 0; i < 50; i++)
				testArray[i] = range(randNumGen);

			copy(begin(testArray), end(testArray), begin(testArray2));

			auto begin = high_resolution_clock::now();
			insertionSort(testArray, 0, 49);
			auto end = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(end - begin);
			cout << duration.count() << " microseconds elapsed for Insertion sort." << endl;
			if (isOrdered(testArray))
				cout << "The array has been sorted correctly." << endl;
			else
				cout << "There was an error sorting the array." << endl;

			begin = high_resolution_clock::now();
			quickSort(testArray2, 0, 49);
			end = high_resolution_clock::now();
			duration = duration_cast<microseconds>(end - begin);
			cout << duration.count() << " microseconds elapsed for Quicksort." << endl;
			if (isOrdered(testArray2))
				cout << "The array has been sorted correctly." << endl;
			else
				cout << "There was an error sorting the array." << endl << endl;

			for (int i = 0; i < 50; i++)
				cout << testArray[i] << " ";

			cout << "---------------" << endl;

			for (int i = 0; i < 50; i++)
				cout << testArray2[i] << " ";

			cout << endl;
		}

		else
			cout << "Invalid input." << endl << endl;

	} while (true);
}
