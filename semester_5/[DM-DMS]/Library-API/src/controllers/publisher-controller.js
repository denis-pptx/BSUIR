const ApiError = require('../exceptions/api-error');
const pool = require('../db/connection-pool');

const PublisherController = {
    getAll: async (req, res, next) => {
        try {
            const [rows] = await pool.query('SELECT * FROM publisher');
            res.json(rows);
        } catch (e) {
            next(e);
        } 
    },

    getById: async (req, res, next) => {
        const id = req.params.id;

        try {
            const [rows] = await pool.query('SELECT * FROM publisher WHERE id = ?', [id]);

            if (!rows.length) {
                return next(ApiError.NotFound("Publisher not found"));
            }

            res.status(200).json(rows[0]);
        } catch (e) {
            next(e);
        } 
    },

    create: async (req, res, next) => {
        const { name, description } = req.body;
        try {
            await pool.query('INSERT INTO publisher (name, description) VALUES (?, ?)', [name, description]);
            res.status(201).json({message: 'Publisher created successfully'});
        } catch (e) {
            next(e);
        } 
    },

    update: async (req, res, next) => {
        const id = req.params.id;
        const { name, description } = req.body;

        try {
            const [result] = await pool.query('UPDATE publisher SET name = ?, description = ? WHERE id = ?', [name, description, id]);

            if (!result.affectedRows) {
                return next(ApiError.NotFound("Publisher not found"));
            }

            res.status(200).json({message: 'Publisher updated successfully'});
        } catch (e) {
            next(e);
        } 
    },

    delete: async (req, res, next) => {
        const id = req.params.id;

        try {
            const [result] = await pool.query('DELETE FROM publisher WHERE id = ?', [id]);
            
            if (!result.affectedRows) {
                return next(ApiError.NotFound("Publisher not found"));
            }

            res.status(200).json({message: 'Publisher deleted successfully'});
        } catch (e) {
            next(e);
        } 
    }
};

module.exports = PublisherController;
