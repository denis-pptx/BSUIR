import os
import sys
import requests
from datetime import datetime


def process_console():
    """
    Processing of console.

    :return: Tuple with URL and folder path.
    :rtype: tuple(str, str).
    """

    if len(sys.argv) != 3:
        print("Использование: python main.py <URL> <Folder>")
        sys.exit(1)

    url = sys.argv[1]
    folder_path = sys.argv[2]

    return url, folder_path


def check_url(url):
    """
    Check if a URL exists by sending a HEAD request.

    :param url: The URL to check.
    :type url: str

    :return: True if the URL exists, False otherwise.
    :rtype: bool
    """
    try:
        response = requests.head(url)
        return response.status_code == 200
    except requests.exceptions.RequestException:
        return False


def download_file(url, folder_path):
    """
    Downloads a file from the provided URL and saves
    it to the specified folder.

    :param url: The URL to download the file from.
    :type url: str.

    :param folder_path: The path to the folder where the file should be saved.
    :type folder_path: str.

    :return: None.
    """

    try:
        response = requests.get(url)
        if response.status_code == 200:
            filename = os.path.join(folder_path, os.path.basename(url))
            with open(filename, 'wb') as file:
                file.write(response.content)
        else:
            print(f"Ошибка при загрузке файла. Код: {response.status_code}")
    except requests.exceptions.RequestException as e:
        print(f"Ошибка при загрузке файла: {e}")


def main():
    url, path = process_console()

    if not check_url(url):
        print('Некорректный URL')
    elif not os.path.exists(path):
        print('Несуществующий путь к папке')
    else:
        download_file(url, path)


if __name__ == '__main__':
    main()

