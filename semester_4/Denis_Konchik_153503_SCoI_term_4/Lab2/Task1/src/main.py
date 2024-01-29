import sys
sys.path.append(".")
from src.helpers import get_text, get_sentences, print_sentences, print_n_grams, enter_n_k, remove_incorrect_characters
from src.statistics_functions import get_number_of_sentences, get_number_of_non_declarative_sentences, \
    get_average_length_of_sentence, get_average_length_of_word, get_top_k_n_grams


if __name__ == '__main__':

    text = remove_incorrect_characters(get_text())
    print_sentences(get_sentences(text))

    print("Sentences:", get_number_of_sentences(text))
    # print("Declarative sentences:", get_number_of_declarative_sentences(text))
    print("Non-declarative sentences:", get_number_of_non_declarative_sentences(text))

    print("Average length of sentence: ", round(get_average_length_of_sentence(text), 2))
    print("Average length of word: ", round(get_average_length_of_word(text), 2))

    k, n = enter_n_k()
    print_n_grams(get_top_k_n_grams(text, k=k, n=n))

