#include "headers.h"

extern double precision;

vector<double> simpleIterations(Matrix<double> A, int& iterations) {

    // ������ �������
    int size = A.getRows();


    // ����������� �� ���������� ��������
    vector <double> prev_X(size, 0.0);

    // ���� �� ����� ���������� ��������
    bool stop = false;
    while (!stop)
    {
        ++iterations;
        // ����������� �� ������� ��������   
        vector <double> current_X(size);

        for (int i = 0; i < size; i++)
        {
            // x_i = b_i
            current_X[i] = A.at(i, size);

            // �������� ����� �� ���� �������� �� i-�� �����������
            for (int j = 0; j < size; j++)
            {
                // � ������ ��������
                if (j != i)
                    current_X[i] -= A.at(i, j) * prev_X[j];
            }

            // x_i /= b_i
            current_X[i] /= A.at(i, i);
        }

        // ������������ �����������
        long double max_error = 0.0;
        for (int i = 0; i < size; i++) {
            double new_max_error = abs(current_X[i] - prev_X[i]);
            max_error = new_max_error > max_error ? new_max_error : max_error;
        }

        // ��������� �� ��������
        if (max_error < precision)
            stop = true;


        // ������� � ��������� ��������
        prev_X = current_X;
    }


    return prev_X;

}

vector<double> seidelMethod(Matrix<double> A, int& iterations) {

    // ������ �������
    int size = A.getRows();
    

    // ����������� �� ���������� ��������
    vector <double> prev_X(size, 0.0);

    // ���� �� ����� ���������� ��������
    bool stop = false;
    while (!stop)
    {
        ++iterations;
        // ����������� �� ������� ��������   
        vector <double> current_X(size);

        for (int i = 0; i < size; i++)
        {
            // x_i = b_i
            current_X[i] = A.at(i,size);

            // �������� ����� �� ���� �������� �� i-�� �����������
            for (int j = 0; j < size; j++)
            {
                // � ���� ��������
                if (j < i) 
                    current_X[i] -= A.at(i, j) * current_X[j];
                
                // � ������ ��������
                if (j > i) 
                    current_X[i] -= A.at(i, j) * prev_X[j];
                
            }

            // x_i /= b_i
            current_X[i] /= A.at(i,i);
        }

        // ������������ �����������
        long double max_error = 0.0;
        for (int i = 0; i < size; i++) {
            double new_max_error = abs(current_X[i] - prev_X[i]);
            max_error = new_max_error > max_error ? new_max_error : max_error;
        }

        // ��������� �� ��������
        if (max_error < precision)
            stop = true;
        

        // ������� � ��������� ��������
        prev_X = current_X;
    }


    return prev_X;


}

