
def input_measure(letter='x'):
    """
    Measure input.

    :param letter.
    :type letter: str.

    :return: Measure value.
    :rtype: float.
    """

    while True:
        try:
            print(f'{letter} = ', end='')
            x = float(input())

            if x < 0:
                raise ValueError(f'{letter} не может быть отрицательным')
        except Exception as ex:
            print(ex)
        else:
            return x


def calculate_square(a, b):
    """
    Square calculation.

    :param a.
    :type a: float.

    :param b.
    :type b: float.

    :return: Square.
    :rtype: float.
    """

    return a * b


def main():
    a = input_measure('a')
    b = input_measure('b')

    s = calculate_square(a, b)
    print(f'{s = }')


if __name__ == '__main__':
    main()

