import os
from PyQt5.QtWidgets import QLabel, QListWidget, QPushButton, QFileDialog, QMessageBox, QWidget
from database import CURRENT_DIR, DB_PATH
import sqlite3

MAX_FILE_SIZE = 1024 * 1024  # Максимальный размер файла (в байтах), например, 1 МБ
TEST_FILE_DIR = os.path.join(CURRENT_DIR, 'test_files')


class UserWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("User Window")

        # Отображение списка продуктов
        self.product_label = QLabel("Product List", self)
        self.product_label.move(20, 20)

        self.product_listwidget = QListWidget(self)
        self.product_listwidget.setGeometry(20, 40, 200, 150)

        # Подключение к базе данных и загрузка продуктов
        self.load_products()

        self.select_file_button = QPushButton("Select File", self)
        self.select_file_button.setGeometry(20, 200, 100, 30)
        self.select_file_button.clicked.connect(self.select_file)

    def load_products(self):
        conn = sqlite3.connect(DB_PATH)
        c = conn.cursor()
        c.execute("SELECT * FROM products")
        products = c.fetchall()
        conn.close()

        for product in products:
            self.product_listwidget.addItem(product[1])  # Предполагается, что название продукта находится во втором столбце

    def select_file(self):
        selected_file, _ = QFileDialog.getOpenFileName(self, "Select File", TEST_FILE_DIR, "Text files (*.txt)")

        if selected_file:
            selected_file = os.path.normpath(selected_file)
            data_dir = os.path.normpath(TEST_FILE_DIR)

            if os.path.dirname(selected_file).lower() != data_dir.lower():
                QMessageBox.critical(self, "Error", "Selected file is not in the data folder.")
                return

            file_size = os.path.getsize(selected_file)
            if file_size > MAX_FILE_SIZE:
                QMessageBox.critical(self, "Error", "Selected file size exceeds the maximum allowed size.")
            else:
                try:
                    with open(selected_file, 'r') as file:
                        file_content = file.read()
                        QMessageBox.information(self, "File Content", file_content)
                except Exception as e:
                    QMessageBox.critical(self, "Error", f"Failed to read file: {e}")
