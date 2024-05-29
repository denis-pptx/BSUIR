const ApiError = require('../exceptions/api-error');
const pool = require('../db/connection-pool');

const ReadingController = {
    getAll: async (req, res, next) => {
        try {
            const [rows] = await pool.query('SELECT * FROM reading');
            res.json(rows);
        } catch (e) {
            next(e);
        }
    },

    getById: async (req, res, next) => {
        const id = req.params.id;
        try {
            const [rows] = await pool.query('SELECT * FROM reading WHERE id = ?', [id]);

            if (!rows.length) {
                return next(ApiError.NotFound("Reading not found"));
            }

            res.status(200).json(rows[0]);
        } catch (e) {
            next(e);
        }
    },

    create: async (req, res, next) => {
        const { book_id } = req.body;
        const user_id = req.user.id;

        try {
            const query = `
                INSERT INTO reading (book_id, user_id)
                VALUES (?, ?)
            `;

            await pool.query(query, [book_id, user_id]);

            res.status(201).json({ message: 'Reading created successfully' });
        } catch (e) {
            next(e);
        }
    },

    delete: async (req, res, next) => {
        const id = req.params.id;
        const user_id = req.user.id;

        try {
            const [result] = await pool.query('DELETE FROM reading WHERE (id, user_id) = (?, ?)', [id, user_id]);

            if (!result.affectedRows) {
                return next(ApiError.NotFound("Reading for current user not found"));
            }
            
            res.status(200).json({ message: 'Reading deleted successfully' });
        } catch (e) {
            next(e);
        }
    }
};

module.exports = ReadingController;
