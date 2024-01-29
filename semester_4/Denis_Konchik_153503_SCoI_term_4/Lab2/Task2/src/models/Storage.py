from ..constants import DEFAULT_PATH, CONTAINER_EXTENSION
from pathlib import Path
import json


class Storage:

    def __init__(self, username: str):
        self.__username: str = username
        self.__container: set[str] = set()
        self.__container_path: Path = Path(DEFAULT_PATH, f'{username}.{CONTAINER_EXTENSION}')

    def load(self) -> None:

        if self.__container_path.exists():
            try:
                with open(self.__container_path, 'r') as file:
                    text: str = file.read()

                    if not (text.isspace() or text == ''):
                        self.__container.update(json.loads(text))

            except Exception as ex:
                print(f'Error: {ex.args}')
        else:
            self.__container_path.touch()


    def add(self, items: list[str]) -> None:
        self.__container.update(items)

    def get(self) -> list[str]:
        return list(self.__container)

    def remove(self, item: str) -> None:
        self.__container.discard(item)

    def save(self) -> None:
        self.__container_path.touch(exist_ok=True)

        try:
            with open(self.__container_path, 'w') as file:
                file.write(json.dumps(list(self.__container)))
        except Exception as ex:
            print(f'Error: {ex.args}')


    def reset(self) -> None:
        self.__container.clear()


