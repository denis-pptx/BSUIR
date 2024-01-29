#include "pch.h"
#include <cmath>
#define ll unsigned long long

// m = 10^t
// x = (k % m)^n % m.
// Case1-Case4 - данные из условия

TEST(Add2, Case1) {
	ll k = 1234, n = 1234, t = 4;
	ll m = (ll)1e4;

	EXPECT_EQ(Foo(k, n, m), 736);
}

TEST(Add2, Case2) {
	ll k = 2323, n = 99999999999, t = 8;
	ll m = (ll)1e8;

	EXPECT_EQ(Foo(k, n, m), 39087387);
}

TEST(Add2, Case3) {
	ll k = 4, n = 99999, t = 9;
	ll m = (ll)1e9;

	EXPECT_EQ(Foo(k, n, m), 494777344);
}

TEST(Add2, Case4) {
	ll k = 888, n = 888, t = 8;
	ll m = (ll)1e8;

	EXPECT_EQ(Foo(k, n, m), 91255296);
}

TEST(Add2, Case5) {
	// Макс
	ll k = (ll)1e19 - 1, n = (ll)1e19 - 1, t = 9;
	ll m = (ll)1e9;

	EXPECT_EQ(Foo(k, n, m), 921859071);
}

TEST(Add2, Case6) {
	// Макс - 1
	ll k = (ll)1e19 - 2, n = (ll)1e19 - 2, t = 8;
	ll m = (ll)1e8;

	EXPECT_EQ(Foo(k, n, m), 51872768);
}

TEST(Add2, Case7) {
	// Мин
	ll k = 1, n = 1, t = 1;
	ll m = (ll)1e1;

	EXPECT_EQ(Foo(k, n, m), 1);
}

TEST(Add2, Case8) {
	// Мин + 1
	ll k = 2, n = 2, t = 2;
	ll m = (ll)1e2;

	EXPECT_EQ(Foo(k, n, m), 4);
}