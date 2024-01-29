"""
Tests for get_number_of_sentences function which
calculates number of sentences in text
"""

from ...src.statistics_functions import get_number_of_sentences


def test_empty_text():
    texts: list[str] = ['', ' ', '          ']
    for text in texts:
        assert get_number_of_sentences(text) == 0


def test_zero_sentences():
    texts: list[str] = ["It's Denis qwe, ",
                        "One sentence",
                        "At 6 a.m",
                        "1 2 3 4 5"]
    for text in texts:
        assert get_number_of_sentences(text) == 0


def test_one_sentence():
    texts: list[str] = ["It's Mr. Denis...!?.?!?!....??!",
                        "One sentence...",
                        "At 6 a.m!!!??!?!?",
                        "At 126 a.m.",
                        "At 126 a.m!"]

    for text in texts:
        assert get_number_of_sentences(text) == 1


def test_normal_text():
    text: str = \
        """
        After a few seconds, I heard it splash into the water deep below.
        I spent the rest of the day helping out on the farm. I picked some fruit 
        and I dug up some potatoes. That night I fell asleep the moment my head 
        touched the pillow. But in the morning when I woke up, I realised they were 
        only dreams. It was hard work. How I wished my wish would start working.
        """

    assert get_number_of_sentences(text) == 7


def test_text_with_abbreviations():
    text: str = \
        """
        Hello, Mr. Denis. At 8 a.m. we will go to school!!
        One Mr Denis bla bla. Mrs. Denis bla bla. Ms. Denis bla bla. 
        My Miss. Denis bla bla. It is Jr. Denis bla bla. Sr. Denis bla?!?!?
        """
    assert get_number_of_sentences(text) == 8
