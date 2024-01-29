import random


def generate_list(length):
    lst = []
    for i in range(length):
        lst.append(random.randint(1, 100))

    return lst


def select_even_numbers(lst):
    result = []
    for number in lst:
        if number % 2 == 0:
            result.append(number)

    return result
