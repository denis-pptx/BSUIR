from .Storage import Storage


class User:

    def __init__(self, name: str):
        self.__name: str = name
        self.__storage: Storage = Storage(name)

    @property
    def name(self) -> str:
        return self.__name

    def load_container(self) -> None:
        self.__storage.load()

    def add_items(self, items: list[str]) -> None:
        self.__storage.add(items)

    def get_items(self) -> list[str]:
        return self.__storage.get()

    def remove_item(self, item: str) -> None:
        self.__storage.remove(item)

    def save_container(self) -> None:
        self.__storage.save()

    def reset_container(self) -> None:
        self.__storage.reset()
