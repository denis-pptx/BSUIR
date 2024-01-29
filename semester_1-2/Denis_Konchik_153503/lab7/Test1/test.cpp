#include "pch.h"

// void FourteenToTernary(char* fourteen, char* three)
// ������� �� 14 � 3 �������

TEST(Case1, Task1) {

    char three[100];
    char fourteen[100] = "0";

    FourteenToTernary(fourteen, three);
    ASSERT_STREQ(three, "0");
}


TEST(Case2, Task1) {

    char three[100];
    char fourteen[100] = "1234567890ABCD";

    FourteenToTernary(fourteen, three);
    ASSERT_STREQ(three, "11110201021222022101101012001120");
}

TEST(Case3, Task1) {

    char three[100];
    char fourteen[100] = "-1234567890ABCD";

    FourteenToTernary(fourteen, three);
    ASSERT_STREQ(three, "-11110201021222022101101012001120");
}