import re
from .User import User
from ..constants import CommandsInfo
from .Command import Command


class Console:

    def __init__(self):
        self.__user: User | None = None
        self.__commands: list[str] = [command.name for command in CommandsInfo]

    def get_line_start(self):
        if self.__user is None:
            return '> '
        else:
            return f'({self.__user.name}) > '

    def start(self) -> None:
        self.help_command()

        while True:
            try:
                command: Command = Command(input(self.get_line_start()))
                self.command_handler(command)
            except KeyboardInterrupt:
                self.keyboard_interrupt_handler()
                break



    def command_handler(self, command: Command) -> None:
        if command.name == CommandsInfo.login.name \
                and len(command.args) == 1:
            self.login_command(*command.args)

        elif command.name == CommandsInfo.help.name \
                and len(command.args) == 0:
            self.help_command()

        elif command.name == CommandsInfo.add.name \
                and len(command.args) != 0:
            self.add_command(command.args)

        elif command.name == CommandsInfo.list.name \
                and len(command.args) == 0:
            self.list_command()

        elif command.name == CommandsInfo.remove.name \
                and len(command.args) == 1:
            self.remove_command(*command.args)

        elif command.name == CommandsInfo.find.name \
                and len(command.args) != 0:
            self.find_command(command.args)

        elif command.name == CommandsInfo.save.name \
                and len(command.args) == 0:
            self.save_command()

        elif command.name == CommandsInfo.load.name \
                and len(command.args) == 0:
            self.load_command()

        elif command.name == CommandsInfo.reset.name \
                and len(command.args) == 0:
            self.reset_command()

        elif command.name == CommandsInfo.grep.name \
                and len(command.args) == 1:
            self.grep_command(*command.args)

        elif command.name == CommandsInfo.logout.name \
                and len(command.args) == 0:
            self.logout_command()

        elif command.name == CommandsInfo.switch.name \
                and len(command.args) == 1:
            self.switch_command(*command.args)

        elif command.name == CommandsInfo.exit.name \
                and len(command.args) == 0:
            raise KeyboardInterrupt

        else:
            self.print_incorrect_command(command.raw)


    @staticmethod
    def print_incorrect_command(command: str) -> None:
        print(f'"{command}" is incorrect command. Look "{CommandsInfo.help.name}".')


    @staticmethod
    def help_command() -> None:
        print('\n', '\n'.join([command.value for command in CommandsInfo]), '\n', sep='')


    def is_logged(self, print_msg: bool = True) -> bool:
        if print_msg and self.__user is None:
            print('You are not logged. Login to realize this operation.')

        return self.__user is not None


    def login_command(self, username: str) -> None:
        if self.__user:
            print('You are already logged in.', f'Use "{CommandsInfo.switch.name}".')
            return

        if not Command.is_correct_username(username):
            print(f'Incorrect username. Use only symbols: {Command.correct_username_symbols}')
            return

        self.__user = User(username)
        print(f'Authorized with "{username}".')

        answer: str = input('Load container (create if not exists)? [Y/N]: ')
        if self.yes_no_handler(answer):
            self.__user.load_container()
            print('Container loaded (created).')
            print(f'Items in container: {len(self.__user.get_items())}.')


    def add_command(self, items: list[str]) -> None:
        if not self.is_logged():
            return

        self.__user.add_items(items)


    def list_command(self) -> None:
        if not self.is_logged():
            return

        items: list[str] = self.__user.get_items()
        if len(items) == 0:
            print("Container is empty.")
        else:
            print(f'Items number: {len(items)}.')
            print('\n'.join(items))


    def remove_command(self, item: str) -> None:
        if not self.is_logged():
            return

        self.__user.remove_item(item)


    def find_command(self, items: list[str]) -> None:
        if not self.is_logged():
            return

        suitable_items: list[str] = []
        all_items: list[str] = self.__user.get_items()

        for item in items:
            if item in all_items:
                suitable_items.append(item)

        if len(suitable_items) == 0:
            print("No such items.")
        else:
            print(f'Found {len(suitable_items)} items.')
            print('\n'.join(suitable_items))


    def save_command(self) -> None:
        if not self.is_logged():
            return

        self.__user.save_container()


    def load_command(self) -> None:
        if not self.is_logged():
            return

        self.__user.load_container()
        self.__user.save_container()


    def reset_command(self) -> None:
        if not self.is_logged():
            return

        self.__user.reset_container()


    def grep_command(self, regex: str) -> None:
        if not self.is_logged():
            return

        suitable_items: list[str] = []
        all_items: list[str] = self.__user.get_items()

        for item in all_items:
            try:
                if re.fullmatch(regex, item):
                    suitable_items.append(item)
            except Exception as ex:
                print("Regular expression is invalid.")
                print(f"Error: {ex.args}")
                return

        if len(suitable_items) == 0:
            print("No such items.")
        else:
            print(f'Found {len(suitable_items)} items.')
            print('\n'.join(suitable_items))


    def logout_command(self) -> None:
        if not self.is_logged():
            return

        answer: str = input('Save container before logout? [Y/N]: ')
        if self.yes_no_handler(answer):
            self.__user.save_container()

        self.__user = None


    def switch_command(self, another_user_name: str) -> None:
        if not self.is_logged():
            return

        if not Command.is_correct_username(another_user_name):
            print(f'Incorrect username. Use only symbols: {Command.correct_username_symbols}')
            return

        if another_user_name == self.__user.name:
            print(f'You are already logged in with "{self.__user.name}".')
            return

        answer: str = input('Save container before switch? [Y/N]: ')
        if self.yes_no_handler(answer):
            self.__user.save_container()

        self.__user = None
        self.login_command(another_user_name)

    def keyboard_interrupt_handler(self) -> None:
        if not self.is_logged(print_msg=False):
            return

        answer: str = input('\rSave container before exit? [Y/N]: ')
        if self.yes_no_handler(answer):
            self.__user.save_container()

    @staticmethod
    def yes_no_handler(answer: str) -> bool:
        if answer == 'Y':
            return True
        else:
            return False

