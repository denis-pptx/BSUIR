from gost3411 import GOST3411
from sha1 import SHA1


with open("input.txt", "rb") as file:
    message_bytes = file.read()

print(message_bytes.decode('utf-8'))
print(f"ГОСТ 34.11: {bytes(GOST3411.hash(message_bytes)).hex()}")
print(f"SHA-1: {bytes(SHA1.hash(message_bytes)).hex()}")
