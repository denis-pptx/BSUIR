import io
import os
import re
import sys
import unittest
from unittest.mock import patch

from main import input_n, create_table


class TestInputMeasure(unittest.TestCase):
    def setUp(self):
        self.temp_output = io.StringIO()
        sys.stdout = self.temp_output

    def tearDown(self):
        self.temp_output.close()
        sys.stdout = sys.__stdout__

    @patch('builtins.input', side_effect=['5'])
    def test_input_positive(self, mock_input):
        result = input_n()
        self.assertEqual(result, 5)

    @patch('builtins.input', side_effect=['0'])
    def test_input_zero(self, mock_input):
        result = input_n()
        self.assertEqual(result, 0)

    @patch('builtins.input', side_effect=['-2', '-2jyt0', 'yreerh', '1gr2313', '5.5', '3'])
    def test_input_multiple(self, mock_input):
        result = input_n()
        self.assertEqual(result, 3)


class TestCreateTableFunction(unittest.TestCase):

    def test_create_table(self):
        file_path = 'table.html'
        create_table(10)

        self.assertTrue(os.path.exists(file_path))

        with open(file_path, "r", encoding="utf-8") as file:
            table_content = file.read()

        self.assertIn("<table>", table_content)
        self.assertIn("</table>", table_content)

        os.remove(file_path)

    def test_zero_rows(self):
        file_path = 'table.html'
        create_table(0)

        with open(file_path, "r", encoding="utf-8") as file:
            rows_count = file.read().count("<tr")
            self.assertEqual(rows_count, 0)

        os.remove(file_path)

    def test_not_zero_rows(self):
        file_path = 'table.html'
        create_table(10)

        with open(file_path, "r", encoding="utf-8") as file:
            rows_count = file.read().count("<tr")
            self.assertEqual(rows_count, 10)

        os.remove(file_path)

    def test_colors(self):
        file_path = 'table.html'
        create_table(10)

        with open(file_path, "r", encoding="utf-8") as file:
            table_content = file.read()

            colors = re.findall(r'rgb\((\d+.?\d+), (\d+.?\d+), (\d+.?\d+)\)', table_content)
            self.assertEqual(colors[0], ('255.0', '255.0', '255.0'))
            self.assertEqual(colors[-1], ('0.0', '0.0', '0.0'))

        os.remove(file_path)


if __name__ == '__main__':
    unittest.main()
