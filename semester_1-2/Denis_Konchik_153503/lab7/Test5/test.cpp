#include "pch.h"
#include <cstring>
using namespace std;

// string ToRoman(int)
// перевод в римскую из арабской

TEST(Case1, Task5) {
	EXPECT_EQ(ToRoman(0), "nulla");
}

TEST(Case2, Task5) {
	EXPECT_EQ(ToRoman(-1), "-I");
}

TEST(Case3, Task5) {
	EXPECT_EQ(ToRoman(2), "II");
}

TEST(Case4, Task5) {
	EXPECT_EQ(ToRoman(3), "III");
}

TEST(Case5, Task5) {
	EXPECT_EQ(ToRoman(4), "IV");
}

TEST(Case6, Task5) {
	EXPECT_EQ(ToRoman(5), "V");
}

TEST(Case7, Task5) {
	EXPECT_EQ(ToRoman(6), "VI");
}

TEST(Case8, Task5) {
	EXPECT_EQ(ToRoman(7), "VII");
}

TEST(Case9, Task5) {
	EXPECT_EQ(ToRoman(8), "VIII");
}

TEST(Case10, Task5) {
	EXPECT_EQ(ToRoman(9), "IX");
}

TEST(Case11, Task5) {
	EXPECT_EQ(ToRoman(10), "X");
}

TEST(Case12, Task5) {
	EXPECT_EQ(ToRoman(50), "L");
}

TEST(Case13, Task5) {
	EXPECT_EQ(ToRoman(100), "C");
}

TEST(Case14, Task5) {
	EXPECT_EQ(ToRoman(500), "D");
}

TEST(Case15, Task5) {
	EXPECT_EQ(ToRoman(1000), "(I)");
}

TEST(Case16, Task5) {
	EXPECT_EQ(ToRoman(222222222), "((CC))((XX))((II))(CC)(XX)(II)CCXXII");
}

TEST(Case17, Task5) {
	EXPECT_EQ(ToRoman(9876543210), "(((I)))((CC))((LXXX))((VI))(DC)(VIII)DCXVIII");
}

TEST(Case18, Task5) {
	EXPECT_EQ(ToRoman(123456789), "((C))((XX))((III))(CD)(L)(VI)DCCLXXXIX");
}
 

