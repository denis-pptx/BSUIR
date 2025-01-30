import random
import numpy as np

from matrix import H, R


def hamming7_4_encode(input_str: str, G_hat: np.ndarray) -> np.ndarray:
    input_bits = np.array([int(bit) for bit in input_str])

    encoded_bits = np.mod(G_hat.dot(input_bits), 2)

    return encoded_bits


def hamming7_4_decode(encoded_bits: np.ndarray) -> np.ndarray:
    decoded_bits = np.mod(R.dot(encoded_bits), 2)

    return decoded_bits


def add_single_bit_error(encoded_bits: np.ndarray) -> np.ndarray:
    error_bits = [0] * 7

    error_index = random.randint(0, 6)

    error_bits[error_index] = 1

    corrupted_bits = np.mod(encoded_bits + error_bits, 2)

    return corrupted_bits


def detect_error(received_bits: np.ndarray) -> int:
    syndrome = np.mod(H.dot(received_bits), 2)

    err_index = int(''.join(str(bit) for bit in syndrome[::-1]), 2)

    return err_index - 1


def flip_bit(bits: np.ndarray, index: int) -> None:
    bits[index] = (bits[index] + 1) % 2