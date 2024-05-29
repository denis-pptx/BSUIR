import os
import sqlite3

CURRENT_DIR = os.path.join(os.path.dirname(__file__))
#CURRENT_DIR = r'D:\Studies\BSUIR\Semester_6\ISOB\lab6\src'
# Пути к базам данных
DB_PATH = os.path.join(CURRENT_DIR, 'lab4.db')

def create_tables():
    conn = sqlite3.connect(DB_PATH)
    c = conn.cursor()
    c.execute('''DROP TABLE IF EXISTS users''')
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT PRIMARY KEY, password TEXT, role TEXT)''')
    c.execute('''CREATE TABLE IF NOT EXISTS products
                 (id INTEGER PRIMARY KEY, name TEXT, description TEXT)''')
    conn.commit()
    conn.close()


def add_user(username, password, role):
    print(DB_PATH)
    conn = sqlite3.connect(DB_PATH)
    c = conn.cursor()
    c.execute("INSERT INTO users VALUES (?, ?, ?)", (username, password, role))
    conn.commit()
    conn.close()


# defense from SQL-injection - parameters in SQL-query
def authenticate(username, password):
    conn = sqlite3.connect(DB_PATH)
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = c.fetchone()
    conn.close()
    return user
