

# ��������� Y �� ������ � X 
def CalculateY(method, x, eps):
    n = 1 # ���������� ����� �� x0 �� x ��� �������� eps

    while True:
        y_list = method(x, n)
        y_list_correctly = method(x, n * 2)
        max_delta = max(abs(y_list_correctly[2 * i] - y_list[i]) for i in range(n + 1)) 

        if (max_delta < eps):
            return round(y_list_correctly[-1], 6), n * 2
        else:
            n *= 2

# ������� ������ Y �� ������ � ������ X
def CalculateListY(method, x_list, eps):
    y_list = [] # ������ �������
    n_list = [] # ������ n (����� �����) ��� ������ �����
    for x in x_list:
        y, n = CalculateY(method, x, eps)
        y_list.append(y)
        n_list.append(n)

    return y_list, max(n_list), sum(n_list) / len(x_list)
