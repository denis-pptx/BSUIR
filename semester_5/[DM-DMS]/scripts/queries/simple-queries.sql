USE library;


SELECT * FROM user;

SELECT *
FROM user
WHERE username LIKE "%d%";

SELECT id
FROM user u
WHERE u.id IN (SELECT user_id FROM user_profile);

SELECT *
FROM user
WHERE LENGTH(email) > 20; 

SELECT *
FROM book
LIMIT 20 OFFSET 5;

SELECT DISTINCT book_id, user_id
FROM bookmark;

SELECT min(rating), max(rating), avg(rating)
FROM review
WHERE book_id = 1;

UPDATE user
SET email = CONCAT("qwe", email)
WHERE id % 2 = 1;

DELETE FROM book_format
WHERE abbreviation = '';

SELECT username, email, first_name, last_name
FROM user u 
	INNER JOIN user_profile up ON u.id = up.user_id

