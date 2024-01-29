#include "pch.h"

// void Full_Check(char* str)
// переводит строку в простой английский


// Тесты из задания

TEST(Case1, Test4) {
	char* test = new char[100];
	strcpy(test, "Too swift for Theex, too quick for Gallow");
	char exp[] = "Tu svift for Ziks, tu kvik for Galov";

	Full_Check(test);
	EXPECT_STREQ(test, exp);
}

TEST(Case2, Test4) {
	char* test = new char[100];
	strcpy(test, "Too strong for young Prince Joseph to follow");
	char exp[] = "Tu strong for ung Prinse Josef to folov";

	Full_Check(test);
	EXPECT_STREQ(test, exp);
}


// c'X' -> s'X' 
// перед e, i, y

TEST(Case3, Test4) {
	char test[] = "ce";
	char exp[] = "se";

	Full_Check(test);
	EXPECT_STREQ(test, exp);
}

TEST(Case4, Test4) {
	char test[] = "ci";
	char exp[] = "si";

	Full_Check(test);
	EXPECT_STREQ(test, exp);
}

TEST(Case5, Test4) {
	char test[] = "cy";
	char exp[] = "sy";

	Full_Check(test);
	EXPECT_STREQ(test, exp);
}

// c'X' -> k'X'
// остальные случаи
TEST(Case6, Test4) {
	char alphabet[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v' };
	char test[] = "ca";
	char exp[] = "ka";

	for (int i = 0; i < 26; i++) {
		// первые три протестили, вторые три пойдут по другим кейсам изменяться
		if (alphabet[i] != 'e' && alphabet[i] != 'i' && alphabet[i] != 'y' && alphabet[i] != 'c' && alphabet[i] != 'k' && alphabet[i] != 'q') {
			test[0] = 'c';
			test[1] = alphabet[i];
			exp[1] = alphabet[i];

			Full_Check(test);
			EXPECT_STREQ(test, exp);
		}
	}
}



TEST(Case7, Test4) {
	// Макс

	char* test = new char[110];
	strcpy(test, "q qu w ph you oo ee th x apple ce ci cccccy youyou quvvvkxk phphphphphphph ththzzzphf vwoowv www qx");
	char exp[] = "k kv v f u u i z ks aple se si ksy uu kvksk f zf vuv v ks";

	Full_Check(test);
	EXPECT_STREQ(test, exp);
}

TEST(Case8, Test4) {
	// Макс + 1

	char* test = new char[110];
	strcpy(test, "qq qu w ph you oo ee th x apple ce ci cccccy youyou quvvvkxk phphphphphphph ththzzzphf vwoowv www qx");
	char exp[] = "k kv v f u u i z ks aple se si ksy uu kvksk f zf vuv v ks";

	Full_Check(test);
	EXPECT_STREQ(test, exp);
}


TEST(Case9, Test4) {
	// Макс - 1

	char* test = new char[110];
	strcpy(test, "qq qu w ph you oo ee th x apple ce ci ccccy youyou quvvvkxk phphphphphphph ththzzphf vwoowv www qx");
	char exp[] = "k kv v f u u i z ks aple se si ksy uu kvksk f zf vuv v ks";

	Full_Check(test);
	EXPECT_STREQ(test, exp);
}

TEST(Case10, Test4) {
	// Мин

	char* test = new char[10];
	strcpy(test, "q");
	char exp[] = "k";

	Full_Check(test);
	EXPECT_STREQ(test, exp);
}

TEST(Case11, Test4) {
	// Мин + 1

	char* test = new char[10];
	strcpy(test, "wv");
	char exp[] = "v";

	Full_Check(test);
	EXPECT_STREQ(test, exp);
}

TEST(Case12, Test4) {
	// Мин - 1

	char* test = new char[10];
	strcpy(test, "");
	char exp[] = "";

	Full_Check(test);
	EXPECT_STREQ(test, exp);
}



