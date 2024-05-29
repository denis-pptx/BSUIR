const ApiError = require('../exceptions/api-error');
const pool = require('../db/connection-pool');

const BookController = {
    getAll: async (req, res, next) => {
        const { language_id, author_id, genre_id, publisher_id } = req.query;

        try {
            const [rows] = await pool.query('CALL GetBooksByParameters(?, ?, ?, ?)', [language_id, author_id, genre_id, publisher_id]);

            res.json(rows[0]);
        } catch (e) {
            next(e);
        }
    },

    getById: async (req, res, next) => {
        const id = req.params.id;

        try {
            const [rows] = await pool.query('SELECT * FROM book WHERE id = ?', [id]);

            if (!rows.length) {
                return next(ApiError.NotFound("Book not found"));
            }

            res.status(200).json(rows[0]);
        } catch (e) {
            next(e);
        }
    },

    create: async (req, res, next) => {
        const { title, description, publication_date, isbn, is_available, publisher_id } = req.body;

        try {
            const query = `
                INSERT INTO book(title, description, publication_date, isbn, is_available, publisher_id)
                VALUES (?, ?, ?, ?, ?, ?)
            `;

            await pool.query(query, [title, description, publication_date, isbn, is_available, publisher_id]);

            res.status(201).json({ message: 'Book created successfully' });
        } catch (e) {
            next(e);
        }
    },

    update: async (req, res, next) => {
        const id = req.params.id;
        const { title, description, publication_date, isbn, is_available, publisher_id } = req.body;

        try {
            const query = `
                UPDATE book
                SET title = ?, description = ?, publication_date = ?, isbn = ?, is_available = ?, publisher_id = ?
                WHERE id = ?
            `;

            const [result] = await pool.query(query, [title, description, publication_date, isbn, is_available, publisher_id, id]);

            if (!result.affectedRows) {
                return next(ApiError.NotFound("Book not found"));
            }

            res.status(200).json({ message: 'Book updated successfully' });
        } catch (e) {
            next(e);
        }
    },

    delete: async (req, res, next) => {
        const id = req.params.id;

        try {
            const [result] = await pool.query('DELETE FROM book WHERE id = ?', [id]);

            if (!result.affectedRows) {
                return next(ApiError.NotFound("Book not found"));
            }

            res.status(200).json({ message: 'Book deleted successfully' });
        } catch (e) {
            next(e);
        }
    },

    add_language: async (req, res, next) => {
        const { book_id, language_id } = req.body;

        try {
            const query = `
                INSERT INTO book_language (book_id, language_id)
                VALUES (?, ?)
            `;

            await pool.query(query, [book_id, language_id]);

            res.status(200).json({ message: 'Language added to book successfully' });
        } catch (e) {
            next(e);
        }
    },

    remove_language: async (req, res, next) => {
        const { book_id, language_id } = req.body;

        try {
            const query = `
                DELETE FROM book_language
                WHERE (book_id, language_id) = (?, ?)
            `;

            const [result] = await pool.query(query, [book_id, language_id]);

            if (!result.affectedRows) {
                return next(ApiError.NotFound("Book with so language not found"));
            }

            res.status(200).json({ message: 'Language removed from successfully' });
        } catch (e) {
            next(e);
        }
    },

    add_author: async (req, res, next) => {
        const { book_id, author_id } = req.body;

        try {
            const query = `
                INSERT INTO book_author (book_id, author_id)
                VALUES (?, ?)
            `;

            await pool.query(query, [book_id, author_id]);

            res.status(200).json({ message: 'Author added to book successfully' });
        } catch (e) {
            next(e);
        }
    },

    remove_author: async (req, res, next) => {
        const { book_id, author_id } = req.body;

        try {
            const query = `
                DELETE FROM book_author
                WHERE (book_id, author_id) = (?, ?)
            `;

            const [result] = await pool.query(query, [book_id, author_id]);

            if (!result.affectedRows) {
                return next(ApiError.NotFound("Book with so author not found"));
            }

            res.status(200).json({ message: 'Author removed from book successfully' });
        } catch (e) {
            next(e);
        }
    },

    add_genre: async (req, res, next) => {
        const { book_id, genre_id } = req.body;

        try {
            const query = `
                INSERT INTO book_genre (book_id, genre_id)
                VALUES (?, ?)
            `;

            await pool.query(query, [book_id, genre_id]);

            res.status(200).json({ message: 'Genre added to book successfully' });
        } catch (e) {
            next(e);
        }
    },

    remove_genre: async (req, res, next) => {
        const { book_id, genre_id } = req.body;

        try {
            const query = `
                DELETE FROM book_genre
                WHERE (book_id, genre_id) = (?, ?)
            `;

            const [result] = await pool.query(query, [book_id, genre_id]);

            if (!result.affectedRows) {
                return next(ApiError.NotFound("Book with so genre not found"));
            }

            res.status(200).json({ message: 'Genre removed from book successfully' });
        } catch (e) {
            next(e);
        }
    }

};

module.exports = BookController;
