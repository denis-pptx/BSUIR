const ApiError = require('../exceptions/api-error');
const pool = require('../db/connection-pool');

const BookFileController = {
    getAll: async (req, res, next) => {
        try {
            const [rows] = await pool.query('SELECT * FROM book_file');
            res.json(rows);
        } catch (e) {
            next(e);
        } 
    },

    getById: async (req, res, next) => {
        const id = req.params.id;

        try {
            const [rows] = await pool.query('SELECT * FROM book_file WHERE id = ?', [id]);

            if (!rows.length) {
                return next(ApiError.NotFound("Book file not found"));
            }

            res.status(200).json(rows[0]);
        } catch (e) {
            next(e);
        } 
    },

    create: async (req, res, next) => {
        const { path, book_id, book_format_id } = req.body;
        try {
            const query = `
                INSERT INTO book_file (path, book_id, book_format_id)
                VALUES (?, ?, ?)
            `;

            await pool.query(query, [path, book_id, book_format_id]);

            res.status(201).json({message: 'Book file created successfully'});
        } catch (e) {
            next(e);
        } 
    },

    update: async (req, res, next) => {
        const id = req.params.id;
        const { path, book_id, book_format_id } = req.body;

        try {
            const query = `
                UPDATE book_file
                SET path = ?, book_id = ?, book_format_id = ?
                WHERE id = ?
            `;

            const [result] = await pool.query(query, [path, book_id, book_format_id, id]);

            if (!result.affectedRows) {
                return next(ApiError.NotFound("Book file not found"));
            }

            res.status(200).json({message: 'Book file updated successfully'});
        } catch (e) {
            next(e);
        } 
    },

    delete: async (req, res, next) => {
        const id = req.params.id;

        try {
            const [result] = await pool.query('DELETE FROM book_file WHERE id = ?', [id]);
            
            if (!result.affectedRows) {
                return next(ApiError.NotFound("Book file not found"));
            }

            res.status(200).json({message: 'Book file deleted successfully'});
        } catch (e) {
            next(e);
        } 
    }
};

module.exports = BookFileController;
