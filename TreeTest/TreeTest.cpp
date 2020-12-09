#include "pch.h"
#include "CppUnitTest.h"
#include "..\BinaryTree\bTree.h"
#include "..\BinaryTree\bTree.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TreeTester
{
	TEST_CLASS(TreeTester)
	{
	public:

		TEST_METHOD(insertTest)
		{
			bTree tree;
			tree.insert(3);
			Assert::AreEqual(tree.contains(3), true);
			tree.insert(2);
			tree.insert(7);
			Assert::AreEqual(tree.contains(7), true);
			tree.remove(3);
			Assert::AreEqual(tree.contains(3), false);
			Assert::AreEqual(tree.contains(2), true);
			Assert::AreEqual(tree.contains(7), true);
			try
			{
				Iterator* iter = tree.create_dft_iterator();
			}
			catch (out_of_range ex)
			{
				Assert::AreEqual(ex.what(), "tree is empty");
			}
		}

		TEST_METHOD(removeTest)
		{
			bTree tree(5);
			tree.insert(3);
			tree.insert(7);
			Assert::AreEqual(tree.contains(5), true);
			Assert::AreEqual(tree.contains(3), true);
			Assert::AreEqual(tree.contains(7), true);
			tree.remove(3);
			Assert::AreEqual(tree.contains(5), true);
			Assert::AreEqual(tree.contains(3), false);
			Assert::AreEqual(tree.contains(7), true);
		}

		TEST_METHOD(containsTest)
		{
			bTree tree(1257);
			Assert::AreEqual(tree.contains(1257), true);
			Assert::AreEqual(tree.contains(4), false);
		}

		TEST_METHOD(bftTest)
		{
			bTree tree;
			try
			{
				Iterator* it = tree.create_bft_iterator();
			}
			catch (out_of_range ex)
			{
				Assert::AreEqual(ex.what(), "tree is empty");
			}
			int digitsForTree[] = { 8, 10, 3, 14, 1, 6, 7, 4, 13 };
			for (int i = 0; i < 9; i++)
				tree.insert(digitsForTree[i]);
			int digitsBft[] = { 8, 3, 10, 1, 6, 14, 4, 7, 13 };
			Iterator* it = tree.create_bft_iterator();
			for (int i = 0; i < 9; i++)
				Assert::AreEqual(it->next(), digitsBft[i]);
		}

		TEST_METHOD(dftTest)
		{
			bTree tree;
			try
			{
				Iterator* it = tree.create_dft_iterator();
			}
			catch (out_of_range ex)
			{
				Assert::AreEqual(ex.what(), "tree is empty");
			}
			int digitsForTree[] = { 8, 10, 3, 14, 1, 6, 7, 4, 13 };
			for (int i = 0; i < 9; i++)
				tree.insert(digitsForTree[i]);
			int digitsBft[] = { 8, 3, 1, 6, 4, 7, 10, 14, 13 };
			Iterator* it = tree.create_dft_iterator();
			for (int i = 0; i < 9; i++)
				Assert::AreEqual(it->next(), digitsBft[i]);
		}
	};
}
