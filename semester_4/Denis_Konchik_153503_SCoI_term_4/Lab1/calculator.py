import constants


def calculate(a, b, operation):
    if operation == constants.ADD:
        return a + b
    if operation == constants.SUB:
        return a - b
    if operation == constants.MULT:
        return a * b
    if operation == constants.DIV:
        return a / b

    raise Exception("Invalid operation")
