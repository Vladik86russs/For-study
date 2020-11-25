#include "pch.h"
#include "CppUnitTest.h"
#include "../sorts/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SortTest
{
	TEST_CLASS(SortTest)
	{
	public:
		TEST_METHOD(Binary_Search)
		{
			vector <int> mas;
			for (int i = 0; i < 1000; i++)
				mas.push_back(i);
			for (int i = 0; i < 1000; i += 15)
				Assert::AreEqual(i, BinarySearch(mas, i, 0, 999));
			Assert::AreEqual(-1, BinarySearch(mas, 1001, 0, 999));
			try
			{
				BinarySearch(mas, 15, 0, 1000);
			}
			catch (out_of_range ex)
			{
				Assert::AreEqual(ex.what(), "end is larger than massive size");
			}
			mas.clear();
			try
			{
				BinarySearch(mas, 23, 0, 999);
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual(ex.what(), "mas is empty");
			} 
		}

		TEST_METHOD(Bogo_Sort)
		{
			vector <int> mas;
			for (int i = 9; i >= 0; i--)
				mas.push_back(i);
			BogoSort(mas, 0, 9);
			for (int i = 0; i < 10; i++)
				Assert::AreEqual(mas[i], i);
			try
			{
				BogoSort(mas, 0, 11);
			}
			catch (out_of_range ex)
			{
				Assert::AreEqual(ex.what(), "end is larger than massive size");
			}
			mas.clear();
			try
			{
				BogoSort(mas, 0, 1);
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual(ex.what(), "mas is empty");
			}
		}

		TEST_METHOD(Counting_Sort)
		{
			vector <unsigned char> mas;
			for (int i = 255; i >= 0; i--)
				mas.push_back(i);
			CountingSort(mas, 0, 255);
			for (int i = 0; i < 256; i++)
				Assert::AreEqual((int)mas[i], i);
			try
			{
				CountingSort(mas, 0, 256);
			}
			catch (out_of_range ex)
			{
				Assert::AreEqual(ex.what(), "end is larger than massive size");
			}
			mas.clear();
			try
			{
				CountingSort(mas, 0, 1);
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual(ex.what(), "mas is empty");
			}
		}

		TEST_METHOD(Insertion_Sort)
		{
			vector <int> mas;
			for (int i = 999; i >= 0; i--)
				mas.push_back(i);
			InsertionSort(mas, 0, 999);
			for (int i = 0; i < 1000; i++)
				Assert::AreEqual(mas[i], i);
			try
			{
				InsertionSort(mas, 0, 1000);
			}
			catch (out_of_range ex)
			{
				Assert::AreEqual(ex.what(), "end is larger than massive size");
			}
			mas.clear();
			try
			{
				InsertionSort(mas, 0, 1);
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual(ex.what(), "mas is empty");
			}
		}

		TEST_METHOD(Quick_Sort)
		{
			vector <int> mas;
			for (int i = 999; i >= 0; i--)
				mas.push_back(i);
			QuickSort(mas, 0, 999);
			for (int i = 0; i < 1000; i++)
				Assert::AreEqual(mas[i], i);
			try
			{
				QuickSort(mas, 0, 1000);
			}
			catch (out_of_range ex)
			{
				Assert::AreEqual(ex.what(), "end is larger than massive size");
			}
			mas.clear();
			try
			{
				QuickSort(mas, 0, 1);
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual(ex.what(), "mas is empty");
			}
		}
	};
}
