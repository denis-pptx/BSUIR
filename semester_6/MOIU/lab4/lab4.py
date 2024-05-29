import numpy as np


def basis_matrix(A: list, b: list) -> list:
    A_b = np.zeros((len(b), A.shape[0]))
    i = 0
    for k in b:
        for j in range(len(A)):
            A_b[j][i] = A[j][k-1]
        i += 1
    return A_b


def basis_vector(c: list, b: list) -> list:
    i = 0
    c_b = [0 for _ in b]
    for index in b:
        c_b[i] = c[index-1]
        i += 1
    return c_b


def main():
    A = np.array([
        [-2, -1, -4, 1, 0],
        [-2, -2, -2, 0, 1]
    ])
    B = [4, 5]
    c = np.array([-4, -3, -7, 0, 0])
    b = np.array([
        [-1],
        [-1.5]
    ])

    counter = 1
    while True:
        print()
        print('-' * 20 + 'Итерация ' + str(counter) + '-' * 20)
        
        print('1.')
        basis_A = basis_matrix(A, B) 
        print('Базисная матрица А: ', basis_A, sep='\n')
        basis_inverted_A = np.linalg.inv(basis_A)  
        print('Матрица, обратная базисной: ', basis_inverted_A, sep='\n')

        print('2.')
        basis_c = basis_vector(c, B)  
        print('Вектор, состоящий из компонент вектора с с базисными индексами из вектора В: ', basis_c, sep='')

        print('3.')
        y = np.matmul(basis_c, basis_inverted_A) 
        print('Базисный допустимый план двойственной задачи: ', y, sep='')

        print('4.')
        k_b = np.matmul(basis_inverted_A, b) 
        print('Компоненты псевдоплана с базисными индексами: ', k_b, sep='\n')
        j = 0
        k = [0, 0, 0, 0, 0]
        for item in B:
            k[item - 1] = k_b[j][0]
            j += 1  
        print('Псевдоплан k: ', k, sep='')

        print('5.')
        if all(x >= 0 for x in k):
            print('Оптимальный план задачи найден: ', k)
            break
        else:
            print('Это не оптимальный план задачи, k не >= 0')

        print('6.')
        negative_component = min(k)  
        print('Минимальный отрицательный элемент: ', negative_component, sep='')
        position_of_nefative_component = k.index(negative_component) + 1
        print('Индекс минимального отрицательного элемента псевдоплана: ', position_of_nefative_component, sep='')
        position_of_j = B.index(position_of_nefative_component) + 1  
        print('Индекс j: ', position_of_j, sep='')

        print('7.')
        delta_y = basis_inverted_A[position_of_j - 1] 
        print('j-ая строка матрицы A: ', delta_y, sep='')
        without_intersections = list(set([1, 2, 3, 4, 5]) - set(B))  
        print('Разность множеств [1, 2, 3, 4, 5] и B: ', without_intersections, sep='')
        M = [] 
        for item in without_intersections:
            m = np.matmul(delta_y, A[:, item - 1])
            M.append(m)
        print('Элементы вектора мю: ', M)
    
        print('8.')
        if (all([m >= 0 for m in M])):
            print('Задача не совместна, все µ >= 0')
        else:
            print('Задача совместна')

        print('9.')
        S = []
        for item, m in zip(without_intersections, M):
            item_s = (c[item - 1] - np.matmul(A[:, item - 1].transpose(), y)) / m
            S.append(item_s)
        print('Вектор σ: ', S)

        print('10.')
        mins = min(S)  
        print('Минимальный элемент вектора σ: ', mins, sep='')
        index_of_mins = S.index(mins) + 1  
        print('Индекс минимального элемента вектора σ: ', index_of_mins, sep='')

        print('11.')
        B[position_of_j - 1] = index_of_mins  
        print('Вектор В после замены элементов: ', B, sep='')
        counter += 1


if __name__ == "__main__":
    main()