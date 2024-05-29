from PyQt5.QtWidgets import QLabel, QListWidget, QPushButton, QMessageBox, QInputDialog, QWidget
from database import DB_PATH
import sqlite3

def validate_input(value):
    if value is not None and len(value) > 50:
        return None
    return value

class AdminWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Admin Window")

        # Отображение списка продуктов
        self.product_label = QLabel("Product Management", self)
        self.product_label.move(20, 20)

        self.product_listwidget = QListWidget(self)
        self.product_listwidget.setGeometry(20, 40, 200, 150)

        # Кнопки для CRUD операций
        self.add_button = QPushButton("Add", self)
        self.add_button.setGeometry(20, 200, 60, 30)
        self.add_button.clicked.connect(self.add_product)

        self.edit_button = QPushButton("Edit", self)
        self.edit_button.setGeometry(90, 200, 60, 30)
        self.edit_button.clicked.connect(self.edit_product)

        self.delete_button = QPushButton("Delete", self)
        self.delete_button.setGeometry(160, 200, 60, 30)
        self.delete_button.clicked.connect(self.delete_product)

        # Подключение к базе данных и загрузка продуктов
        self.load_products()

    def load_products(self):
        conn = sqlite3.connect(DB_PATH)
        c = conn.cursor()
        c.execute("SELECT * FROM products")
        products = c.fetchall()
        conn.close()

        for product in products:
            self.product_listwidget.addItem(product[1])  # Предполагается, что название продукта находится во втором столбце

    def add_product(self):
        name, ok_pressed = QInputDialog.getText(self, "Add Product", "Enter product name:")
        if ok_pressed and name.strip():
            if validate_input(name):
                conn = sqlite3.connect(DB_PATH)
                c = conn.cursor()
                c.execute("INSERT INTO products (name) VALUES (?)", (name,))
                conn.commit()
                conn.close()
                self.product_listwidget.addItem(name)
            else:
                QMessageBox.critical(self, "Error", "Length exceeds 50 chars")

    def edit_product(self):
        selected_item = self.product_listwidget.currentItem()
        if selected_item:
            new_name, ok_pressed = QInputDialog.getText(self, "Edit Product", "Enter new name:", text=selected_item.text())
            if ok_pressed and new_name.strip():
                if validate_input(new_name):
                    conn = sqlite3.connect(DB_PATH)
                    c = conn.cursor()
                    c.execute("UPDATE products SET name=? WHERE name=?", (new_name, selected_item.text()))
                    conn.commit()
                    conn.close()
                    selected_item.setText(new_name)
                else:
                    QMessageBox.critical(self, "Error", "Length exceeds 50 chars")

    def delete_product(self):
        selected_item = self.product_listwidget.currentItem()
        if selected_item:
            reply = QMessageBox.question(self, "Delete Product", f"Are you sure you want to delete {selected_item.text()}?", QMessageBox.Yes | QMessageBox.No)
            if reply == QMessageBox.Yes:
                conn = sqlite3.connect(DB_PATH)
                c = conn.cursor()
                c.execute("DELETE FROM products WHERE name=?", (selected_item.text(),))
                conn.commit()
                conn.close()
                selected_row = self.product_listwidget.row(selected_item)
                self.product_listwidget.takeItem(selected_row)
