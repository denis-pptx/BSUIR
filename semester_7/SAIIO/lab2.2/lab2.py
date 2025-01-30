import numpy as np

from SimplexMethod import MySimplexMethodStartPhase
from SimplexMethod import MySimplexMethodMainPhase
from matrixInversion import MyMatrixInversion


def gomory_restriction(c: np.ndarray, A: np.ndarray, b: np.ndarray):
    # step 1
    x, B, _, _ = MySimplexMethodStartPhase(c, A, b)
    x, B = MySimplexMethodMainPhase(c, x, A, B)

    print('x:')
    print(x)
    print('\n')

    # Step 2
    if np.all(np.floor(x) == x):
        return x

    # Step 3
    for index, value in enumerate(x):
        if not np.isclose(value, np.round(value)): 
            i = index
            val = value
            break

    k = B.index(i + 1) 

    print('k')
    print(k)
    print('\n')

    # Step 4
    A_B = A[:, [b - 1 for b in B]] 
    non_base_indices = [j for j in range(A.shape[1]) if j + 1 not in B]
    A_N = A[:, non_base_indices] 

    print('A_B')
    print(A_B)
    print('\n')

    print('A_N')
    print(A_N)
    print('\n')

    # Step 5
    x_B = x[[b - 1 for b in B]]  # Elements from x with base indexes
    x_N = x[non_base_indices]    # Elements from x with non-base indexes

    print('x_B')
    print(x_B)
    print('\n')

    print('x_N')
    print(x_N)
    print('\n')

    # Step 6
    A_B_inv = np.linalg.inv(A_B)  

    # Step 7
    Q = np.dot(A_B_inv, A_N)  
    print('Q')
    print(Q)
    print('\n')

    # Step 8
    l = Q[k]  
    print('Row l (k-th row of Q)')
    print(l)
    print('\n')

    # Step 9
    coeffs = np.zeros_like(x)
    for idx, nb_idx in enumerate(non_base_indices):
        coeffs[nb_idx] = l[idx]

    print('Coeffs')
    print(coeffs)
    print('\n')

    free_variable = val - np.floor(val)

    print('Free variable')
    print(free_variable)
    print('\n')

    return (coeffs, free_variable)
