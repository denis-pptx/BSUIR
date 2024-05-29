from common import caesar_encrypt, caesar_decrypt


def main():
    file_name = "example.txt"

    try:
        with open(file_name, 'r', encoding='utf-8') as file:
            text = file.read()
    except FileNotFoundError:
        print(f"File '{file_name}' not found.")
        return

    print(f"Text from file:\n{text}")


    k = int(input("Input key (integer): "))
    action = input("Choose the action (encrypt - 'e', decrypt - 'd'): ").lower()

    if action == 'e':
        result = caesar_encrypt(text, k)
        print(f"Encrypted text:\n{result}")
    elif action == 'd':
        result = caesar_decrypt(text, k)
        print(f"Decrypted text:\n{result}")
    else:
        print("Incorrect action. Choose 'e' or 'd'.")


if __name__ == "__main__":
    main()
