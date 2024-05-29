const ApiError = require('../exceptions/api-error');
const pool = require('../db/connection-pool');

const LanguageController = {
    getAll: async (req, res, next) => {
        try {
            const [rows] = await pool.query('SELECT * FROM language');
            res.json(rows);
        } catch (e) {
            next(e);
        } 
    },

    getById: async (req, res, next) => {
        const id = req.params.id;

        try {
            const [rows] = await pool.query('SELECT * FROM language WHERE id = ?', [id]);

            if (!rows.length) {
                return next(ApiError.NotFound("Language not found"));
            }

            res.status(200).json(rows[0]);
        } catch (e) {
            next(e);
        } 
    },

    create: async (req, res, next) => {
        const { name } = req.body;
        try {
            await pool.query('INSERT INTO language (name) VALUES (?)', [name]);
            res.status(201).json({message: 'Language created successfully'});
        } catch (e) {
            next(e);
        } 
    },

    update: async (req, res, next) => {
        const id = req.params.id;
        const { name } = req.body;

        try {
            const [result] = await pool.query('UPDATE language SET name = ? WHERE id = ?', [name, id]);

            if (!result.affectedRows) {
                return next(ApiError.NotFound("Language not found"));
            }

            res.status(200).json({message: 'Language updated successfully'});
        } catch (e) {
            next(e);
        } 
    },

    delete: async (req, res, next) => {
        const id = req.params.id;

        try {
            const [result] = await pool.query('DELETE FROM language WHERE id = ?', [id]);
            
            if (!result.affectedRows) {
                return next(ApiError.NotFound("Language not found"));
            }

            res.status(200).json({message: 'Language deleted successfully'});
        } catch (e) {
            next(e);
        } 
    }
};

module.exports = LanguageController;
