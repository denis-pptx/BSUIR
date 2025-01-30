import numpy as np
from lab2 import gomory_restriction

if __name__ == "__main__":
    A = np.array([[3, 2, 1, 0],
                  [-3, 2, 0, 1]])
    
    c = np.array([0, 1, 0, 0])
    b = np.array([6, 0])    
    gomory_restriction(c,A,b)
