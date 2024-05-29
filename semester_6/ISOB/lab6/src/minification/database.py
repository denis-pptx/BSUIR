import os,sqlite3
CURRENT_DIR=os.path.join(os.path.dirname(__file__))
DB_PATH=os.path.join(CURRENT_DIR,'lab4.db')
def create_tables():A=sqlite3.connect(DB_PATH);B=A.cursor();B.execute('DROP TABLE IF EXISTS users');B.execute('CREATE TABLE IF NOT EXISTS users\n                 (username TEXT PRIMARY KEY, password TEXT, role TEXT)');B.execute('CREATE TABLE IF NOT EXISTS products\n                 (id INTEGER PRIMARY KEY, name TEXT, description TEXT)');A.commit();A.close()
def add_user(username,password,role):print(DB_PATH);A=sqlite3.connect(DB_PATH);B=A.cursor();B.execute('INSERT INTO users VALUES (?, ?, ?)',(username,password,role));A.commit();A.close()
def authenticate(username,password):A=sqlite3.connect(DB_PATH);B=A.cursor();B.execute('SELECT * FROM users WHERE username=? AND password=?',(username,password));C=B.fetchone();A.close();return C