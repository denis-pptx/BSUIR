_A='admin'
import sys
from PyQt5.QtWidgets import QApplication,QMainWindow,QLabel,QLineEdit,QPushButton,QMessageBox
from PyQt5.QtGui import QPalette,QColor,QRadialGradient,QBrush
from admin_window import AdminWindow
from user_window import UserWindow
from database import add_user,authenticate,create_tables
class MainWindow(QMainWindow):
	def __init__(A):super().__init__();A.setWindowTitle('Authentication System');A.resize(350,150);A.username_label=QLabel('Username:',A);A.username_label.move(20,20);A.username_entry=QLineEdit(A);A.username_entry.move(120,20);A.password_label=QLabel('Password:',A);A.password_label.move(20,60);A.password_entry=QLineEdit(A);A.password_entry.move(120,60);A.password_entry.setEchoMode(QLineEdit.Password);A.login_button=QPushButton('Login',A);A.login_button.move(20,100);A.login_button.clicked.connect(A.login);create_tables();add_user('denis','denis123#A','user');add_user(_A,'admin123#A',_A);C=QPalette();B=QRadialGradient(200,100,200,200,100);B.setColorAt(.0,QColor(255,255,0));B.setColorAt(1.,QColor(255,0,0));C.setBrush(QPalette.Window,QBrush(B));A.setPalette(C)
	def login(A):
		C=A.validate_input(A.username_entry.text());D=A.validate_input(A.password_entry.text());B=authenticate(C,D)
		if B:
			if B[2]==_A:A.admin_window=AdminWindow();A.admin_window.show()
			else:A.user_window=UserWindow();A.user_window.show()
		else:QMessageBox.critical(A,'Error','Invalid username or password.')
	def validate_input(B,value):
		A=value
		if A is not None and len(A)>50:return
		return A
def main():A=QApplication(sys.argv);B=MainWindow();B.show();sys.exit(A.exec_())
if __name__=='__main__':main()