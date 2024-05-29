const ApiError = require('../exceptions/api-error');
const pool = require('../db/connection-pool');

const BookFormatController = {
    getAll: async (req, res, next) => {
        try {
            const [rows] = await pool.query('SELECT * FROM book_format');
            res.json(rows);
        } catch (e) {
            next(e);
        } 
    },

    getById: async (req, res, next) => {
        const id = req.params.id;

        try {
            const [rows] = await pool.query('SELECT * FROM book_format WHERE id = ?', [id]);

            if (!rows.length) {
                return next(ApiError.NotFound("Book format not found"));
            }

            res.status(200).json(rows[0]);
        } catch (e) {
            next(e);
        } 
    },

    create: async (req, res, next) => {
        const { abbreviation, description } = req.body;
        try {
            await pool.query('INSERT INTO book_format (abbreviation, description) VALUES (?, ?)', [abbreviation, description]);
            res.status(201).json({message: 'Book format created successfully'});
        } catch (e) {
            next(e);
        } 
    },

    update: async (req, res, next) => {
        const id = req.params.id;
        const { abbreviation, description } = req.body;

        try {
            const [result] = await pool.query('UPDATE book_format SET abbreviation = ?, description = ? WHERE id = ?', [abbreviation, description, id]);

            if (!result.affectedRows) {
                return next(ApiError.NotFound("Book format not found"));
            }

            res.status(200).json({message: 'Book format updated successfully'});
        } catch (e) {
            next(e);
        } 
    },

    delete: async (req, res, next) => {
        const id = req.params.id;

        try {
            const [result] = await pool.query('DELETE FROM book_format WHERE id = ?', [id]);
            
            if (!result.affectedRows) {
                return next(ApiError.NotFound("Book format not found"));
            }

            res.status(200).json({message: 'Book format deleted successfully'});
        } catch (e) {
            next(e);
        } 
    }
};

module.exports = BookFormatController;
