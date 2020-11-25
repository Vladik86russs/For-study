#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

int BinarySearch(vector <int> mas, int digit, size_t start, size_t end)
{
	if (mas.empty()) throw invalid_argument ("mas is empty"); // throw exception
	if (end >= mas.size()) throw out_of_range("end is larger than massive size"); // throw exception
	if (start == end) // if interval length is one
	{
		if (digit == mas[start]) return start;
		else return -1;
	}
	int lLimit = start, rLimit = end, pos = (lLimit + rLimit) / 2; // set borders
	while (lLimit + 1 != rLimit) // while the borders is not closed
	{
		if (mas[pos] >= digit)
			rLimit = pos; // shifting right border
		else
			lLimit = pos; // shifting left border
		pos = (lLimit + rLimit) / 2; // shifting the main position
	}
	if (mas[lLimit] == digit) 
		return lLimit;
	else if (mas[rLimit] == digit)
		return rLimit;
	else
		return -1;
}

void QuickSort(vector <int>& mas, size_t lLimit, size_t rLimit)
{
	if (mas.empty()) throw invalid_argument("mas is empty"); // throw exception
	if (rLimit >= mas.size()) throw out_of_range("end is larger than massive size"); // throw exception
	if (lLimit == rLimit) return; // first base case
	else if (lLimit + 1 == rLimit) // second base case
	{
		if (mas[lLimit] > mas[rLimit])
			swap(mas[lLimit], mas[rLimit]);
		return;
	}
	size_t left = lLimit, right = rLimit; // set the borders
	size_t pivot = rand() % (rLimit + 1 - lLimit) + lLimit; // randomly set main position
	while (left + 1 < right) // loop for sorting by sides
	{
		for (int i = left; i < pivot; i++) // look for element that is larger than pivot
		{
			if (mas[i] > mas[pivot]) // if found then swap
			{
				swap(mas[i], mas[pivot]);
				pivot = i;
				break;
			}
			left++;
		}
		for (int i = right; i > pivot; i--) // look for element that is smaller than pivot
		{
			if (mas[i] < mas[pivot])
			{
				swap(mas[i], mas[pivot]); // if found then swap
				pivot = i;
				break;
			}
			right--;
		}
	}
	QuickSort(mas, lLimit, pivot); // sorting left side
	QuickSort(mas, pivot, rLimit); // sorting right side
}

void InsertionSort(vector <int>& mas, size_t start, size_t end)
{
	if (mas.empty()) throw invalid_argument("mas is empty"); // throw exception
	if (end >= mas.size()) throw out_of_range("end is larger than massive size"); // throw exception
	int position, digit;
	for (int i = start + 1; i <= end; i++) 
	{
		if (mas[i] < mas[i - 1])
		{
			digit = mas[i] + 1;
			do // loop for searching first element that is larger than current
			{
				position = BinarySearch(mas, digit, start, i - 1);
				digit++;
			} while (position == -1);
			mas.insert(mas.begin() + position, mas[i]); // moving current element before the found one
			mas.erase(mas.begin() + i + 1); 
		}
	}
}

bool isSorted(vector <int> mas, size_t start, size_t end)
{
	for (int i = start + 1; i <= end; i++)
		if (mas[i] < mas[i - 1]) return 0;
	return 1;
}

void BogoSort(vector <int>& mas, size_t start, size_t end)
{
	if (mas.empty()) throw invalid_argument("mas is empty"); // throw exception
	if (end >= mas.size()) throw out_of_range("end is larger than massive size"); // throw exception
	while (!isSorted(mas, start, end))
	{
		for (int i = start; i <= end; i++) // shuffling elements
		{
			size_t index = rand() % (end + 1 - start) + start;
			swap(mas[i], mas[index]);
		}
	}
}

void CountingSort(vector <unsigned char>& mas, size_t start, size_t end)
{
	if (mas.empty()) throw invalid_argument("mas is empty"); // throw exception
	if (end >= mas.size()) throw out_of_range("end is larger than massive size"); // throw exception
	vector <uint8_t> count(256); // supporting massive
	for (int i = start; i <= end; i++) // filling the massive
		count[mas[i]]++;
	size_t index = start;
	for (int i = 0; i < 256; i++) // writing int the cource massive
	{
		for (int j = 0; j < count[i]; j++)
		{
			mas[index] = i;
			index++;
		}
	}
}

void Print(vector <int> mas)
{
	for (int i = 0; i < mas.size(); i++)
		cout << " ( " << mas[i] << " ) ";
}

void Print(vector <unsigned char> mas)
{
	for (int i = 0; i < mas.size(); i++)
		cout << " " << mas[i] << " ";
}

void main()
{
	/*
	int timeStart, timeEnd, itime, qtime;
	for (int i = 0; i < 10; i++)
	{
		vector <vector <int>> result(2);
		srand(time(0));
		for (int j = 10; j <= 100000; j *= 10)
		{
			vector <int> mas, mas2;
			for (int q = 0; q < j; q++)
				mas.push_back(rand());
			mas2 = mas;
			timeStart = clock();
			InsertionSort(mas, 0, j - 1);
			timeEnd = clock();
			itime = timeEnd - timeStart;
			timeStart = clock();
			QuickSort(mas, 0, j - 1);
			timeEnd = clock();
			qtime = timeEnd - timeStart;
			result[0].push_back(itime);
			result[1].push_back(qtime);
		}
		cout << "  InsertionSort ";
		for (int i = 0; i < 5; i++)
			cout << "   |   " << result[0][i];
		cout << "   |\n";
		cout << "    QuickSort   ";
		for (int i = 0; i < 5; i++)
			cout << "   |   " << result[1][i];
		cout << "   |\n";
		cout << "___________________________________________________________\n";
	}
	*/
	/*srand(time(0));
	vector <int> mas, mas2;
	for (int i = 0; i < 100; i++)
		mas.push_back(rand());
	mas2 = mas;
	Print(mas);
	cout << "\n\nQuickSort:\n";
	QuickSort(mas, 0, 99);
	Print(mas);
	cout << "\n\nInsertionSort:\n";
	InsertionSort(mas2, 0, 99);
	Print(mas2); */
	/*vector <unsigned char> mas;
	for (int i = 0; i < 300; i++)
		mas.push_back(rand() % 256);
	Print(mas);
	CountingSort(mas, 0, 299);
	cout << "\n\nCountingSort:\n";
	Print(mas);*/
	/*vector <int> mas;
	for (int i = 0; i < 10; i++)
		mas.push_back(rand() % 20);
	Print(mas);
	cout << "\n\nBogoSort:\n";
	BogoSort(mas, 0, 9);
	Print(mas);*/
}