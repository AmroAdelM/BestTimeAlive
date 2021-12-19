#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "gtest/gtest.h"

#define FILE_PATH "dataset.txt"
#define ARBITRARY_RANGE 3

std::unordered_map<int, int> readFileIntoYears(std::string aFilePath)
{
	std::unordered_map<int, int> years;
	std::ifstream myfile;
	std::string line;

	myfile.open(aFilePath);
	while (std::getline(myfile, line))
	{
		std::string birth_str = line.substr(1, 4);
		std::string death_str = line.substr(6, 4);

		int birth_year = birth_str == "    " ? 0 : atoi(birth_str.c_str());
		int death_year = death_str == "    " ? 1993 : atoi(death_str.c_str());

		for (auto it = birth_year; it <= death_year; it++)
		{
			// add 1 if it didn't exist in map befoe, or increase count if exists
			years[it]++;
		}
	}
	myfile.close();
	return years;
}

// returns -1 if a failure of search or if range is bigger than count 
int getRangeofMaxAlive(std::unordered_map<int, int> aYears, int aRange)
{
	if (aRange > aYears.size())
	{
		return -1;
	}

	auto maxSum = 0;
	auto foundYear = -1;

	// reverse iterating to get most recent first
	for (int iterator = 1993; iterator > 0; iterator--)
	{
		int sumYears = 0;
		for (int n = 0; n < aRange; n++)
		{
			// to make sure we don't insert unreferenced year in map
			if (aYears.count(iterator - n) > 0)
			{
				sumYears += aYears[iterator - n];
			}
		}

		if (sumYears > maxSum)
		{
			foundYear = iterator;
			maxSum = sumYears;
		}
	}

	return foundYear;
}

int main()
{
	auto years = readFileIntoYears(FILE_PATH);
	auto startYearWithMax = getRangeofMaxAlive(years, ARBITRARY_RANGE);

	std::cout << "range of years with max composers alive are :" << std::endl;

	// reverse iterating to show older year first
	for (int n = ARBITRARY_RANGE - 1; n >= 0; n--)
	{
		std::cout << startYearWithMax - n << std::endl;
	}

	::testing::InitGoogleTest();
	//RUN_ALL_TESTS();
	return 0;
}

TEST(TEST_METHOD, Test1RangeAtEnd) {
	std::unordered_map<int, int> testData;
	testData[1993] = 7;
	testData[1992] = 6;
	testData[1991] = 5;
	testData[1990] = 4;
	testData[1989] = 6;
	testData[1988] = 5;
	testData[1987] = 4;
	EXPECT_EQ(getRangeofMaxAlive(testData, 1), 1993);
}

TEST(TEST_METHOD, Test2RangeAtEnd) {
	std::unordered_map<int, int> testData;
	testData[1993] = 7;
	testData[1992] = 6;
	testData[1991] = 5;
	testData[1990] = 4;
	testData[1989] = 6;
	testData[1988] = 5;
	testData[1987] = 4;
	EXPECT_EQ(getRangeofMaxAlive(testData, 2), 1993);
}

TEST(TEST_METHOD, Test3RangeAtEnd) {
	std::unordered_map<int, int> testData;
	testData[1993] = 7;
	testData[1992] = 6;
	testData[1991] = 6;
	testData[1990] = 4;
	testData[1989] = 6;
	testData[1988] = 5;
	testData[1987] = 4;
	EXPECT_EQ(getRangeofMaxAlive(testData, 3), 1993);
}

TEST(TEST_METHOD, Test1RangeAtBegining) {
	std::unordered_map<int, int> testData;
	testData[1993] = 6;
	testData[1992] = 6;
	testData[1991] = 5;
	testData[1990] = 4;
	testData[1989] = 6;
	testData[1988] = 5;
	testData[1987] = 7;
	EXPECT_EQ(getRangeofMaxAlive(testData, 1), 1987);
}

TEST(TEST_METHOD, Test2RangeAtBegining) {
	std::unordered_map<int, int> testData;
	testData[1993] = 7;
	testData[1992] = 4;
	testData[1991] = 5;
	testData[1990] = 4;
	testData[1989] = 6;
	testData[1988] = 5;
	testData[1987] = 7;
	EXPECT_EQ(getRangeofMaxAlive(testData, 2), 1988);
}

TEST(TEST_METHOD, Test3RangeAtBegining) {
	std::unordered_map<int, int> testData;
	testData[1993] = 7;
	testData[1992] = 6;
	testData[1991] = 5;
	testData[1990] = 4;
	testData[1989] = 6;
	testData[1988] = 6;
	testData[1987] = 7;
	EXPECT_EQ(getRangeofMaxAlive(testData, 3), 1989);
}

TEST(TEST_METHOD, Test2Range_MostRecentOnly) {
	std::unordered_map<int, int> testData;
	testData[1993] = 7;
	testData[1992] = 6;
	testData[1991] = 5;
	testData[1990] = 4;
	testData[1989] = 5;
	testData[1988] = 6;
	testData[1987] = 7;
	EXPECT_EQ(getRangeofMaxAlive(testData, 2), 1993);
}

TEST(TEST_METHOD, Test3Range_MostRecentOnly) {
	std::unordered_map<int, int> testData;
	testData[1993] = 7;
	testData[1992] = 6;
	testData[1991] = 6;
	testData[1990] = 4;
	testData[1989] = 6;
	testData[1988] = 6;
	testData[1987] = 7;
	EXPECT_EQ(getRangeofMaxAlive(testData, 2), 1993);
}
TEST(TEST_METHOD, Test1RangeWithOnly1Year) {
	std::unordered_map<int, int> testData;
	testData[1993] = 7;
	EXPECT_EQ(getRangeofMaxAlive(testData, 1), 1993);
}

TEST(TEST_METHOD, Test2RangeWithOnly1Year) {
	std::unordered_map<int, int> testData;
	testData[1993] = 7;
	EXPECT_EQ(getRangeofMaxAlive(testData, 2), -1);
}

TEST(TEST_METHOD, TestYearOutOfRange) {
	std::unordered_map<int, int> testData;
	testData[1994] = 7;
	EXPECT_EQ(getRangeofMaxAlive(testData, 1), -1);
}