# Create user procedure
DELIMITER //
CREATE PROCEDURE CreateUser(
    IN p_username VARCHAR(20),
    IN p_password VARCHAR(100),
    IN p_email VARCHAR(254),
    IN p_is_active TINYINT(1),
    IN p_is_admin TINYINT(0)
)
BEGIN
    DECLARE existing_user INT;

    SELECT COUNT(*) INTO existing_user
    FROM user
    WHERE username = p_username OR email = p_email;
    
    IF existing_user = 0 THEN
        INSERT INTO user(username, password, email, is_active, is_admin)
        VALUES (p_username, SHA2(p_password, 256), p_email, p_is_active, p_is_admin);
        
        SELECT 'User created successfully' AS result;
    ELSE
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Username or email already exists';
    END IF;
END; 
//
DELIMITER ;

# Test procedure
# CALL CreateUser("denis_test", "test_password", "qwe@mail.ru", 1, 0, 0);



# Update user procedure
DELIMITER //
CREATE PROCEDURE UpdateUser(
    IN p_user_id INT,
    IN p_username VARCHAR(20),
    IN p_password VARCHAR(100),
    IN p_email VARCHAR(254),
    IN p_is_active TINYINT(1),
    IN p_is_admin TINYINT(0)
)
BEGIN
    DECLARE existing_user INT;
	
    SELECT COUNT(*) INTO existing_user
    FROM user
    WHERE id = p_user_id;
    
    IF existing_user != 1 THEN
		SIGNAL SQLSTATE '45000'
		SET MESSAGE_TEXT = 'User not found';
    END IF;
        
    SELECT COUNT(*) INTO existing_user
    FROM user
    WHERE (username = p_username OR email = p_email) AND id != p_user_id;

    IF existing_user = 0 THEN
        UPDATE user
        SET
            username = p_username,
            password = SHA2(p_password, 256),
            email = p_email,
            is_active = p_is_active,
            is_admin = p_is_admin
        WHERE id = p_user_id;

        SELECT 'User updated successfully' AS result;
    ELSE
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Username or email already exists';
    END IF;
END; 
//
DELIMITER ;


# Books by parameters procedure
DELIMITER //
CREATE PROCEDURE GetBooksByParameters(
    IN p_language_id INT,
    IN p_author_id INT,
    IN p_genre_id INT,
    IN p_publisher_id INT
)
BEGIN
    SELECT DISTINCT b.*
    FROM book b
    LEFT JOIN book_language bl ON b.id = bl.book_id
    LEFT JOIN book_author ba ON b.id = ba.book_id
    LEFT JOIN book_genre bg ON b.id = bg.book_id
    WHERE
        (p_language_id IS NULL OR bl.language_id = p_language_id)
        AND (p_author_id IS NULL OR ba.author_id = p_author_id)
        AND (p_genre_id IS NULL OR bg.genre_id = p_genre_id)
        AND (p_publisher_id IS NULL OR b.publisher_id = p_publisher_id);
END;
//
DELIMITER ;

# Test procedure
# CALL GetBooksByParameters(NULL, 1, 3, NULL);




# Books reading by user
DELIMITER //
CREATE PROCEDURE GetReadingList(IN p_user_id INT)
BEGIN
    SELECT b.*
    FROM book b INNER JOIN reading r 
		ON r.book_id = b.id
	WHERE r.user_id = p_user_id;
END //
DELIMITER ;

# Test procedure
# CALL GetReadingList(1);