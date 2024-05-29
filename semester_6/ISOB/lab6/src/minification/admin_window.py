_A='Length exceeds 50 chars'
from PyQt5.QtWidgets import QLabel,QListWidget,QPushButton,QMessageBox,QInputDialog,QWidget
from database import DB_PATH
import sqlite3
def validate_input(value):
	A=value
	if A is not None and len(A)>50:return
	return A
class AdminWindow(QWidget):
	def __init__(A):super().__init__();A.setWindowTitle('Admin Window');A.product_label=QLabel('Product Management',A);A.product_label.move(20,20);A.product_listwidget=QListWidget(A);A.product_listwidget.setGeometry(20,40,200,150);A.add_button=QPushButton('Add',A);A.add_button.setGeometry(20,200,60,30);A.add_button.clicked.connect(A.add_product);A.edit_button=QPushButton('Edit',A);A.edit_button.setGeometry(90,200,60,30);A.edit_button.clicked.connect(A.edit_product);A.delete_button=QPushButton('Delete',A);A.delete_button.setGeometry(160,200,60,30);A.delete_button.clicked.connect(A.delete_product);A.load_products()
	def load_products(C):
		A=sqlite3.connect(DB_PATH);B=A.cursor();B.execute('SELECT * FROM products');D=B.fetchall();A.close()
		for E in D:C.product_listwidget.addItem(E[1])
	def add_product(B):
		A,D=QInputDialog.getText(B,'Add Product','Enter product name:')
		if D and A.strip():
			if validate_input(A):C=sqlite3.connect(DB_PATH);E=C.cursor();E.execute('INSERT INTO products (name) VALUES (?)',(A,));C.commit();C.close();B.product_listwidget.addItem(A)
			else:QMessageBox.critical(B,'Error',_A)
	def edit_product(C):
		A=C.product_listwidget.currentItem()
		if A:
			B,E=QInputDialog.getText(C,'Edit Product','Enter new name:',text=A.text())
			if E and B.strip():
				if validate_input(B):D=sqlite3.connect(DB_PATH);F=D.cursor();F.execute('UPDATE products SET name=? WHERE name=?',(B,A.text()));D.commit();D.close();A.setText(B)
				else:QMessageBox.critical(C,'Error',_A)
	def delete_product(A):
		B=A.product_listwidget.currentItem()
		if B:
			D=QMessageBox.question(A,'Delete Product',f"Are you sure you want to delete {B.text()}?",QMessageBox.Yes|QMessageBox.No)
			if D==QMessageBox.Yes:C=sqlite3.connect(DB_PATH);E=C.cursor();E.execute('DELETE FROM products WHERE name=?',(B.text(),));C.commit();C.close();F=A.product_listwidget.row(B);A.product_listwidget.takeItem(F)