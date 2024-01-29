import re
from .constants import SENTENCE_END_SINGS, PUNCTUATION_SIGNS, NOT_SENTENCE_END_ABBREVIATIONS


def get_text() -> str:
    """Returns text from file / entry"""

    answer: str = ''
    while answer.strip() not in ['1', '2']:
        answer = input("1 - enter text \n"
                       "2 - read text from file \n"
                       "> ")

    if answer.strip() == '1':
        return input('Text: \n')

    while True:
        path: str = input("Path to the file with text: ")
        # path: str = r'/home/den/Studies/Denis_Konchik_153503_SCoI_term_4/Lab2/Task1/text/test.txt'

        try:
            with open(path, 'r') as file:
                return file.read()
        except Exception as ex:
            print(f"Error: {ex.args}")


def enter_n_k() -> tuple:
    """Handles input of integers: K and N"""

    print()
    print('Top-K repeated N-grams:')
    print('Enter K, N? (Y/N):', end=' ')

    k: int = 10
    n: int = 4
    ans: str = input()
    if ans == 'Y':
        print('K > 0, N > 0')

        while True:
            try:
                print('K =', end=' ')
                k = int(input())
                print('N =', end=' ')
                n = int(input())

                if k < 1 or n < 1:
                    raise Exception("Invalid K or N")

                break
            except Exception as ex:
                print(f'Error: {ex.args}')
    else:
        print(f'K = {k}')
        print(f'N = {n}')

    return k, n


def is_number(string: str) -> bool:
    """Checks if the string is a number"""

    try:
        float(string)
    except:
        return False

    return True


def get_words(sentence: str) -> list[str]:
    """Returns words from sentence"""

    return [word for word in re.findall(r'\b[\w]+\b', sentence)]


def remove_incorrect_characters(text: str) -> str:
    """Removes incorrect characters from text"""

    remove_pattern: str = '[^' + ''.join(map(re.escape, PUNCTUATION_SIGNS)) + r'a-zA-Z0-9\s]'
    new_text: str = re.sub(remove_pattern, '', text)

    return new_text


def get_sentences(text: str) -> list[str]:
    """Splits text into sentences"""

    def need_merging(sentence: str) -> bool:
        return sentence.lower().strip().endswith(
                tuple(map(lambda abbreviation: ' ' + abbreviation.lower().strip(), NOT_SENTENCE_END_ABBREVIATIONS))) or \
            sentence.lower().strip() in \
            tuple(map(lambda abbreviation: abbreviation.lower().strip(), NOT_SENTENCE_END_ABBREVIATIONS))

    # Example of the resulting regular expression:
    # \w.*?(?:!|\?|\.|\.\.\.)+(?=\s|$)
    pattern: str = r'\w.*?(?:' + '|'.join(map(re.escape, SENTENCE_END_SINGS)) + r')+(?=\s|$)'
    sentences: list[str] = re.findall(pattern, text, flags=re.DOTALL)

    # Take into consideration abbreviations.
    # Merge [1] and [2] if [1] ends with an abbreviation.
    sentences_with_abbreviations: list[str] = []

    i: int = 0
    while i < len(sentences):
        forming_sentence: str = sentences[i]

        while need_merging(forming_sentence) and i < len(sentences) - 1:
            i += 1
            forming_sentence += ' ' + sentences[i]

        i += 1
        sentences_with_abbreviations.append(forming_sentence)

    return sentences_with_abbreviations


def print_sentences(sentences: list[str], print_words=True) -> None:
    print()
    for sentence in sentences:
        if print_words:
            print(sentence, '#', get_words(sentence))
        else:
            print(sentence)

    print()


def print_n_grams(n_grams: list[(str, int)]) -> None:
    print()

    if not len(n_grams):
        print('List of N-grams is empty')
    else:
        for item in n_grams:
            print(item[0], ':', item[1])
