const ApiError = require('../exceptions/api-error');
const pool = require('../db/connection-pool');

const UserProfileController = {
    getAll: async (req, res, next) => {
        try {
            const [rows] = await pool.query('SELECT * FROM user_profile');
            res.json(rows);
        } catch (e) {
            next(e);
        }
    },

    getById: async (req, res, next) => {
        const user_id = req.params.id;

        try {
            if (!req.user.is_admin && user_id != req.user.id) {
                return next(ApiError.Forbidden());
            }

            const [rows] = await pool.query('SELECT * FROM user_profile WHERE user_id = ?', [user_id]);

            if (!rows.length) {
                return next(ApiError.NotFound("User profile not found"));
            }

            res.status(200).json(rows[0]);
        } catch (e) {
            next(e);
        }
    },

    create: async (req, res, next) => {
        let { user_id, first_name, last_name, brith_date } = req.body;

        try {
            if (!req.user.is_admin)
                user_id = req.user.id;

            const query = `
                INSERT INTO user_profile (user_id, first_name, last_name, birth_date)
                VALUES (?, ?, ?, ?);
            `;

            await pool.query(query, [user_id, first_name, last_name, brith_date]);

            res.status(201).json({ message: 'User profile created successfully' });
        } catch (e) {
            next(e);
        }
    },

    update: async (req, res, next) => {
        const user_id = req.params.id;
        const { first_name, last_name, brith_date } = req.body;

        try {
            if (!req.user.is_admin && user_id != req.user.id) {
                return next(ApiError.Forbidden());
            }

            const query = `
                UPDATE user_profile
                SET first_name = ?, last_name = ?, birth_date = ?
                WHERE user_id = ?;
            `;

            await pool.query(query, [first_name, last_name, brith_date, user_id]);

            res.status(200).json({ message: 'User profile updated successfully' });
        } catch (e) {
            next(e);
        }
    },

    delete: async (req, res, next) => {
        const user_id = req.params.id;

        try {
            
            if (!req.user.is_admin && user_id != req.user.id) {
                return next(ApiError.Forbidden());
            }

            const [result] = await pool.query('DELETE FROM user_profile WHERE user_id = ?', [user_id]);

            if (!result.affectedRows) {
                return next(ApiError.NotFound("User profile not found"));
            }

            res.status(200).json({ message: 'User profile deleted successfully' });
        } catch (e) {
            next(e);
        }
    }
};

module.exports = UserProfileController;
