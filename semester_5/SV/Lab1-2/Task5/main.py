import os
import sys


def process_console():
    """
    Processing of console.

    :return: Tuple with folder and extension.
    :rtype: tuple(str, str).
    """

    if len(sys.argv) != 3:
        print("Использование: python main.py <папка> <расширение>")
        sys.exit(1)

    folder_path = sys.argv[1]
    extension = sys.argv[2]

    if not os.path.exists(folder_path):
        print(f"Папка {folder_path} не существует.")
        sys.exit(1)

    return folder_path, extension


def find_files(folder_path, extension):
    """
    :param folder_path:
    :type folder_path: str.

    :param extension:
    :type extension: str.

    :return: List with absolute paths to files.
    :rtype: list[str].
    """

    paths = []
    for root, _, files in os.walk(folder_path):
        for file in files:
            if file.endswith(f".{extension}"):
                file_path = os.path.join(root, file)
                absolute_path = os.path.abspath(file_path)
                paths.append(absolute_path)

    return paths


def main():
    for path in find_files(*process_console()):
        print(path)


if __name__ == '__main__':
    main()
