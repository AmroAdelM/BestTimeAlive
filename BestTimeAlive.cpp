// BestTimeAlive.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "gtest/gtest.h"

#define FILE_PATH "dataset.txt"
#define ARBITRARY_RANGE 3

std::map<int, int> readFileIntoYears(std::string aFilePath)
{
	// unordered_map is faster to search and insert in
	// but it doesn't give the ability to check for "most recent years", hence: unordered
	std::map<int, int> years;
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

int getRangeofMaxAlive(std::map<int, int> aYears, int aRange)
{
	auto maxSum = aYears.rbegin()->second;
	auto year = aYears.rbegin()->first;

	// reverse iterating to get most recent first
	for (auto it = aYears.rbegin(); it != aYears.rend(); it++)
	{
		int sumYears = 0;
		for (int n = 0; n < aRange; n++)
		{
			// to make sure we don't go out of range and also 
			if (aYears.count(it->first - n) > 0)
			{
				sumYears += aYears[it->first - n];
			}
		}

		if (sumYears > maxSum)
		{
			year = it->first;
			maxSum = sumYears;
		}
	}

	return year;
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
	std::map<int, int> testData;
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
	std::map<int, int> testData;
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
	std::map<int, int> testData;
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
	std::map<int, int> testData;
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
	std::map<int, int> testData;
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
	std::map<int, int> testData;
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
	std::map<int, int> testData;
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
	std::map<int, int> testData;
	testData[1993] = 7;
	testData[1992] = 6;
	testData[1991] = 6;
	testData[1990] = 4;
	testData[1989] = 6;
	testData[1988] = 6;
	testData[1987] = 7;
	EXPECT_EQ(getRangeofMaxAlive(testData, 2), 1993);
}