#pragma once

int input_natural();
int input_natural_z(); // +0
int input_int();
int input_int_pairs();
unsigned long long input_int_pairs_ll();
double input_double();

int** input_arr2_natural	(int** array, int& N, int& M);
int** input_arr2_int		(int** array, int& N, int& M);
double** input_arr2_double	(double** array, int& N, int& M);

int* input_arr1_natural		(int* array, int& N);
int* input_arr1_int			(int* array, int& N);
double* input_arr1_double	(double* array, int& N);