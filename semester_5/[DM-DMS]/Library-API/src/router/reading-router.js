const router = require('express').Router();
const controller = require('../controllers/reading-controller');
const authMiddleware = require('../middleware/auth-middleware');

router.get('/', controller.getAll);
router.get('/:id', controller.getById);
router.post('/', authMiddleware, controller.create);
router.delete('/:id', authMiddleware, controller.delete);

module.exports = router;
