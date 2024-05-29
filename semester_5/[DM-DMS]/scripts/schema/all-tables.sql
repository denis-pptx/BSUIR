CREATE SCHEMA IF NOT EXISTS library;

USE library;


CREATE TABLE IF NOT EXISTS user (
	id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(20) NOT NULL UNIQUE,
    password CHAR(64) NOT NULL,
    email VARCHAR(254) NOT NULL UNIQUE,
    is_active TINYINT(1) NOT NULL DEFAULT 1,
    is_admin TINYINT(1) NOT NULL DEFAULT 0,
    
    CHECK (username REGEXP '^[A-Za-z0-9_]{6,}$'),
    CHECK (CHAR_LENGTH(password) = 64),
    CHECK (email REGEXP '[a-zA-Z0-9._-]+@[a-zA-Z0-9._-]+\.[a-zA-Z0-9_-]+')
);

CREATE TABLE IF NOT EXISTS user_profile (
	user_id INT PRIMARY KEY,
	first_name VARCHAR(45),
	last_name VARCHAR(45),
    birth_date DATE,
    
    FOREIGN KEY (user_id) REFERENCES user(id) ON DELETE CASCADE,
    CHECK (first_name IS NULL OR first_name != ''),
    CHECK (last_name IS NULL OR last_name != '')
);

CREATE TABLE IF NOT EXISTS action_type (
	id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(45) NOT NULL,
    
    CHECK (name != '')
);

CREATE TABLE IF NOT EXISTS action (
	id INT PRIMARY KEY AUTO_INCREMENT,
    timestamp TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    description TEXT,
    action_type_id INT NOT NULL,
    user_id INT,
    
    FOREIGN KEY (action_type_id) REFERENCES action_type(id) ON DELETE NO ACTION,
    FOREIGN KEY (user_id) REFERENCES user(id) ON DELETE SET NULL
);

CREATE TABLE IF NOT EXISTS publisher (
	id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL UNIQUE,
    description TEXT,
    
    CHECK(name != '')
);

CREATE TABLE IF NOT EXISTS book (
	id INT PRIMARY KEY AUTO_INCREMENT,
    title VARCHAR(200) NOT NULL,
    description TEXT,
    publication_date DATE NOT NULL,
    added TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    isbn VARCHAR(13) NOT NULL,
    is_available TINYINT(1) NOT NULL DEFAULT 1,
    average_rating DECIMAL(3, 2) NOT NULL DEFAULT 0,
    publisher_id INT NOT NULL,
    
    FOREIGN KEY (publisher_id) REFERENCES publisher(id) ON DELETE NO ACTION,
    CHECK (title != ''),
    CHECK (CHAR_LENGTH(isbn) IN (10, 13))
);

CREATE TABLE IF NOT EXISTS language (
	id INT PRIMARY KEY AUTO_INCREMENT,
	name VARCHAR(45) NOT NULL UNIQUE,
    
    CHECK (name != '')
);

CREATE TABLE IF NOT EXISTS book_language (
	book_id INT NOT NULL,
    language_id INT NOT NULL,
    
    PRIMARY KEY (book_id, language_id),
    FOREIGN KEY (book_id) REFERENCES book(id) ON DELETE CASCADE,
    FOREIGN KEY (language_id) REFERENCES language(id) ON DELETE NO ACTION
);

CREATE TABLE IF NOT EXISTS genre (
	id INT PRIMARY KEY AUTO_INCREMENT,
	name VARCHAR(45) NOT NULL UNIQUE,
    
    CHECK (name != '')
);

CREATE TABLE IF NOT EXISTS book_genre (
	book_id INT NOT NULL,
    genre_id INT NOT NULL,
    
    PRIMARY KEY (book_id, genre_id),
    FOREIGN KEY (book_id) REFERENCES book(id) ON DELETE CASCADE,
    FOREIGN KEY (genre_id) REFERENCES genre(id) ON DELETE NO ACTION
);

CREATE TABLE IF NOT EXISTS review (
	id INT PRIMARY KEY AUTO_INCREMENT,
    text TEXT,
    rating TINYINT UNSIGNED NOT NULL,
    user_id INT,
    book_id INT NOT NULL,
    
    FOREIGN KEY (user_id) REFERENCES user(id) ON DELETE SET NULL,
    FOREIGN KEY (book_id) REFERENCES book(id) ON DELETE CASCADE,
    CHECK (rating BETWEEN 1 AND 5)
);

CREATE TABLE IF NOT EXISTS author (
	id INT PRIMARY KEY AUTO_INCREMENT,
    first_name VARCHAR(45) NOT NULL,
	last_name VARCHAR(45) NOT NULL,
	birth_date DATE NOT NULL,
    
    CHECK (first_name != ''),
    CHECK (last_name != '')
);

CREATE TABLE IF NOT EXISTS book_author (
	book_id INT NOT NULL,
	author_id INT NOT NULL,
    
    PRIMARY KEY (book_id, author_id),
    FOREIGN KEY (book_id) REFERENCES book(id) ON DELETE CASCADE,
    FOREIGN KEY (author_id) REFERENCES author(id) ON DELETE NO ACTION
);

CREATE TABLE IF NOT EXISTS book_format (
	id INT PRIMARY KEY AUTO_INCREMENT,
	abbreviation VARCHAR(10) NOT NULL UNIQUE,
	description TEXT,
    
    CHECK (abbreviation != '')
);

CREATE TABLE IF NOT EXISTS book_file (
	id INT PRIMARY KEY AUTO_INCREMENT,
    path VARCHAR(255) NOT NULL,
    book_id INT NOT NULL,
    book_format_id INT NOT NULL,
    
    FOREIGN KEY (book_id) REFERENCES book(id) ON DELETE CASCADE,
    FOREIGN KEY (book_format_id) REFERENCES book_format(id) ON DELETE NO ACTION,
    CHECK (path != '')
);

CREATE TABLE IF NOT EXISTS bookmark (
	id INT PRIMARY KEY AUTO_INCREMENT,
    page_number INT UNSIGNED NOT NULL,
    book_id INT NOT NULL,
    user_id INT NOT NULL,
    
    FOREIGN KEY (book_id) REFERENCES book(id) ON DELETE CASCADE,
    FOREIGN KEY (user_id) REFERENCES user(id) ON DELETE CASCADE,
	CHECK (page_number > 0)
);

CREATE TABLE IF NOT EXISTS reading (
	id INT PRIMARY KEY AUTO_INCREMENT,
    added TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    book_id INT NOT NULL,
    user_id INT NOT NULL,
    
    FOREIGN KEY (book_id) REFERENCES book(id) ON DELETE CASCADE,
    FOREIGN KEY (user_id) REFERENCES user(id) ON DELETE CASCADE
);
