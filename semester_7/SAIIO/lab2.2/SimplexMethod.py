from hmac import new
from math import inf
import numpy as np
from matrixInversion import MyMatrixInversion

def MySimplexMethodStartPhase(c: np.ndarray, A: np.ndarray, b: np.ndarray):
# step 1
    negative_index = b < 0
    A[negative_index] *= -1
    b[negative_index] *= -1
    #print("\nA")
    #print(A)
    #print("\nb")
    #print(b)
# step 2
    m, n = A.shape
    
    c_wave = np.zeros(n + m)
    c_wave[n:] = -1
    #print("\nC_Wave")
    #print(c_wave)
    
    identity_matrix = np.eye(m)
    A_wave = np.hstack((A, identity_matrix))
    #print("\nA_Wave")
    #print(A_wave)
    
# step 3
    x_wave = np.zeros(n + m)
    x_wave[n:] = b[:]
    #print("\nx_wave")
    #print(x_wave)
    
    B = [i + n for i in range(1, m + 1)]
    #print("\nB")
    #print(B)
    
# step 4
    x_wave, B = MySimplexMethodMainPhase(c_wave, x_wave, A_wave, B)
    #print("\nx_wave")
    #print(x_wave)
    #print("\nB")
    #print(B)
    
# step 5
    if np.any(x_wave[n] > 0):
        raise Exception("problem is not feasible")
    
# step 6
    x = x_wave[:n]
    #print("\nx")
    #print(x)
    
    while True:
# step 7
        
        if all(bi <= n for bi in B):
            return x, B, A, b
        
# step 8
        j_k = max(B)
        k = B.index(j_k) + 1
        #print("\nj_k")
        #print(j_k)
        
        #print("\nk")
        #print(k)
        
# step 9
        j_NB = [i+1 for i in range(n) if all(bi - 1 != i for bi in B)]
        #print("\nj_NB")
        #print(j_NB)
        
        A_B = A_wave[:, np.array(B) - 1]
        A_B_inverted = np.linalg.inv(A_B)
        #print("\nA_B_inverted")
        #print(A_B_inverted)
        
        l = [(j, A_B_inverted.dot(A_wave[:, j - 1])) for j in j_NB]
        #print("\nl")
        #print(l)

# step 10
        found = False
        for j,l_j in l:
            if l_j[k-1] != 0:
                found = True
                B[k - 1] = j

# step 11
        if not found:
            i = j_k - n
            
            A = np.delete(A, i - 1, axis=0)
            b = np.delete(b, i - 1)
            B = np.delete(B, k - 1)
            A_wave = np.delete(A_wave, i - 1, axis=0)


def MySimplexMethodMainPhase(c: np.ndarray, x: np.ndarray, A: np.ndarray, B: np.ndarray):
    Is_First_Lap = True
    new_index = 0
    new_column = A[new_index]
    m = A.shape[0]
    iteration = 1
    
    while True:
        #print(f'-----------ITERATION N{iteration}---------------')
        #step 1
        A_B = A[:, np.array(B) - 1]
        
        #print ('A base')
        #print (A_B)
        #print('\n')
        
        if Is_First_Lap:
            A_I_B= np.linalg.inv(A_B)
        else:
            A_I_B= MyMatrixInversion(A_I_B, new_column, new_index)
        
        if (A_I_B is None):
            #print('couldnt inverse matrix')
            return
        
        #print('A base inverted')
        #print(A_I_B)
        #print('\n')
            
        #step 2
        c_B = c[np.array(B) - 1]
        
        #print('c with base indexes')
        #print(c_B)
        #print('\n')
        
        #step 3
        u = c_B.dot(A_I_B)
        
        #print('u')
        #print(u)
        #print('\n')
        
        #step 4
        delta = u.dot(A) - c
        
        #print('estimates vector')
        #print(delta)
        #print('\n')
        
        #step 5
        if np.all(delta >= 0):
            #print('found optimal plan')
            return x, B
        
        #step 6
        j0 = (delta < 0).argmax() + 1
        
        #print('index of first negative number')
        #print(j0)
        #print('\n')
        
        #step 7
        z = A_I_B.dot(A[:,j0 - 1])
        
        #print('z')
        #print(z)
        #print('\n')
        
        #step 8-9(didn't create whole vector because it's unnecessary)
        teta0 = inf
        k = -1
        for i in range(m):
            if z[i] > 0 and teta0 > x[int(B[i] - 1)] / z[i] :
                teta0 = x[int(B[i] - 1)] / z[i]    
                k = i + 1
            else:
                teta0
            
        
        #print('teta0')
        #print(teta0)
        #print('\n')
        
        #step 10
        if teta0 == inf:
            #print('objective function is not limited from above on a set of acceptable plans')
            return
        
        #step 11
        j_Star = B[k-1]
        
        #print('k')
        #print(k)
        #print('\n')
        #print('j_Star')
        #print(j_Star)
        #print('\n')
        
        #step 12
        B[k-1] = j0
        
        #step 13
        for i in range (m):
            x[int(B[i] - 1)] = x[int(B[i] - 1)] - teta0*z[i] if i != k-1 else x[int(B[i] - 1)]
            
        x[j_Star - 1] = 0
        x[j0 - 1] = teta0
        #print('x')
        #print(x)
        #print('\n')
            
        
        
        new_index = k
        new_column = A[:,B[k-1] - 1]
        Is_First_Lap = False
        iteration+=1
    

