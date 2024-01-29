"""Tests for function is_number which defines if string is number"""

from ...src.helpers import is_number


def test_empty_string():
    assert is_number('') is False
    assert is_number(' ') is False
    assert is_number('  ') is False


def test_number():
    assert is_number('12345') is True
    assert is_number('1.2345') is True
    assert is_number('0') is True
    assert is_number('-12345') is True
    assert is_number('-1.2345') is True


def test_word():
    assert is_number('denis') is False
    assert is_number('d') is False


def test_combination():
    assert is_number('a1b2c3') is False
    assert is_number('111denis') is False
    assert is_number('denis3333') is False
