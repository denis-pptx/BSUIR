from constants import OP_LIST
from list_generator import generate_list, select_even_numbers
from calculator import calculate


print("Hello, World!")

try:
    print("\nAvailable operation names: ", OP_LIST)
    operation = input("Enter operation: ")

    print("Enter operands:")
    a = float(input("a = "))
    b = float(input("b = "))

    print("Result:", calculate(a, b, operation))
except Exception as e:
    print("Error: ", e.args)


length = input("\nEnter length of list: ")
if length.isdigit() and int(length) > 0:
    lst = generate_list(int(length))
    print("Generated list:      ", lst)
    print("List of even numbers:", select_even_numbers(lst))
else:
    print("Invalid list length")
