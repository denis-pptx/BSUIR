import io
import sys
import unittest
from unittest.mock import patch

from main import people_input, people_output, Person, calculate_stats, output_stats


class TestPeopleInput(unittest.TestCase):
    def setUp(self):
        self.temp_output = io.StringIO()
        sys.stdout = self.temp_output

    def tearDown(self):
        self.temp_output.close()
        sys.stdout = sys.__stdout__

    def test_correct_values(self):
        with patch('builtins.input', side_effect=[
            'John', 'Doe', '30',
            'Jane', 'Smith', '25',
            'Alice', 'Johnson', '40',
            'Bob', 'Brown', '35',
            'Eva', 'Williams', '28',
            'stop'
        ]):
            people_list = people_input()
            self.assertEqual(len(people_list), 5)

    def test_empty_input(self):
        with patch('builtins.input', side_effect=[
            '', '', '', 'stop'
        ]):
            people_list = people_input()
            self.assertEqual(len(people_list), 0)

    def test_incorrect_values(self):
        with patch('builtins.input', side_effect=[
            'John', 'Doe', '-30',
            'Jane', 'Smith', '25312',
            'Alice', 'Johnson', 'fe',

            'Bob', 'Bro000wn', '35',
            'Bob', '132312', '35',
            'Alic34e', 'Williams', '28',
            '623', 'Williams', '28',

            'John', 'Doe', '30',
            'Jane', 'Smith', '25',
            'stop'
        ]):
            people_list = people_input()
            self.assertEqual(len(people_list), 2)


class TestPeopleOutput(unittest.TestCase):
    def test(self):
        people_list = [Person('John', 'Doe', 30), Person('Jane', 'Smith', 25),
                       Person('Denis', 'Konchik', 19)]
        expected_output = "Doe John 30\nSmith Jane 25\nKonchik Denis 19\n"

        with patch('sys.stdout', new_callable=io.StringIO) as output:
            people_output(people_list)
            actual_output = output.getvalue()

        self.assertEqual(actual_output, expected_output)


class TestCalculateStats(unittest.TestCase):
    def test_empty_list(self):
        with self.assertRaises(ValueError):
            calculate_stats([])

    def test_single_person(self):
        people_list = [Person('John', 'Doe', 30)]
        min_age, max_age, avg_age = calculate_stats(people_list)
        self.assertEqual(min_age, 30)
        self.assertEqual(max_age, 30)
        self.assertEqual(avg_age, 30.0)

    def test_multiple_people(self):
        people_list = [Person('John', 'Doe', 30), Person('Jane', 'Smith', 25),
                       Person('Denis', 'Konchik', 19)]
        min_age, max_age, avg_age = calculate_stats(people_list)
        self.assertEqual(min_age, 19)
        self.assertEqual(max_age, 30)
        self.assertEqual(avg_age, 24.67)


class TestOutputStats(unittest.TestCase):
    def test_output_stats(self):
        min_age = 19
        max_age = 30
        avg_age = 24.67

        expected_output = "Min: 19, max: 30, avg: 24.67\n"

        with patch('sys.stdout', new_callable=io.StringIO) as output:
            output_stats(min_age, max_age, avg_age)
            actual_output = output.getvalue()

        self.assertEqual(actual_output, expected_output)


if __name__ == '__main__':
    unittest.main()
