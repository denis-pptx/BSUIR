"""
Tests for remove_incorrect_characters function which
removes incorrect characters from text
"""

from ...src.helpers import remove_incorrect_characters


def test_empty_text():
    assert remove_incorrect_characters('') == ''
    assert remove_incorrect_characters('          ') == '          '
    assert remove_incorrect_characters('                ') == '                '


def test_normal_text():
    text: str = 'But in the morning when I woke up, I realised they were only dreams.'
    assert remove_incorrect_characters(text) == text

    text: str = \
        """
        After a few seconds, I heard it splash into the water deep below.
        I spent the rest of the day helping out on the farm. I fed the geese, 
        I picked some fruit and I dug up some potatoes.
        """
    assert remove_incorrect_characters(text) == text


def test_text_with_incorrect_characters():
    original_text: str = \
        """
        After a few seconds, I heard it splash into the water d@^&@^&@^&eep below.
        I spent the rest of the da<><><>><<>y helping out on the farm. @^&I fed the geese, 
        I picked some fruit and I dug up some #@potatoes. That night I fell asleep 
        the mome~~~~~~~~nt my head touched the pill#@#@#ow. I had so№№№№№№№№me magical dreams...
        But in the morning when I woke up, I realised they were only dreams.
        It was hard work. How I wi&&^&&&shed my wish would start working.~~~~~~~~
        """
    result_text: str = \
        """
        After a few seconds, I heard it splash into the water deep below.
        I spent the rest of the day helping out on the farm. I fed the geese, 
        I picked some fruit and I dug up some potatoes. That night I fell asleep 
        the moment my head touched the pillow. I had some magical dreams...
        But in the morning when I woke up, I realised they were only dreams.
        It was hard work. How I wished my wish would start working.
        """
    assert remove_incorrect_characters(original_text) == result_text
