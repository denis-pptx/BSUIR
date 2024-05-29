_A='Select File'
import os
from PyQt5.QtWidgets import QLabel,QListWidget,QPushButton,QFileDialog,QMessageBox,QWidget
from database import CURRENT_DIR,DB_PATH
import sqlite3
MAX_FILE_SIZE=1024*1024
TEST_FILE_DIR=os.path.join(CURRENT_DIR,'test_files')
class UserWindow(QWidget):
	def __init__(A):super().__init__();A.setWindowTitle('User Window');A.product_label=QLabel('Product List',A);A.product_label.move(20,20);A.product_listwidget=QListWidget(A);A.product_listwidget.setGeometry(20,40,200,150);A.load_products();A.select_file_button=QPushButton(_A,A);A.select_file_button.setGeometry(20,200,100,30);A.select_file_button.clicked.connect(A.select_file)
	def load_products(C):
		A=sqlite3.connect(DB_PATH);B=A.cursor();B.execute('SELECT * FROM products');D=B.fetchall();A.close()
		for E in D:C.product_listwidget.addItem(E[1])
	def select_file(B):
		C='Error';A,I=QFileDialog.getOpenFileName(B,_A,TEST_FILE_DIR,'Text files (*.txt)')
		if A:
			A=os.path.normpath(A);D=os.path.normpath(TEST_FILE_DIR)
			if os.path.dirname(A).lower()!=D.lower():QMessageBox.critical(B,C,'Selected file is not in the data folder.');return
			E=os.path.getsize(A)
			if E>MAX_FILE_SIZE:QMessageBox.critical(B,C,'Selected file size exceeds the maximum allowed size.')
			else:
				try:
					with open(A,'r')as F:G=F.read();QMessageBox.information(B,'File Content',G)
				except Exception as H:QMessageBox.critical(B,C,f"Failed to read file: {H}")