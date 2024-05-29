const router = require('express').Router();
const controller = require('../controllers/complex-queries-controller');

router.get('/allBookInfo1', controller.getAllBookInfo1);
router.get('/allBookInfo2', controller.getAllBookInfo2);
router.get('/booksRatingByBookmarks', controller.getBooksRatingByBookmarks);
router.get('/booksRatingByReview', controller.getBooksRatingByReview);
router.get('/booksRatingByGenre', controller.getBooksRatingByGenre);
router.get('/booksRatingByPublisher', controller.getBooksRatingByPublisher);
router.get('/booksInstanceNumber', controller.getBooksInstanceNumber);
router.get('/booksBeingRead', controller.getBooksBeingRead);
router.get('/usersWithProfiles', controller.getUsersWithProfiles);
router.get('/usersBookmarkNumber', controller.getUsersBookmarkNumber);
router.get('/publishersBooksQuantity', controller.getPublishersBooksQuantity);
router.get('/bookFilesWithFormats', controller.getBookFilesWithFormats);
router.get('/authorsWithGenres', controller.getAuthorsWithGenres);
router.get('/publishersRating', controller.getPublishersRating);
router.get('/unionUserProfileAndAuthor', controller.getUnionUserProfileAndAuthor);

module.exports = router;
