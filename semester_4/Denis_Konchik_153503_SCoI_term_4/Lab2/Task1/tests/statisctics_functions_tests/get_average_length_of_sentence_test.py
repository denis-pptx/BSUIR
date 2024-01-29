"""
Tests for get_average_length_of_sentence function which
calculates average length of sentence in characters (words count only)
"""

from ...src.statistics_functions import get_average_length_of_sentence


def test_empty_text():
    texts: list[str] = ['', ' ', '          ']
    for text in texts:
        assert get_average_length_of_sentence(text) == 0


def test_zero_sentences():
    texts: list[str] = ["It's Denis qwe It is second It is third",
                        "One sentence bla bla bla",
                        "At 6 a.m",
                        "1 2 3 4 5 q we r ty"]
    for text in texts:
        assert get_average_length_of_sentence(text) == 0


def test_normal_text():

    text: str = "After a few sec12onds, I 567 heard it splash into the water deep below."
    assert round(get_average_length_of_sentence(text), 2) == round(53 / 1, 2)

    text: str = "After a fe32w seconds, I heard098 it splash 123 into the 45.23 water de2ep below. \
                I spen32t the r9est o0000f 00 the day 999 helping out on the farm."
    assert round(get_average_length_of_sentence(text), 2) == round(104 / 2, 2)

    text: str = "I picked 642 some f512ruit and a.m. I dug up some po321tatoes. \
                That night 1I 532fell 12.34 asleep Mr. Denis the moment my head 53512512 touched the pillow. \
                But in the12 morning when I 645325 w532oke up, I realised they were only dreams."
    assert round(get_average_length_of_sentence(text), 2) == round(165 / 3, 2)
