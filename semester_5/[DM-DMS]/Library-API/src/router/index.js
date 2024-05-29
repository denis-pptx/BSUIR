const router = require('express').Router();

router.use('/auth', require('./auth-router'));
router.use('/genre', require('./genre-router'));
router.use('/publisher', require('./publisher-router'));
router.use('/author', require('./author-router'));
router.use('/language', require('./language-router'));
router.use('/book_format', require('./book-format-router'));
router.use('/book_file', require('./book-file-router'));
router.use('/book', require('./book-router'));
router.use('/review', require('./review-router'));
router.use('/bookmark', require('./bookmark-router'));
router.use('/reading', require('./reading-router'));
router.use('/user', require('./user-router'));
router.use('/user_profile', require('./user-profile-router'));
router.use('/complex_queries', require('./complex-queries-router'));

module.exports = router;