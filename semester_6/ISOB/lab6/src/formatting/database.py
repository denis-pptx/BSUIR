import os #line:1
import sqlite3 #line:2
CURRENT_DIR =os .path .join (os .path .dirname (__file__ ))#line:4
DB_PATH =os .path .join (CURRENT_DIR ,'lab4.db')#line:7
def create_tables ():#line:9
    O000OO000OO0O0O00 =sqlite3 .connect (DB_PATH )#line:10
    O0000O0OOO00OO00O =O000OO000OO0O0O00 .cursor ()#line:11
    O0000O0OOO00OO00O .execute ('''DROP TABLE IF EXISTS users''')#line:12
    O0000O0OOO00OO00O .execute ('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT PRIMARY KEY, password TEXT, role TEXT)''')#line:14
    O0000O0OOO00OO00O .execute ('''CREATE TABLE IF NOT EXISTS products
                 (id INTEGER PRIMARY KEY, name TEXT, description TEXT)''')#line:16
    O000OO000OO0O0O00 .commit ()#line:17
    O000OO000OO0O0O00 .close ()#line:18
def add_user (OOOO0000O0O0O0OOO ,O0O00OO0O0O00000O ,OO0OO0000O0OOO000 ):#line:21
    print (DB_PATH )#line:22
    OOO0O00OO0O00000O =sqlite3 .connect (DB_PATH )#line:23
    OOOOOOO0OOOO0O0OO =OOO0O00OO0O00000O .cursor ()#line:24
    OOOOOOO0OOOO0O0OO .execute ("INSERT INTO users VALUES (?, ?, ?)",(OOOO0000O0O0O0OOO ,O0O00OO0O0O00000O ,OO0OO0000O0OOO000 ))#line:25
    OOO0O00OO0O00000O .commit ()#line:26
    OOO0O00OO0O00000O .close ()#line:27
def authenticate (OO0O0OOO0O0O0OOOO ,O0O0O00O0O000O0OO ):#line:31
    OOO0O0000OOOO00OO =sqlite3 .connect (DB_PATH )#line:32
    O00OO000OO0OOOOOO =OOO0O0000OOOO00OO .cursor ()#line:33
    O00OO000OO0OOOOOO .execute ("SELECT * FROM users WHERE username=? AND password=?",(OO0O0OOO0O0O0OOOO ,O0O0O00O0O000O0OO ))#line:34
    OOO00000OOO0O000O =O00OO000OO0OOOOOO .fetchone ()#line:35
    OOO0O0000OOOO00OO .close ()#line:36
    return OOO00000OOO0O000O #line:37
