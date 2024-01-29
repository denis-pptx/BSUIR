#include "pch.h"
#include <cstring>
#include <string>

// double FuncSum(string str)
// сумма чисел в строке

TEST(Case1, Test9) {
	string str = "123";
	EXPECT_EQ(FuncSum(str), 123);
}

TEST(Case2, Test9) {
	string str = "abcdef";
	EXPECT_EQ(FuncSum(str), 0);
}

TEST(Case3, Test9) {
	string str = "123.3";
	EXPECT_EQ(FuncSum(str), 123.3);
}

TEST(Case4, Test9) {
	string str = ".............";
	EXPECT_EQ(FuncSum(str), 0);
}

TEST(Case5, Test9) {
	string str = "1.1.1.1.1.1.1.1.1.1.1.1.1";
	EXPECT_EQ(FuncSum(str), 7.6);
}

TEST(Case6, Test9) {
	string str = "khrtkktrk2.2.2.3.4..3.55.1.4.grlglerger0gerger0g0ege0r.0.....000..0.45.301flr9";
	EXPECT_EQ(FuncSum(str), 323.9);
}

TEST(Case7, Test9) {
	string str = "17e2e4e1e1e1e1e2e2e3e2e2e2e3kgtgtgjtg";
	EXPECT_EQ(FuncSum(str), 6050);
}

TEST(Case8, Test9) {
	string str = "1e+-+-+-++++-4";
	EXPECT_EQ(FuncSum(str), 10000);
}

TEST(Case9, Test9) {
	string str = "aaaa1e+--1g1------------------4";
	EXPECT_EQ(FuncSum(str), 15);
}

TEST(Case10, Test9) {
	string str = "-=-=-=-.+-+-+-+-1.7e--+1";
	EXPECT_EQ(FuncSum(str), 17);
}







