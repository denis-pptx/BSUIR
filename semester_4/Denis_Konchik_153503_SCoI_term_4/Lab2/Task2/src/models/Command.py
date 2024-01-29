import re


class Command:

    correct_username_symbols: str = 'a-z, A-Z, 0-9, _'

    def __init__(self, command: str):
        self.__command: str = command

    @property
    def name(self) -> str | None:
        first_word_match = re.match(r'(?<=^)[^ ]+(?= |$)', self.__command)

        if first_word_match:
            return first_word_match.group(0)
        else:
            return None

    @property
    def args(self) -> list[str] | None:

        if self.name:
            return re.findall(r'(?<!^)(?<= )[^ ]+', self.__command)
        else:
            return None

    @property
    def raw(self) -> str:
        return self.__command

    @staticmethod
    def is_correct_username(username: str) -> bool:
        return re.fullmatch(r'[a-zA-Z0-9_]+', username)
