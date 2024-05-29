create view temp as 
WITH user_stats AS
	(SELECT u.username, l.name, COUNT(*) as number
	FROM reading r
		INNER JOIN user u ON u.id = r.user_id
		INNER JOIN book b ON b.id = r.book_id
		INNER JOIN book_language bl ON bl.book_id = b.id
		INNER JOIN language l ON bl.language_id = l.id
	GROUP BY u.id, l.id)
SELECT us.username, us.name, us.number, dense_rank() over (partition by us.username order by us.number desc) as place
FROM user_stats as us;

SELECT username, name, number
FROM temp
WHERE place = 1;