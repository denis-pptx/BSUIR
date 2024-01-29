import constants


def input_n():
    """
    Natural number (plus zero) input.
    
    :return: n.
    :rtype: int >= 0.
    """
    
    while True:
        try:
            print('n = ', end='')
            x = int(input())

            if x < 0:
                raise ValueError('n не может быть отрицательным')
        except Exception as ex:
            print(ex)
        else:
            return x


def create_table(n):
    """
    Creates table whit gradient.

    :param n: Number of rows in table.
    :type n: int.

    :return: Nothing.
    :rtype: None.
    """
    
    with open("table.html", "w", encoding="utf-8") as file:
        file.write(constants.HTML_START)

        file.write('<table>\n')
        for i in range(n):
            color_value = 255 - i * 255 / (n - 1)
            color = f"rgb({color_value}, {color_value}, {color_value})"

            file.write(f"<tr style='background-color:{color};'>\n")
            file.write("<td></td>\n")
            file.write("</tr>\n")

        file.write("</table>\n")

        file.write(constants.HTML_END)


def main():
    n = input_n()
    create_table(n)


if __name__ == '__main__':
    main()

