import io
import os
import sys
import tempfile
import unittest

from main import process_console, find_files


class TestProcessConsole(unittest.TestCase):
    def setUp(self):
        self.temp_output = io.StringIO()
        sys.stdout = self.temp_output

        self.original_argv = sys.argv

    def tearDown(self):
        self.temp_output.close()
        sys.stdout = sys.__stdout__

        sys.argv = self.original_argv

    def test_invalid_args(self):
        sys.argv = ['main.py']
        with self.assertRaises(SystemExit) as context:
            process_console()
        self.assertEqual(context.exception.code, 1)

    def test_non_existing_path(self):
        self.argv = ['main.py', 'QWE&*(', 'py']
        with self.assertRaises(SystemExit) as context:
            process_console()
        self.assertEqual(context.exception.code, 1)

    def test_valid(self):
        sys.argv = ['main.py', '../Task5', 'py']
        folder, extension = process_console()

        self.assertEqual(folder, '../Task5')
        self.assertEqual(extension, 'py')


class TestFindFiles(unittest.TestCase):
    def setUp(self):
        self.test_dir = tempfile.mkdtemp()
        self.file1 = os.path.join(self.test_dir, 'file1.txt')
        self.file2 = os.path.join(self.test_dir, 'file2.txt')
        self.file3 = os.path.join(self.test_dir, 'file3.pdf')

        with open(self.file1, 'w') as f:
            f.write('Content1')

        with open(self.file2, 'w') as f:
            f.write('Content2')

        with open(self.file3, 'w') as f:
            f.write('Content3')

    def tearDown(self):
        os.remove(self.file1)
        os.remove(self.file2)
        os.remove(self.file3)
        os.rmdir(self.test_dir)

    def test(self):
        paths = find_files(self.test_dir, 'txt')
        self.assertEqual(len(paths), 2)
        self.assertIn(self.file1, paths)
        self.assertIn(self.file2, paths)
        self.assertNotIn(self.file3, paths)


if __name__ == '__main__':
    unittest.main()
