import sys #line:1
from PyQt5 .QtWidgets import QApplication ,QMainWindow ,QLabel ,QLineEdit ,QPushButton ,QMessageBox #line:2
from PyQt5 .QtGui import QPalette ,QColor ,QRadialGradient ,QBrush #line:3
from admin_window import AdminWindow #line:4
from user_window import UserWindow #line:5
from database import add_user ,authenticate ,create_tables #line:6
class MainWindow (QMainWindow ):#line:8
    def __init__ (O000OO0OOO0OOOO0O ):#line:9
        super ().__init__ ()#line:10
        O000OO0OOO0OOOO0O .setWindowTitle ("Authentication System")#line:11
        O000OO0OOO0OOOO0O .resize (350 ,150 )#line:12
        O000OO0OOO0OOOO0O .username_label =QLabel ("Username:",O000OO0OOO0OOOO0O )#line:15
        O000OO0OOO0OOOO0O .username_label .move (20 ,20 )#line:16
        O000OO0OOO0OOOO0O .username_entry =QLineEdit (O000OO0OOO0OOOO0O )#line:17
        O000OO0OOO0OOOO0O .username_entry .move (120 ,20 )#line:18
        O000OO0OOO0OOOO0O .password_label =QLabel ("Password:",O000OO0OOO0OOOO0O )#line:20
        O000OO0OOO0OOOO0O .password_label .move (20 ,60 )#line:21
        O000OO0OOO0OOOO0O .password_entry =QLineEdit (O000OO0OOO0OOOO0O )#line:22
        O000OO0OOO0OOOO0O .password_entry .move (120 ,60 )#line:23
        O000OO0OOO0OOOO0O .password_entry .setEchoMode (QLineEdit .Password )#line:24
        O000OO0OOO0OOOO0O .login_button =QPushButton ("Login",O000OO0OOO0OOOO0O )#line:26
        O000OO0OOO0OOOO0O .login_button .move (20 ,100 )#line:27
        O000OO0OOO0OOOO0O .login_button .clicked .connect (O000OO0OOO0OOOO0O .login )#line:28
        create_tables ()#line:30
        add_user ('denis','denis123#A','user')#line:31
        add_user ('admin','admin123#A','admin')#line:32
        O0O0O00O000OOO000 =QPalette ()#line:35
        O0O0OO0000000000O =QRadialGradient (200 ,100 ,200 ,200 ,100 )#line:36
        O0O0OO0000000000O .setColorAt (0.0 ,QColor (255 ,255 ,0 ))#line:37
        O0O0OO0000000000O .setColorAt (1.0 ,QColor (255 ,0 ,0 ))#line:38
        O0O0O00O000OOO000 .setBrush (QPalette .Window ,QBrush (O0O0OO0000000000O ))#line:39
        O000OO0OOO0OOOO0O .setPalette (O0O0O00O000OOO000 )#line:40
    def login (O0OO0O0OO000OOO0O ):#line:42
        OO00OO0OO0O0000OO =O0OO0O0OO000OOO0O .validate_input (O0OO0O0OO000OOO0O .username_entry .text ())#line:43
        O00OO000O0O0000O0 =O0OO0O0OO000OOO0O .validate_input (O0OO0O0OO000OOO0O .password_entry .text ())#line:44
        O00000O0O00OO0000 =authenticate (OO00OO0OO0O0000OO ,O00OO000O0O0000O0 )#line:45
        if O00000O0O00OO0000 :#line:46
            if O00000O0O00OO0000 [2 ]=="admin":#line:47
                O0OO0O0OO000OOO0O .admin_window =AdminWindow ()#line:48
                O0OO0O0OO000OOO0O .admin_window .show ()#line:49
            else :#line:50
                O0OO0O0OO000OOO0O .user_window =UserWindow ()#line:51
                O0OO0O0OO000OOO0O .user_window .show ()#line:52
        else :#line:53
            QMessageBox .critical (O0OO0O0OO000OOO0O ,"Error","Invalid username or password.")#line:54
    def validate_input (O00OOOOOOO0OOO00O ,O00O0000O0000OOO0 ):#line:57
        if O00O0000O0000OOO0 is not None and len (O00O0000O0000OOO0 )>50 :#line:58
            return None #line:59
        return O00O0000O0000OOO0 #line:60
def main ():#line:62
    OO0OO00OOOOO0O00O =QApplication (sys .argv )#line:63
    OOO000OO00O000O0O =MainWindow ()#line:64
    OOO000OO00O000O0O .show ()#line:65
    sys .exit (OO0OO00OOOOO0O00O .exec_ ())#line:66
if __name__ =="__main__":#line:68
    main ()#line:69
