# -*- coding: cp1251 -*-
import numpy as np
import matplotlib.pyplot as plt
from numpy.core.multiarray import dot
import math

Pi = math.pi

def input():

    x = [0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]
    p = [0.0, 0.41, 0.79, 1.13, 1.46, 1.76, 2.04, 2.3, 2.55, 2.79, 3.01]
    k = 11
    m = 2.53
    y = [ (p[i] + ((-1) ** k) * m) for i in range(len(x))]
    
    dots = list(zip(x, y))


    #dots = [(0, 1), (5, 5)] # �������� ������ 1
    
    #dots = [(0, -1), (1, -2), (3, 2)] # �������� ������ 2
    
    #dots = [(-5, 8), (-3, 7), (2, -2), (7, -3), (8, 5)] # �������� ������ 3
    
    #dots = [(-9, -3), (-7, 2), (-4, 1), (0, 9), (2, 15), (7, 9), (4, 2)] # �������� ������ 4
    
    #x = [0, Pi/4, Pi/2, 3*Pi/4, Pi] # �������� ������ 5
    #dots = []
    #for x in x:
    #    dots.append((x, np.sin(x)))

    #x = [1, np.e, np.e + 1, np.e + 2, np.e + 3] # �������� ������ 6
    #dots = []
    #for x in x:
    #    dots.append((x, np.log(x)))



    #dots = [(, ), ]
    #def f(x):
    #    return 1 / (1 + x**2)
    #SIZE = 6
    #dots = [(-5 + 10 * x / (SIZE - 1), f(-5 + 10 * x / (SIZE - 1))) for x in range(SIZE) ]


    return dots



# ��������� ��������
def Lagrange(dots):
    n = len(dots)                  # ����� �����
    (x, y) = map(list, zip(*dots)) # ������ X � Y ��������
    polynom = np.poly1d([0])       # polynom = 0
    for i in range(n):
        p = np.poly1d([1]) # p = 1
        for j in range(n):
            if j != i:     # ���������� j-��
                p *= np.poly1d([ 1, -x[j] ]) / (x[i] - x[j]) # p *= (X-Xj)/(Xi-Xj)
        polynom += y[i] * p                                  # polynom += P*Yi
    return polynom



# ����������� ��������
def DividedDifferences(x):
    n = len(x)
    diffs = [[None for j in range(n - i)] for i in range(n)]

    for i in range(n):
        diffs[i][0] = y[i]

    for j in range(1, n):
        for i in range(n - j):
            diffs[i][j] = ((diffs[i + 1][j - 1] - diffs[i][j - 1]) / (x[i + j] - x[i]))

    return diffs
    
# �����������
#def Inaccuracy(xs, xdot):
#    n = len(xs)
#    diffs = DividedDifferences(xs)
#    maxdiff = 0.0
#    for i in range(len(diffs)):
#        for j in range(len(diffs[i])):
#            maxdiff = max(maxdiff, abs(diffs[i][j]))
#
#    w = 1
#    for i in range(n):
#        w *= xdot - xs[i]
#
#    f = 1
#    for i in range(1, n+1 + 1):
#        f *= i
#
#    R = maxdiff * w / f
#    return R


# ��������� �������
def Newton(dots):
    n = len(dots)                  # ����� �����
    (x, y) = map(list, zip(*dots)) # ������ X � Y ��������

    diffs = DividedDifferences(x)  # ����������� ��������
    polynom = np.poly1d([0]) # polynom = 0
    for i in range(n):
        p = np.poly1d([1])   # p = 1
        for j in range(i):
            p *= np.poly1d([ 1, -x[j] ]) # p *= (X - Xj)
        polynom += p * diffs[0][i]       # polynom += p * fn(x0,..,xi)

    return polynom
    

# ��� ��� m == n
def Simple(dots):
    n = len(dots)
    (x, y) = map(list, zip(*dots))
    A = []
    for i in range(n):
        A.append([])
        for j in range(n):
            A[i].append(x[i] ** j)
    polynom = np.poly1d(np.linalg.solve(A, y)[::-1])
    return polynom

# ������������� ������� ���������� ���������
def Squares(dots, m = None):
    n = len(dots) - 1
    if m is None:
        m = n

    assert 0 <= m <= n
    if m == n:
        return Simple(dots)
    
    (x, y) = map(list, zip(*dots))
    
    b = []
    for k in range(m + 1):
        s = 0
        for i in range(n + 1):
            s += y[i] * (x[i] ** (m - k)) 
        b.append(s)

    A = []
    for k in range(m + 1):
        A.append([])

        for j in range(m + 1):
            s = 0
            for i in range(n + 1):
                s += x[i] ** (2 * m - k - j)
            A[k].append(s)

    polynom = np.poly1d(np.linalg.solve(A, b))
    return polynom

# ��� ��� ��������
#def SquaresCheck(dots, m = None):
#
#    n = len(dots) - 1
#    if m is None:
#        m = n
#    assert 0 <= m <= n
#    return np.poly1d(np.polyfit(*map(list, zip(*dots)), m))

# ����� �����������
def get_error(method, dots, m = None):

    (x, y) = map(list, zip(*dots))

    func = method(dots) - Squares(dots, m)
    der = np.polyder(func)

    max_error = 0.0
    for root in np.roots(der):
        if x[0] <= root <= x[-1]:
            max_error = max(max_error, abs(np.polyval(func, root)))

    return max_error

dots = input()
(x, y) = map(list, zip(*dots))
print("(x,y) =", dots, '\n')

lagrange = Lagrange(dots)
print("������� �������� =")
print(lagrange, '\n')

newton = Newton(dots)
print("������� ������� =")
print(newton, '\n')

squares = Squares(dots)
print("������� ��� =")
print(squares, '\n')

#sqrs = Squares(dots, 2)
#print("\n ������� ��� �� �������� = 2 \n")
#print(sqrs, '\n')


xdot = 0.47
#xdot = 3*Pi/8
#xdot = math.e + 0.5
width = 40

print(f"������� �������� ({xdot}) =".ljust(width), lagrange(xdot))
print(f"������� ������� ({xdot}) =".ljust(width), newton(xdot))
print(f"������� ��� ({xdot}) =".ljust(width), squares(xdot))
#print(f"������� ��� ({xdot}) =", "{:.4f}".format(squares(xdot)))

print("|������� - ������| =".ljust(width), abs(lagrange(xdot) - newton(xdot)))
print("|������� - ���| =".ljust(width), abs(lagrange(xdot) - squares(xdot)))
print("|������ - ���| =".ljust(width), abs(newton(xdot) - squares(xdot)))

print("����������� ������� (���. ���): ".ljust(width), get_error(Lagrange, dots))
print("����������� ������ (���. ���): ".ljust(width), get_error(Newton, dots))
#print(Inaccuracy(x, xdot))



plotdots = 10**4
plt.plot(x, y, 'og',markersize=10)

xplot = np.linspace(min(x), max(x), plotdots)

yplot = [squares(xdot) for xdot in xplot]
plt.plot(xplot, yplot, 'r',linewidth=4) # �������

yplot = [lagrange(xdot) for xdot in xplot]
plt.plot(xplot, yplot, 'b--',linewidth=4) # ������� �������

#yplot = [sqrs(xdot) for xdot in xplot]
#plt.plot(xplot, yplot, 'y') # Ƹ����

yplot = [newton(xdot) for xdot in xplot]
plt.plot(xplot, yplot, 'm:', linewidth=4) # ���������� �������


plt.show()

