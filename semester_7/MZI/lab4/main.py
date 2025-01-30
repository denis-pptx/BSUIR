import numpy as np

from constants import SOURCE_PATH, ENCRYPTED_PATH, DECRYPTED_PATH
from matrix import G
from hamming import hamming7_4_encode, hamming7_4_decode, add_single_bit_error, detect_error, flip_bit


def generate_non_singular_binary_matrix(n: int) -> np.ndarray:
    while True:
        matrix: np.ndarray = np.random.randint(0, 2, size=(n, n))
        if np.linalg.det(matrix) != 0:
            return matrix


def generate_random_permutation_matrix(n: int) -> np.ndarray:
    perm_indices = np.random.permutation(n)

    permutation_matrix = np.zeros((n, n), dtype=int)
    for i in range(n):
        permutation_matrix[i, perm_indices[i]] = 1

    return permutation_matrix


def split_binary_string(binary_str: str, chunk_size: int) -> list[str]:
    return [binary_str[i:i + chunk_size] for i in range(0, len(binary_str), chunk_size)]


def bits_to_str(bits: str) -> str:
    byte_chunks = [bits[i:i + 8] for i in range(0, len(bits), 8)]

    characters = [chr(int(chunk, 2)) for chunk in byte_chunks]

    return ''.join(characters)


def input_with_default(prompt: str, default_value: str) -> str:
    return input(prompt) or default_value


def binary_string_to_bytes(binary_string: str) -> bytes:
    byte_chunks = [binary_string[i:i + 8] for i in range(0, len(binary_string), 8)]

    byte_array = bytearray(int(chunk, 2) for chunk in byte_chunks)

    return bytes(byte_array)


# k x k невырожденная матрица
S: np.ndarray = generate_non_singular_binary_matrix(4)
S_inv: np.ndarray = np.linalg.inv(S).astype(int)

# n x n матрица перестановки
P: np.ndarray = generate_random_permutation_matrix(7)
P_inv: np.ndarray = np.linalg.inv(P).astype(int)

G_hat = np.transpose(np.mod((S.dot(np.transpose(G))).dot(P), 2))


def main() -> None:
    source_file_path: str = input_with_default("Путь к файлу для шифрования: ", SOURCE_PATH)
    encrypted_file_path: str = input_with_default("Путь для зашифрованного файла: ", ENCRYPTED_PATH)
    decrypted_file_path: str = input_with_default("Путь для расшифрованного файла: ", DECRYPTED_PATH)

    with open(source_file_path, "rb") as file:
        input_bytes = file.read()

    print(f"Прочитан текст из [{source_file_path}]: {input_bytes}")

    binary_input: str = ''.join(f"{byte:08b}" for byte in input_bytes)
    binary_blocks: list[str] = split_binary_string(binary_input, 4)

    encrypted_blocks: list[str] = []

    for block in binary_blocks:
        encoded_block: np.ndarray = hamming7_4_encode(block, G_hat)
        corrupted_block: np.ndarray = add_single_bit_error(encoded_block)
        encoded_str: str = ''.join(str(bit) for bit in corrupted_block)
        encrypted_blocks.append(encoded_str)

    encrypted_data = ''.join(encrypted_blocks)

    with open(encrypted_file_path, "w", encoding="utf-8") as file:
        file.write(encrypted_data)

    print(f"Шифртекст записан в [{encrypted_file_path}]: {encrypted_data}")

    decoded_messages: list[str] = []
    for encrypted_block in encrypted_blocks:
        encrypted_bits: np.ndarray = np.array([int(bit) for bit in encrypted_block])

        c_hat: np.ndarray = np.mod(encrypted_bits.dot(P_inv), 2)

        error_index: int = detect_error(c_hat)
        flip_bit(c_hat, error_index)

        m_hat: np.ndarray = hamming7_4_decode(c_hat)
        m: np.ndarray = np.mod(m_hat.dot(S_inv), 2)

        decoded_str: str = ''.join(str(bit) for bit in m)
        decoded_messages.append(decoded_str)

    decoded_data: str = ''.join(decoded_messages)

    decoded_text: str = binary_string_to_bytes(decoded_data).decode('utf-8')

    with open(decrypted_file_path, "w", encoding="utf-8", newline='') as file:
        file.write(decoded_text)

    print(f"Расшифрованный текст записан в [{decrypted_file_path}]: {decoded_text}")


if __name__ == '__main__':
    main()
