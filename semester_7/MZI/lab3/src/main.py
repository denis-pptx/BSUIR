import random
from sympy import isprime
from typing import Tuple, Optional
import os

from constants import SOURCE_PATH, ENCRYPTED_PATH, DECRYPTED_PATH, KEYS_PATH, OPEN_KEY_LENGTH


def generate_rabin_keys(bit_size: int = 256) -> Tuple[int, int, int]:
    def find_prime() -> int:
        while True:
            candidate: int = random.getrandbits(bit_size)
            if isprime(candidate) and candidate % 4 == 3:
                return candidate

    p: int = find_prime()
    q: int = find_prime()

    return p * q, p, q


def encrypt(message: str, n: int) -> int:
    m: int = int.from_bytes(message.encode('utf-8'), byteorder='big')

    if not (m < n):
        raise ValueError("Должно выполняться условие m < n при шифровании")

    c: int = pow(m, 2, n)

    return c


def decrypt(c: int, p: int, q: int) -> str:
    n: int = p * q

    r: int = pow(c, (p + 1) // 4, p)
    s: int = pow(c, (q + 1) // 4, q)

    # px + qy = 1
    _, x, y = extended_euclid(p, q)

    m1: int = (x * p * s + y * q * r) % n
    m2: int = n - m1
    m3: int = (x * p * s - y * q * r) % n
    m4: int = n - m3

    i = 0
    for mi in [m1, m2, m3, m4]:
        i += 1
        try:
            return mi.to_bytes((mi.bit_length() + 7) // 8, 'big').decode('utf-8')
        except UnicodeDecodeError:
            continue

    raise ValueError("Не смогли преобразовать c в m")


# nod(a,b) = ax + by
def extended_euclid(a: int, b: int) -> Tuple[int, int, int]:
    if a == 0:
        return b, 0, 1

    nod, prev_x, prev_y = extended_euclid(b % a, a)

    current_x = prev_y - (b // a) * prev_x
    current_y = prev_x

    return nod, current_x, current_y


def read_file(file_path: str) -> str:
    if not os.path.exists(file_path):
        with open(file_path, 'w', encoding='utf-8'):
            pass
    with open(file_path, 'r', encoding='utf-8') as f:
        return f.read()


def write_file(file_path: str, data: str) -> None:
    with open(file_path, 'w', encoding='utf-8') as f:
        f.write(data)


def display_menu() -> str:
    print()
    print("1. Сгенерировать n,p,q")
    print("2. Зашифровать файл")
    print("3. Расшифровать файл")
    print("q. Выйти")

    print()
    user_choice: str = input("Действие (номер): ")
    return user_choice


def input_with_default(prompt: str, default_value: str) -> str:
    return input(prompt) or default_value


n: Optional[int] = None
p: Optional[int] = None
q: Optional[int] = None


def main() -> None:
    actions: dict = {
        "1": lambda: generate_keys(),
        "2": lambda: encrypt_file(),
        "3": lambda: decrypt_file(),
        "q": lambda: exit_program(),
    }

    while True:
        selected_action: str = display_menu()
        action = actions.get(selected_action)

        if action:
            action()
        else:
            print("Неверный выбор. Пожалуйста, попробуйте снова.")


def generate_keys() -> None:
    bits: int = int(input_with_default("Введите размер ключа: ", OPEN_KEY_LENGTH))
    global n, p, q
    n, p, q = generate_rabin_keys(bits)
    write_file(KEYS_PATH, f"n: {n}\np: {p}\nq: {q}")
    print(f"Ключи размером {bits} бит сгенерированы и сохранены в {KEYS_PATH}.")


def encrypt_file() -> None:
    global n
    if n is None:
        print("N is None")
        return
    file_path: str = input_with_default("Путь к файлу для шифрования: ", SOURCE_PATH)
    try:
        message: str = read_file(file_path)
        ciphertext: int = encrypt(message, n)
        enc_file_path: str = input_with_default("Путь для зашифрованного файла: ", ENCRYPTED_PATH)
        write_file(enc_file_path, str(ciphertext))
        print(f"Файл {file_path} зашифрован и сохранен как {enc_file_path}")
    except Exception as e:
        print(f"Ошибка при шифровании: {e}")


def decrypt_file() -> None:
    global p, q
    if p is None or q is None:
        print("p or q is None")
        return
    file_path: str = input_with_default("Путь к файлу для расшифрования: ", ENCRYPTED_PATH)
    try:
        ciphertext: int = int(read_file(file_path))
        message: str = decrypt(ciphertext, p, q)
        dec_file_path: str = input_with_default("Путь для расшифрованного файла: ", DECRYPTED_PATH)
        write_file(dec_file_path, message)
        print(f"Файл {file_path} расшифрован и сохранен как {dec_file_path}")
    except Exception as e:
        print(f"Ошибка: {e}")


def exit_program() -> None:
    print("exit")
    exit()


if __name__ == "__main__":
    main()
