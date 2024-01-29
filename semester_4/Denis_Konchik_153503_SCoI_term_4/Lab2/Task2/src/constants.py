import pathlib
from enum import Enum
from pathlib import Path


class CommandsInfo(Enum):
    login:  str = "login <username>    – authorize"
    add:    str = "add <key> [key, …]  – add one or more elements to the container"
    remove: str = "remove <key>        – delete key from container"
    find:   str = "find <key> [key, …] – check if the element is presented in the container"
    list:   str = "list                – print all elements of container"
    grep:   str = "grep <regex>        – check the value in the container by regular expression"
    save:   str = "save                – save container to file"
    load:   str = "load                – load container from file"
    switch: str = "switch <username>   – switch to another user"
    reset:  str = "reset               – delete all keys from container"
    logout: str = "logout              – log out of the user account"
    exit:   str = "exit                – stop program"
    help:   str = "help                – show all commands"


# DEFAULT_PATH: Path = Path(r'/home/den/Studies/Denis_Konchik_153503_SCoI_term_4/Lab2/Task2/containers')
# DEFAULT_PATH: Path = Path(pathlib.Path().absolute(), "containers")
DEFAULT_PATH: Path = Path(Path(__file__).parent.parent.absolute(), "containers")
CONTAINER_EXTENSION = 'txt'
