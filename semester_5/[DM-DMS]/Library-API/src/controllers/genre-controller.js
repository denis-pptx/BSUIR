const ApiError = require('../exceptions/api-error');
const pool = require('../db/connection-pool');

const GenreController = {
    getAll: async (req, res, next) => {
        try {
            const [rows] = await pool.query('SELECT * FROM genre');
            res.json(rows);
        } catch (e) {
            next(e);
        } 
    },

    getById: async (req, res, next) => {
        const id = req.params.id;

        try {
            const [rows] = await pool.query('SELECT * FROM genre WHERE id = ?', [id]);

            if (!rows.length) {
                return next(ApiError.NotFound("Genre not found"));
            }

            res.status(200).json(rows[0]);
        } catch (e) {
            next(e);
        } 
    },

    create: async (req, res, next) => {
        const { name } = req.body;
        try {
            await pool.query('INSERT INTO genre (name) VALUES (?)', [name]);
            res.status(201).json({message: 'Genre created successfully'});
        } catch (e) {
            next(e);
        } 
    },

    update: async (req, res, next) => {
        const id = req.params.id;
        const { name } = req.body;

        try {
            const [result] = await pool.query('UPDATE genre SET name = ? WHERE id = ?', [name, id]);

            if (!result.affectedRows) {
                return next(ApiError.NotFound("Genre not found"));
            }

            res.status(200).json({message: 'Genre updated successfully'});
        } catch (e) {
            next(e);
        } 
    },

    delete: async (req, res, next) => {
        const id = req.params.id;

        try {
            const [result] = await pool.query('DELETE FROM genre WHERE id = ?', [id]);
            
            if (!result.affectedRows) {
                return next(ApiError.NotFound("Genre not found"));
            }

            res.status(200).json({message: 'Genre deleted successfully'});
        } catch (e) {
            next(e);
        } 
    }
};

module.exports = GenreController;
