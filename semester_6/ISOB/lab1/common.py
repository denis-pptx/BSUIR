import re


def is_english_letters_only(string):
    return bool(re.match("^[A-Za-z]+$", string))

def caesar_encrypt(text: str, k):
    result = ''

    for x in text:
        y = x

        if is_english_letters_only(x):    
            if x.isupper():
                y = chr((ord(x) - ord('A') + k) % 26 + ord('A'))
            else:
                y = chr((ord(x) - ord('a') + k) % 26 + ord('a'))

        result += y

    return result


def caesar_decrypt(text, k):
    result = ''

    for y in text:
        x = y

        if is_english_letters_only(y):    
            if y.isupper():
                x = chr((ord(y) - ord('A') - k + 26) % 26 + ord('A'))
            else:
                x = chr((ord(y) - ord('a') - k + 26) % 26 + ord('a'))
                
        result += x

    return result


