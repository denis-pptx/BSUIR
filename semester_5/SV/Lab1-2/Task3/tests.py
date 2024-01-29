import io
import sys
import unittest
from unittest.mock import patch
from main import input_measure, calculate_square


class TestInputMeasure(unittest.TestCase):
    def setUp(self):
        self.temp_output = io.StringIO()
        sys.stdout = self.temp_output

    def tearDown(self):
        self.temp_output.close()
        sys.stdout = sys.__stdout__

    @patch('builtins.input', side_effect=['5'])
    def test_input_positive(self, mock_input):
        result = input_measure()
        self.assertEqual(result, 5.0)

    @patch('builtins.input', side_effect=['0'])
    def test_input_zero(self, mock_input):
        result = input_measure()
        self.assertEqual(result, 0)

    @patch('builtins.input', side_effect=['-2', '-2jyt0', 'yreerh', '1gr2313', '3'])
    def test_input_multiple_(self, mock_input):
        result = input_measure()
        self.assertEqual(result, 3.0)


class TestCalculateSquare(unittest.TestCase):
    def test_positive_values(self):
        result = calculate_square(5, 4)
        self.assertEqual(result, 20)

    def test_one_zero_value(self):
        result = calculate_square(0, 8)
        self.assertEqual(result, 0)

    def test_both_zero_values(self):
        result = calculate_square(0, 0)
        self.assertEqual(result, 0)


if __name__ == '__main__':
    unittest.main()
