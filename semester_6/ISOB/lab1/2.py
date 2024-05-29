from common import caesar_encrypt, caesar_decrypt, is_english_letters_only


def adjust_key(text: str, key: str):
    extended_key = key
    while len(extended_key) < len(text):
        extended_key += key

    return extended_key[:len(text)]


def main():
    file_name = "example.txt"

    try:
        with open(file_name, 'r', encoding='utf-8') as file:
            text = file.read()
    except FileNotFoundError:
        print(f"File '{file_name}' not found.")
        return

    print(f"Text from file:\n{text}")

    key = input("Input key (string): ")

    if is_english_letters_only(key):
        key = adjust_key(text, key)

        action = input("Choose the action (encrypt - 'e', decrypt - 'd'): ").lower()

        result = ''

        if action == 'e':
            for i in range(len(text)):
                result += caesar_encrypt(text[i], ord(key[i]) - ord('A'))

            print(f"Encrypted text:\n{result}")
        elif action == 'd':
            for i in range(len(text)):
                result += caesar_decrypt(text[i], ord(key[i]) - ord('A'))

            print(f"Decrypted text:\n{result}")
        else:
            print("Incorrect action. Choose 'e' or 'd'.")
    else:
        print("Key is incorrect. Use only caps english letters.")



if __name__ == "__main__":
    main()
