#include "pch.h"
#include <cstring>
using namespace std;

// int PATRICIAN(int N)
// определение номера отравленной бочки

TEST(CaseALL, Task10) {
	for (int i = 1; i <= 240; i++)
		EXPECT_EQ(PATRICIAN(i), i);
}