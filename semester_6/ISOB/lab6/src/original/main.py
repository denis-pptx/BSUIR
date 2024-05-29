import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QLineEdit, QPushButton, QMessageBox
from PyQt5.QtGui import QPalette, QColor, QRadialGradient, QBrush
from admin_window import AdminWindow
from user_window import UserWindow
from database import add_user, authenticate, create_tables

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Authentication System")
        self.resize(350, 150)

        # Создание и размещение элементов интерфейса
        self.username_label = QLabel("Username:", self)
        self.username_label.move(20, 20)
        self.username_entry = QLineEdit(self)
        self.username_entry.move(120, 20)

        self.password_label = QLabel("Password:", self)
        self.password_label.move(20, 60)
        self.password_entry = QLineEdit(self)
        self.password_entry.move(120, 60)
        self.password_entry.setEchoMode(QLineEdit.Password)

        self.login_button = QPushButton("Login", self)
        self.login_button.move(20, 100)
        self.login_button.clicked.connect(self.login)

        create_tables()
        add_user('denis', 'denis123#A', 'user')
        add_user('admin', 'admin123#A', 'admin')

        # Установка фона градиентом
        palette = QPalette()
        gradient = QRadialGradient(200, 100, 200, 200, 100)
        gradient.setColorAt(0.0, QColor(255, 255, 0)) 
        gradient.setColorAt(1.0, QColor(255, 0, 0))   
        palette.setBrush(QPalette.Window, QBrush(gradient))
        self.setPalette(palette)

    def login(self):
        username = self.validate_input(self.username_entry.text())
        password = self.validate_input(self.password_entry.text())
        user = authenticate(username, password)
        if user:
            if user[2] == "admin":
                self.admin_window = AdminWindow()
                self.admin_window.show()
            else:
                self.user_window = UserWindow()
                self.user_window.show()
        else:
            QMessageBox.critical(self, "Error", "Invalid username or password.")

    # defense from buffer overflow
    def validate_input(self, value):
        if value is not None and len(value) > 50:
            return None
        return value

def main():
    app = QApplication(sys.argv)
    main_window = MainWindow()
    main_window.show()
    sys.exit(app.exec_())

if __name__ == "__main__":
    main()
