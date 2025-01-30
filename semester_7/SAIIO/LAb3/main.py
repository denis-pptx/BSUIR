from copy import deepcopy as dc
import numpy as np


def read() -> tuple:
    with open('input.txt', 'r') as file:
        A = [[float(i) for i in line.split()] 
             for line in file if line.strip()]

        P = len(A)
        Q = len(A[0]) - 1

    return P, Q, A


def forward(p, Q, A) -> tuple:
    B = [dc(A[0])]
    C = [[i for i in range(Q+1)]]
    for k in range(1, p):
        B.append([])
        C.append([])
        for q in range(Q+1):
            cur_max, cur_x = - np.inf, None
            for xk in range(0, q+1):
                if cur_max < B[k-1][q-xk] + A[k][xk]:
                    cur_x = xk
                cur_max = max(cur_max, B[k-1][q-xk] + A[k][xk])
            B[-1].append(cur_max)
            C[-1].append(cur_x)
    return B, C


def reverse(P, Q, C) -> list:
    gives, q_sum = [C[-1][-1]], C[-1][-1]
    for k in range(P-2, -1, -1):
        give = C[k][Q - q_sum]
        gives.append(give)
        q_sum += give

    return gives


if __name__ == '__main__':
    P, Q, A = read()

    B, C = forward(P, Q, A)

    print('B\n' + str(np.array(B)) + "\n")
    print('C:\n' + str(np.array(C)))

    answer = reverse(P, Q, C)
 
    print("Максимум прибыли: "  + str(B[-1][-1]))
    print("Распределение: " + str(answer[::-1]))