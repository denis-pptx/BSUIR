import sys
import unittest
from io import StringIO

from main import print_text, print_exclamation


class TestPrintText(unittest.TestCase):
    def setUp(self):
        self.str_output = StringIO()
        sys.stdout = self.str_output

    def tearDown(self):
        self.str_output.close()
        sys.stdout = sys.__stdout__

    def test(self):
        print_text()

        self.str_output.seek(0)
        output = self.str_output.read().strip().split('\n')

        self.assertEqual(output[0], 'Hello, world!')
        self.assertEqual(output[1], 'Andhiagain!')


class TextPrintExclamation(unittest.TestCase):
    def setUp(self):
        self.str_output = StringIO()
        sys.stdout = self.str_output

    def tearDown(self):
        self.str_output.close()
        sys.stdout = sys.__stdout__

    def test(self):
        print_exclamation()

        self.str_output.seek(0)
        output = self.str_output.read().strip()

        self.assertTrue(5 <= len(output) <= 50)
        self.assertEqual(output.count('!'), len(output))


if __name__ == '__main__':
    unittest.main()
