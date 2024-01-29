import io
import os
import sys
import unittest
from unittest.mock import patch

import requests
from main import process_console, check_url, download_file


class TestProcessConsole(unittest.TestCase):
    def setUp(self):
        self.temp_output = io.StringIO()
        sys.stdout = self.temp_output

        self.original_argv = sys.argv

    def tearDown(self):
        self.temp_output.close()
        sys.stdout = sys.__stdout__

        sys.argv = self.original_argv

    @patch('sys.argv', ['script_name', 'http://example.com', '/path/to/folder'])
    def test_process_console_valid_args(self):
        url, folder_path = process_console()
        self.assertEqual(url, 'http://example.com')
        self.assertEqual(folder_path, '/path/to/folder')

    @patch('sys.argv', ['script_name', 'http://example.com'])
    def test_process_console_invalid_args(self):
        with self.assertRaises(SystemExit):
            process_console()


class TestCheckURL(unittest.TestCase):

    def test_valid_url(self):
        with patch('requests.head') as mock_head:
            mock_head.return_value.status_code = 200
            url = 'http://www.example.com'
            self.assertTrue(check_url(url))

    def test_invalid_url(self):
        with patch('requests.head') as mock_head:
            mock_head.return_value.status_code = 404
            url = 'http://www.invalid.com'
            self.assertFalse(check_url(url))

    def test_exception_handling(self):
        with patch('requests.head', side_effect=requests.exceptions.RequestException):
            url = 'http://www.example.com'
            self.assertFalse(check_url(url))


class TestDownloadFile(unittest.TestCase):
    def setUp(self):
        self.url = 'https://ru-ru.learn.canva.com/wp-content/uploads/sites/19/2020/07/paul-skorupskas-7KLa-xLbSXA-unsplash-2.jpg'
        self.folder_path = 'test_folder'

        if not os.path.exists(self.folder_path):
            os.mkdir(self.folder_path)

        self.temp_output = io.StringIO()
        sys.stdout = self.temp_output

    def tearDown(self):
        if os.path.exists(self.folder_path):
            for file_name in os.listdir(self.folder_path):
                file_path = os.path.join(self.folder_path, file_name)
                os.remove(file_path)
            os.rmdir(self.folder_path)

        self.temp_output.close()
        sys.stdout = sys.__stdout__

    def test_download_successful(self):
        download_file(self.url, self.folder_path)
        files = os.listdir(self.folder_path)
        self.assertEqual(len(files), 1)

    def test_download_error(self):
        invalid_url = 'https://www.bsuir.by.invalid.url'
        download_file(invalid_url, self.folder_path)
        files = os.listdir(self.folder_path)
        self.assertEqual(len(files), 0)


if __name__ == '__main__':
    unittest.main()
