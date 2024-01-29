# -*- coding: cp1251 -*-
import numpy


eps = 0.0001

def isMatrixSymmetric(matrix):
    for i in range(1, len(matrix)):
        for j in range(i):
            if matrix[i][j] != matrix[j][i]:
                return False
    return True




def CreateMatrix():

    k = 10

    C = numpy.array([
        [0.2, 0.0, 0.2, 0.0, 0.0],
        [0.0, 0.2, 0.0, 0.2, 0.0],
        [0.2, 0.0, 0.2, 0.0, 0.2],
        [0.0, 0.2, 0.0, 0.2, 0.0],
        [0.0, 0.0, 0.2, 0.0, 0.2]
    ])

    D = numpy.array([
        [2.33, 0.81, 0.67, 0.92, -0.53],
        [0.81, 2.33, 0.81, 0.67, 0.92],
        [0.67, 0.81, 2.33, 0.81, 0.92],
        [0.92, 0.67, 0.81, 2.33, -0.53],
        [-0.53, 0.92, 0.92, -0.53, 2.33]
    ])

    return k * C + D

def CreateMatrixTest():
    A = numpy.array([
        [1, 0, 0, 0],
        [0, 1, 0, 1],
        [0, 0, 1, 0],
        [0, 0, 0, 1]
    ])

    return A


def GetSumOfSqsFromNodiag(matrix):
    sum = 0.0

    for i in range(len(matrix)):
        for j in range(len(matrix)):
            if i != j:
                sum += matrix[i][j] ** 2

    return sum


def GetPosOfMaxFromNodiag(matrix):

    max = 0.0
    row = 0
    column = 0

    for i in range(len(matrix)):
        for j in range(i + 1, len(matrix)):
            if abs(matrix[i][j]) > max:
                max = abs(matrix[i][j])
                row = i
                column = j

    return row, column


def GetPhi(matrix, point):
    if matrix[point[0]][point[0]] == matrix[point[1]][point[1]]:
        return numpy.pi / 4
    else:
        p = 2 * matrix[point[0]][point[1]] / (matrix[point[0]][point[0]] - matrix[point[1]][point[1]])
    res = 0.5 * numpy.arctan(p)

    return res


def GetR(size, pos, phi):
    R = numpy.eye(size)
    R[pos[0]][pos[0]] = R[pos[1]][pos[1]] = numpy.cos(phi)
    R[pos[0]][pos[1]] = -numpy.sin(phi)
    R[pos[1]][pos[0]] = numpy.sin(phi)
    return R


def Jacobi(matrix):

    V = numpy.eye(len(matrix))

    while GetSumOfSqsFromNodiag(matrix) >= eps:

        posOfMax = GetPosOfMaxFromNodiag(matrix)

        phi = GetPhi(matrix, posOfMax)

        R = GetR(len(matrix), posOfMax, phi)

        V = V @ R

        matrix = R.T @ matrix @ R
    
    #print(matrix)
 
    eigenValues = []
    for i in range(len(matrix)):
        eigenValues.append(matrix[i][i])

    return numpy.array(eigenValues), V.T


def main():

    numpy.set_printoptions(precision = 4, suppress = True, floatmode = "fixed")

    A = CreateMatrix()

    print("Исходная матрица: \n", A)

    if (isMatrixSymmetric(A) != True):
        print("Матрица не является симметричной\nРешение методом Якоби невозможно")
    else:
        eigenValues, eigenVectors = Jacobi(A)
        print("\nСобственные значения: \n", eigenValues)
        print("\nСобственные векторы: \n", eigenVectors)
   

main()