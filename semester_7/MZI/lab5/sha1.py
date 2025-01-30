import struct


class SHA1:
    @staticmethod
    def hash(message_bytes):
        # 32 битные константы
        A = 0x67452301
        B = 0xEFCDAB89
        C = 0x98BADCFE
        D = 0x10325476
        E = 0xC3D2E1F0

        # Дополнение сообщения
        bytes_ = bytearray(message_bytes)
        bytes_.append(0x80)  # Добавление 1 в начале

        # Дополнение нулями до длины чтобы в конце осталось 64 бита
        while len(bytes_) % 64 != 56:
            bytes_.append(0x00)

        # Добавление длины исходного сообщения в битах
        message_length_bits = len(message_bytes) * 8

        # big-endian, по младшему адресу старший бит
        bytes_.extend(struct.pack('>Q', message_length_bits))

        # Разделение сообщения на блоки по 512 бит (64 байта)
        for i in range(0, len(bytes_), 64):
            # 80 32-битных слов
            W = [0] * 80

            # Первые 16 32-битных слов переносим
            for t in range(16):
                W[t] = struct.unpack('>I', bytes_[i + t * 4:i + t * 4 + 4])[0]

            # Дополнение массива до 80 слов
            for t in range(16, 80):
                W[t] = SHA1.rotate_left(W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16], 1)

            # Инициализация переменных для текущего блока
            a, b, c, d, e = A, B, C, D, E

            # Основной цикл обработки
            for t in range(80):
                if t < 20:
                    f = (b & c) | (~b & d)
                    k = 0x5A827999
                elif t < 40:
                    f = b ^ c ^ d
                    k = 0x6ED9EBA1
                elif t < 60:
                    f = (b & c) | (b & d) | (c & d)
                    k = 0x8F1BBCDC
                else:
                    f = b ^ c ^ d
                    k = 0xCA62C1D6

                temp = (SHA1.rotate_left(a, 5) + f + e + k + W[t]) & 0xFFFFFFFF
                e, d, c, b, a = d, c, SHA1.rotate_left(b, 30), a, temp

            # Добавление результатов к текущим переменным
            A = (A + a) & 0xFFFFFFFF
            B = (B + b) & 0xFFFFFFFF
            C = (C + c) & 0xFFFFFFFF
            D = (D + d) & 0xFFFFFFFF
            E = (E + e) & 0xFFFFFFFF

        hash_bytes = struct.pack('>5I', A, B, C, D, E)
        return hash_bytes

    # Циклический сдвиг влево
    @staticmethod
    def rotate_left(value, bits):
        return ((value << bits) | (value >> (32 - bits))) & 0xFFFFFFFF
