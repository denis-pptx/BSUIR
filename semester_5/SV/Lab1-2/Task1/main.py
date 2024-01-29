import random


def print_text():
    """
    Output of two lines

    :return: Nothing.
    :rtype: None
    """

    print('Hello, world!')
    print('Andhiagain!')


def print_exclamation():
    """
    Output of a random number of
    exclamation marks (from 5 to 50)

    :return: Nothing.
    :rtype: None
    """

    print("!" * random.randint(5, 50))


if __name__ == '__main__':
    print_text()
    print_exclamation()


