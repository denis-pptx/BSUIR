const ApiError = require('../exceptions/api-error');
const pool = require('../db/connection-pool');

const BookmarkController = {
    getAll: async (req, res, next) => {
        try {
            const [rows] = await pool.query('SELECT * FROM bookmark');
            res.json(rows);
        } catch (e) {
            next(e);
        }
    },

    getById: async (req, res, next) => {
        const id = req.params.id;
        try {
            const [rows] = await pool.query('SELECT * FROM bookmark WHERE id = ?', [id]);

            if (!rows.length) {
                return next(ApiError.NotFound("Bookmark not found"));
            }

            res.status(200).json(rows[0]);
        } catch (e) {
            next(e);
        }
    },

    create: async (req, res, next) => {
        const { page_number, book_id } = req.body;
        const user_id = req.user.id;

        try {
            const query = `
                INSERT INTO bookmark (page_number, book_id, user_id)
                VALUES (?, ?, ?)
            `;

            await pool.query(query, [page_number, book_id, user_id]);

            res.status(201).json({ message: 'Bookmark created successfully' });
        } catch (e) {
            next(e);
        }
    },

    delete: async (req, res, next) => {
        const id = req.params.id;
        const user_id = req.user.id;

        try {
            const [result] = await pool.query('DELETE FROM bookmark WHERE (id, user_id) = (?, ?)', [id, user_id]);

            if (!result.affectedRows) {
                return next(ApiError.NotFound("Bookmark for current user not found"));
            }
            
            res.status(200).json({ message: 'Bookmark deleted successfully' });
        } catch (e) {
            next(e);
        }
    }
};

module.exports = BookmarkController;
