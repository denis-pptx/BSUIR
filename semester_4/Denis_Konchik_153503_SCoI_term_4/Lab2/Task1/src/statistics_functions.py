import re
from .constants import SENTENCE_END_SINGS
from .helpers import get_words, get_sentences, is_number


def get_number_of_sentences(text: str) -> int:
    return len(get_sentences(text))


def get_number_of_declarative_sentences(text: str) -> int:

    # Example of the resulting regular expression:
    # (?:\!|\?|\.|\.\.\.)+(?=$)
    signs_group_pattern: str = r'(?:' + '|'.join(tuple(map(re.escape, SENTENCE_END_SINGS))) + r')+(?=$)'

    sentences: list[str] = [sentence.strip() for sentence in get_sentences(text)]
    count: int = 0

    for sentence in sentences:
        sign_group: str = str(re.search(signs_group_pattern, sentence))
        if not ('!' in sign_group or '?' in sign_group):
            count += 1

    return count


def get_number_of_non_declarative_sentences(text: str) -> int:
    return get_number_of_sentences(text) - get_number_of_declarative_sentences(text)


def get_average_length_of_sentence(text: str) -> float:
    total_sentences_length: int = 0
    sentences: list[str] = get_sentences(text)

    for sentence in sentences:
        words = [word for word in get_words(sentence) if not is_number(word)]
        # print(sentence, ":", words)

        for word in words:
            total_sentences_length += len(word)

    if len(sentences):
        return total_sentences_length / len(sentences)
    else:
        return 0


def get_average_length_of_word(text: str) -> float:
    words_number: int = 0
    total_words_length: int = 0
    sentences: list[str] = get_sentences(text)

    for sentence in sentences:
        words = [word for word in get_words(sentence) if not is_number(word)]
        words_number += len(words)
        # print(sentence, ":", words)

        for word in words:
            total_words_length += len(word)

    if words_number:
        return total_words_length / words_number
    else:
        return 0


def get_top_k_n_grams(text: str, k: int = 10, n: int = 4) -> list[(str, int)]:

    word_matrix: list[list[str]] = [get_words(sentence) for sentence in get_sentences(text)]
    words: list[str] = []
    for row in word_matrix:
        words.extend(row)

    words_str = ' '.join(words).lower()
    n_grams_dict: dict[str, int] = {}

    for i in range(len(words) - n + 1):
        # substr: str = ' '.join(words[i:(i + n)]).lower()
        # n_grams_dict[substr] = words_str.count(substr)
        substr: str = ' '.join(words[i:(i + n)]).lower()
        n_grams_dict[substr] = len(re.findall(r'\b' + substr + r'\b', words_str))

    n_grams_lst = [(key, value) for key, value in n_grams_dict.items()]
    n_grams_lst = sorted(n_grams_lst, key=lambda item: item[1], reverse=True)[:k]

    return n_grams_lst
