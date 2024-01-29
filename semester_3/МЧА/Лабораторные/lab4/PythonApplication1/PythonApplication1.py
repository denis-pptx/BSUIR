# -*- coding: cp1251 -*-
import numpy
import sympy


m = 0.2
a = 0.9

iters = 0
EPS = 10.0 ** -4

# Исходные уравнения в формате f(x,y) = 0
(x, y) = sympy.symbols("x y")
eq1 = sympy.tan(x * y + m) - x
eq2 = a * (x ** 2) + 2 * (y ** 2) - 1

print("Система нелинейных уравнений:")
print(eq1, "= 0")
print(eq2, "= 0")
print()

# Вычисление исходных уравнений: f1(x,y), f2(x,y)
def val1(x, y):
    return numpy.tan(x * y + m) - x
def val2(x, y):
    return a * (x ** 2) + 2 * (y ** 2) - 1

# Вычисление из исходных уравнений: x = phi(x,y), y = phi(x,y)
def eqx(x, y):
    return numpy.tan(x * y + m)
#def eqy(x, y):
 #   return numpy.sqrt((1 - a * (x ** 2)) / 2)
def eqy(x, y):
    return a * x**2 + 2*y**2-1+y;
# Вычисление матрицы Якоби
def J(x, y):
    return numpy.array([
        [(1 + numpy.tan(x * y + m) ** 2) * y - 1, (1 + numpy.tan(x * y + m) ** 2) * x],
        [2 * a * x, 4 * y]
    ])


# Графики исходных уравнений
l = 2
plots = sympy.plot_implicit(sympy.Eq(eq1, 0), (x, -l, l), (y, -l, l), line_color = "blue", show = False)
plots.extend(sympy.plot_implicit(sympy.Eq(eq2, 0), (x, -l, l), (y, -l, l), line_color = "red", show = False))
    
# Метод простых итераций
def SimpleIterations(x0, y0):
    global iters
    iters = 0
    (x, y) = (x0, y0)
    while True:
        iters += 1
        oldx = x
        oldy = y
        x = eqx(x, y)
        y = eqy(x, y)
        if (not (numpy.isfinite(x) and numpy.isfinite(y))):
            raise RuntimeError("Последовательность {x} расходящаяся")
        if (max(abs(x - oldx), abs(y - oldy)) < EPS):
            return (x, y)

# Метод Ньютона
def NewtonMethod(x0, y0):
    global iters
    iters = 0
    (x, y) = (x0, y0)
    while True:
        iters += 1
        j = J(x, y)
        f = numpy.array([[val1(x, y)], [val2(x, y)]])
        deltas = numpy.linalg.solve(j, -f)
        x += deltas[0][0]
        y += deltas[1][0]
        if (not (numpy.isfinite(x) and numpy.isfinite(y))):
            raise RuntimeError("Последовательность {x} расходящаяся")
        if (max(abs(deltas)) < EPS):
            return (x, y)


x0 = 0.5 
y0 = 0.5
print("Начальное приближение: \n(x0, y0) = ", (x0, y0))
print()

def solute(method):
    global iters
    try:
        (x, y) = method(x0, y0)
        print(f"{method.__name__} (итераций: {iters})")
        print(f"(x, y) = ({x:.4f}, {y:.4f})")
    except Exception as ex:
        print(f"Ошибка: {ex} - в {method.__name__} (итераций: {iters})")
    print()

SimpleIterations.__name__ = "Метод простых итераций"
NewtonMethod.__name__ = "Метод Ньютона"
solute(SimpleIterations)
#solute(NewtonMethod)

plots.show()

