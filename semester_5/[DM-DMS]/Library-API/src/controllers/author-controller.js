const ApiError = require('../exceptions/api-error');
const pool = require('../db/connection-pool');

const AuthorController = {
    getAll: async (req, res, next) => {
        try {
            const [rows] = await pool.query('SELECT * FROM author');
            res.json(rows);
        } catch (e) {
            next(e);
        }
    },

    getById: async (req, res, next) => {
        const id = req.params.id;

        try {
            const [rows] = await pool.query('SELECT * FROM author WHERE id = ?', [id]);

            if (!rows.length) {
                return next(ApiError.BadRequest("Author not found"));
            }

            res.status(200).json(rows[0]);
        } catch (e) {
            next(e);
        }
    },

    create: async (req, res, next) => {
        const { first_name, last_name, birth_date } = req.body;
        try {
            const query = `
                INSERT INTO author(first_name, last_name, birth_date)
                VALUES (?, ?, ?)
            `;

            await pool.query(query, [first_name, last_name, birth_date]);

            res.status(201).json({ message: 'Author created successfully' });
        } catch (e) {
            next(e);
        }
    },

    update: async (req, res, next) => {
        const id = req.params.id;
        const { first_name, last_name, birth_date } = req.body;

        try {
            const query = `
                UPDATE author
                SET first_name = ?, last_name = ?, birth_date = ?
                WHERE id = ?
            `;

            const [result] = await pool.query(query, [first_name, last_name, birth_date, id]);

            if (!result.affectedRows) {
                return next(ApiError.BadRequest("Author not found"));
            }

            res.status(200).json({ message: 'Author updated successfully' });
        } catch (e) {
            next(e);
        }
    },

    delete: async (req, res, next) => {
        const id = req.params.id;

        try {
            const [result] = await pool.query('DELETE FROM author WHERE id = ?', [id]);

            if (!result.affectedRows) {
                return next(ApiError.BadRequest("Author not found"));
            }

            res.status(200).json({ message: 'Author deleted successfully' });
        } catch (e) {
            next(e);
        }
    }
};

module.exports = AuthorController;
