import re
import constants


class Person:
    def __init__(self, first_name, last_name, age):
        self.first_name = first_name
        self.last_name = last_name
        self.age = age

    def __repr__(self):
        return f'{self.last_name} {self.first_name} {self.age}'


def people_input():
    """
    Input of people.

    :return: List of people.
    :rtype: list[Person].
    """

    people_list = []

    while True:
        try:
            first_name = input("Введите имя (или 'stop' для завершения ввода): ")
            if first_name == 'stop':
                break

            if not re.fullmatch(constants.FIRST_NAME_EXPRESSION, first_name):
                raise ValueError('Некорректное имя')

            last_name = input("Введите фамилию: ")
            if not re.fullmatch(constants.FIRST_NAME_EXPRESSION, last_name):
                raise ValueError('Некорректная фамилия')

            age = int(input("Введите возраст: "))
            if age < 0 or age > 130:
                raise ValueError('Некорректный возраст')

            person = Person(first_name, last_name, age)
            people_list.append(person)

        except Exception as ex:
            print(f'Ошибка: {ex}')

        print()

    return people_list


def people_output(people_list):
    """
    Print list of people.

    :param people_list: List of people.
    :type people_list: list[Person].
    """

    for human in people_list:
        print(human)


def calculate_stats(people_list):
    """
    Calculates stats about people (ages)

    :param people_list: List of people.
    :type people_list: list[Person]

    :return: Statistics about ages.
    :rtype: tuple(int, int, float)
    """

    if len(people_list) == 0:
        raise ValueError('Список людей пуст')
    else:
        min_age = min(people_list, key=lambda x: x.age).age
        max_age = max(people_list, key=lambda x: x.age).age
        avg_age = round(sum(person.age for person in people_list) / len(people_list), 2)

        return min_age, max_age, avg_age


def output_stats(min_age, max_age, avg_age):
    """
    Stats output

    :return: Nothing.
    :rtype: None.
    """
    print(f'Min: {min_age}, max: {max_age}, avg: {avg_age}')


def main():
    people = people_input()

    print('\nСписок людей:')
    people_output(people)

    try:
        output_stats(*calculate_stats(people))
    except Exception as ex:
        print(ex)


if __name__ == '__main__':
    main()

