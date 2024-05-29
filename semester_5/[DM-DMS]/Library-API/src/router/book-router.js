const router = require('express').Router();
const controller = require('../controllers/book-controller');
const authMiddleware = require('../middleware/auth-middleware');
const adminMiddleware = require('../middleware/admin-middleware');


router.post('/language', [authMiddleware, adminMiddleware], controller.add_language);
router.delete('/language', [authMiddleware, adminMiddleware], controller.remove_language);

router.post('/author', [authMiddleware, adminMiddleware], controller.add_author);
router.delete('/author', [authMiddleware, adminMiddleware], controller.remove_author);

router.post('/genre', [authMiddleware, adminMiddleware], controller.add_genre);
router.delete('/genre', [authMiddleware, adminMiddleware], controller.remove_genre);

router.get('/', controller.getAll);
router.get('/:id', controller.getById);
router.post('/', [authMiddleware, adminMiddleware], controller.create);
router.put('/:id', [authMiddleware, adminMiddleware], controller.update);
router.delete('/:id', [authMiddleware, adminMiddleware], controller.delete);



module.exports = router;
