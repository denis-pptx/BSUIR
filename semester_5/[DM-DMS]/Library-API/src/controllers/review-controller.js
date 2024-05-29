const ApiError = require('../exceptions/api-error');
const pool = require('../db/connection-pool');

const ReviewController = {
    getAll: async (req, res, next) => {
        try {
            const [rows] = await pool.query('SELECT * FROM review');
            res.json(rows);
        } catch (e) {
            next(e);
        }
    },

    getById: async (req, res, next) => {
        const id = req.params.id;

        try {
            const [rows] = await pool.query('SELECT * FROM review WHERE id = ?', [id]);

            if (!rows.length) {
                return next(ApiError.NotFound("Review not found"));
            }

            res.status(200).json(rows[0]);
        } catch (e) {
            next(e);
        }
    },

    create: async (req, res, next) => {
        const { text, rating, book_id } = req.body;
        const user_id = req.user.id;

        try {
            const query = `
                INSERT INTO review (text, rating, user_id, book_id)
                VALUES (?, ?, ?, ?)
            `;

            await pool.query(query, [text, rating, user_id, book_id]);

            res.status(201).json({ message: 'Review created successfully' });
        } catch (e) {
            next(e);
        }
    },

    update: async (req, res, next) => {
        const id = req.params.id;
        const { text, rating, book_id } = req.body;
        const user_id = req.user.id;

        try {
            const query = `
                UPDATE review
                SET text = ?, rating = ?, book_id = ?
                WHERE (id, user_id) = (?, ?)
            `;

            const [result] = await pool.query(query, [text, rating, book_id, id, user_id]);

            if (!result.affectedRows) {
                return next(ApiError.NotFound("Review for current user not found"));
            }

            res.status(200).json({ message: 'Review updated successfully' });
        } catch (e) {
            next(e);
        }
    },

    delete: async (req, res, next) => {
        const id = req.params.id;
        const user_id = req.user.id;

        try {
            if (req.user.is_admin) {
                const [result] = await pool.query('DELETE FROM review WHERE id = ?', [id]);

                if (!result.affectedRows) {
                    return next(ApiError.NotFound("Review not found"));
                }
            }
            else {
                const [result] = await pool.query('DELETE FROM review WHERE (id, user_id) = (?, ?)', [id, user_id]);

                if (!result.affectedRows) {
                    return next(ApiError.NotFound("Review for current user not found"));
                }
            }


            res.status(200).json({ message: 'Review deleted successfully' });
        } catch (e) {
            next(e);
        }
    }
};

module.exports = ReviewController;
