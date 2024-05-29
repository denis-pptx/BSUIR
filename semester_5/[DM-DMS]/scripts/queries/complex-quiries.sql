USE library;


-- All info about books [1]
SELECT b.id as book_id, b.title, 
	   GROUP_CONCAT(DISTINCT l.name SEPARATOR ', ') as languages,
       GROUP_CONCAT(DISTINCT CONCAT_WS(' ', a.first_name, a.last_name) SEPARATOR ', ') as authors,
       GROUP_CONCAT(DISTINCT g.name SEPARATOR ', ') as genres,
       p.name as publisher
FROM book b 
	INNER JOIN book_language bl ON b.id = bl.book_id
	INNER JOIN language l ON l.id = bl.language_id
    
    INNER JOIN book_author ba ON b.id = ba.book_id
    INNER JOIN author a ON a.id = ba.author_id
    
    INNER JOIN book_genre bg ON b.id = bg.book_id
    INNER JOIN genre g ON g.id = bg.genre_id
    
	INNER JOIN publisher p on p.id = b.publisher_id
GROUP BY b.id;


-- All info about books [2]
SELECT b.id as book_id, b.title,
	(SELECT GROUP_CONCAT(l.name SEPARATOR ', ')
     FROM book_language bl INNER JOIN language l ON bl.language_id = l.id 
	 WHERE bl.book_id = b.id) as languages,
     
	(SELECT GROUP_CONCAT(CONCAT_WS(' ', a.first_name, a.last_name) SEPARATOR ', ')
	 FROM book_author ba INNER JOIN author a ON ba.author_id = a.id
	 WHERE ba.book_id = b.id) as authors,
     
	(SELECT GROUP_CONCAT(g.name SEPARATOR ', ')
	 FROM book_genre bg INNER JOIN genre g ON bg.genre_id = g.id
     WHERE bg.book_id = b.id) as genres,
     
	(SELECT p.name
     FROM publisher p
     WHERE b.publisher_id = p.id) publisher
FROM book b;


-- Books rating by bookmarks
SELECT b.id, b.title, dense_rank() over (order by COUNT(*) DESC) as place
FROM book b
	INNER JOIN bookmark bm ON bm.book_id = b.id
GROUP BY b.id;


-- Books rating by review
SELECT b.id, b.title, 
	dense_rank() over (order by avg(r.rating) DESC) as place, 
    round(avg(r.rating), 2) as rating, 
    COUNT(*) as review_number
FROM book b
	INNER JOIN review r ON r.book_id = b.id
GROUP BY b.id;


-- Books' rating by genre
SELECT g.name, round(avg(rating), 2) as rating, 
	dense_rank() over (order by avg(rating) desc) as place
FROM book_genre bg 
    INNER JOIN genre g ON g.id = bg.genre_id
    INNER JOIN review r ON r.book_id = bg.book_id
GROUP BY genre_id;


-- Books' rating by publisher
SELECT DISTINCT p.name as publisher, 
	avg(r.rating) over (partition by b.publisher_id) as average_rating
FROM book b 
	INNER JOIN publisher p ON b.publisher_id = p.id
    INNER JOIN review r ON r.book_id = b.id;
    
    
-- Books with their instance number
SELECT bf.book_id, b.title, COUNT(*) instances
FROM book_file bf 
	INNER JOIN book b ON b.id = bf.book_id
GROUP BY book_id;


-- Books that are being read
SELECT b.id, b.title
FROM book b 
WHERE EXISTS 
	(SELECT 1 
     FROM bookmark bm 
     WHERE bm.book_id = b.id);


-- Users with Profiles
SELECT id, username, email, 
	if(is_active, 'Yes', 'No') is_active, 
    CASE
		WHEN is_admin THEN 'Yes'
        ELSE 'No'
    END is_admin,
    CONCAT(first_name, ' ', last_name) as name, birth_date
FROM user u
	LEFT OUTER JOIN user_profile p ON p.user_id = u.id;
    
    
-- Users' bookmark number
SELECT u.id, u.username, COUNT(b.user_id) as boomkarks, 
	dense_rank() over (order by COUNT(b.user_id) DESC) as place
FROM user u
	LEFT OUTER JOIN bookmark b ON b.user_id = u.id
GROUP BY u.id;


-- Publisher's books quantity
SELECT 
	(SELECT name 
     FROM publisher 
     WHERE id = publisher_id) publisher, 
     COUNT(*) as books
FROM book b
GROUP BY publisher_id WITH ROLLUP;
-- HAVING books > 6;


-- Book files with PDF / ePub format
SELECT *
FROM book_file 
WHERE book_format_id IN 
	(SELECT id 
     FROM book_format 
	 WHERE abbreviation IN ('pdf', 'epub'));
     
     
-- Authors with genres
WITH 
	books_authors AS
	(SELECT book_id, CONCAT_WS(' ', a.first_name, a.last_name) as author_name
     FROM book_author ba 
		 INNER JOIN author a ON ba.author_id = a.id
         INNER JOIN book b ON ba.book_id = b.id),
    books_genres AS
    (SELECT book_id, g.name
     FROM book_genre bg
		INNER JOIN genre g ON bg.genre_id = g.id
        INNER JOIN book b ON bg.book_id = b.id)
SELECT ba.author_name as author, GROUP_CONCAT(bg.name SEPARATOR ', ') as genres
FROM books_authors ba 
	INNER JOIN books_genres bg USING(book_id)
GROUP BY ba.author_name;


-- Publisher's rating
SELECT p.name as publisher, avg(r.rating) as rating, 
	dense_rank() over (order by avg(r.rating) desc) as place
FROM book b 
	INNER JOIN publisher p ON b.publisher_id = p.id
    INNER JOIN review r ON r.book_id = b.id
GROUP BY p.id;


-- Union between user_profile and author
SELECT first_name, last_name, 'user' as who
FROM user_profile
UNION
SELECT first_name, last_name, 'author'
FROM author;