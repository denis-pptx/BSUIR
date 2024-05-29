USE library;

# Reviews only for available books
DELIMITER // 
CREATE TRIGGER check_book_availability
BEFORE INSERT ON review
FOR EACH ROW
BEGIN
    DECLARE is_book_available TINYINT;
    SELECT is_available INTO is_book_available FROM book WHERE id = NEW.book_id;
    IF is_book_available = 0 THEN
        SIGNAL SQLSTATE '45000' # unhandled user-defined exception
        SET MESSAGE_TEXT = 'Cannot add review for an unavailable book';
    END IF;
END;
//
DELIMITER ;

# Test check_book_availability
/*
UPDATE book
SET is_available = 1
WHERE id = 1;

INSERT INTO review (text, rating, user_id, book_id) 
VALUES 
	("Test text",  5, 10, 1); 
*/



# Maintain an average book rating
DELIMITER // 
CREATE TRIGGER book_average_rating_insert
AFTER INSERT ON review
FOR EACH ROW
BEGIN
    UPDATE book
    SET average_rating = (SELECT AVG(rating) FROM review WHERE book_id = NEW.book_id)
    WHERE id = NEW.book_id;
END;
//

CREATE TRIGGER book_average_rating_update
AFTER UPDATE ON review
FOR EACH ROW
BEGIN
    UPDATE book
    SET average_rating = (SELECT AVG(rating) FROM review WHERE book_id = NEW.book_id)
    WHERE id = NEW.book_id;
END;
//

CREATE TRIGGER book_average_rating_delete
AFTER DELETE ON review
FOR EACH ROW
BEGIN
    UPDATE book
    SET average_rating = (SELECT AVG(rating) FROM review WHERE book_id = OLD.book_id)
    WHERE id = OLD.book_id;
END;
//
DELIMITER ;



# Log user adding
DELIMITER // 
CREATE TRIGGER log_user_add
AFTER INSERT on user
FOR EACH ROW
BEGIN
	INSERT INTO action (description, action_type_id, user_id) 
    VALUES (CONCAT('username: ', NEW.username), 4, NEW.id);
END;
//
DELIMITER ;
