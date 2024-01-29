"""Tests for function get_words which splits sentence into words"""

from ...src.helpers import get_words


def test_empty_sentence():
    assert get_words('') == []
    assert get_words(' ') == []
    assert get_words('  ') == []


def test_normal_sentence():
    assert get_words("Hello, world!") == \
           ['Hello', 'world']

    assert get_words("I'm Denis from Minsk.") == \
           ['I', 'm', 'Denis', 'from', 'Minsk']

    assert get_words("This is a story about my uncle.") == \
           ['This', 'is', 'a', 'story', 'about', 'my', 'uncle']

    assert get_words("And guess what?") == \
           ['And', 'guess', 'what']

    assert get_words("There are 5 apples!") == \
           ['There', 'are', '5', 'apples']


def test_sentence_without_end_sign():
    assert get_words("We followed the list") == \
           ['We', 'followed', 'the', 'list']

    assert get_words("Hello, Denis") == \
           ['Hello', 'Denis']


def test_sentence_with_icorrect_symbols():
    assert get_words("&^^*^&^%&%&&^^&&^") == \
           []

    assert get_words("Hello, my &$ friend.") == \
           ['Hello', 'my', 'friend']

    assert get_words("A<@b#$c d%^e&*f") == \
           ['A', 'b', 'c', 'd', 'e', 'f']


def test_sentence_with_abbreviations():
    assert get_words("V.I.P. person is!!!") == \
        ['V', 'I', 'P', 'person', 'is']

    assert get_words("At 6 a.m.") == \
           ['At', '6', 'a', 'm']

    assert get_words("Is it Mr. Jones!?!?!?") == \
           ['Is', 'it', 'Mr', 'Jones']
