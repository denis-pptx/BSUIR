"""Tests for get_top_k_n_grams function"""

from ...src.statistics_functions import get_top_k_n_grams


def test_empty_text():
    texts: list[str] = ['', ' ', '          ']
    for text in texts:
        assert len(get_top_k_n_grams(text)) == 0


def test_mormal_text():
    text: str = 'A b c d. E f g a c. D e f g. A b c.'
    assert get_top_k_n_grams(text, 1, 5) == [('c d e f g', 2)]
    assert get_top_k_n_grams(text, 1, 6) == [('c d e f g a', 2)]
    assert get_top_k_n_grams(text, 1, 7) == [('a b c d e f g', 1)]
    assert get_top_k_n_grams(text, 2, 4) == [('c d e f', 2), ('d e f g', 2)]


