DECLARATIVE_SENTENCE_END_SIGNS: list[str] = ['.', '...']
NON_DECLARATIVE_SENTENCE_END_SIGNS: list[str] = ['!', '?']
SENTENCE_END_SINGS = DECLARATIVE_SENTENCE_END_SIGNS + NON_DECLARATIVE_SENTENCE_END_SIGNS
PUNCTUATION_SIGNS: list[str] = [',', ':', ';', "'", '(', ')', '—', '–', '−', '-', '"'] + SENTENCE_END_SINGS
NOT_SENTENCE_END_ABBREVIATIONS: list[str] = ['mr.', 'mrs.', 'ms.', 'miss.', 'jr.', 'sr.',
                                             'v.i.p.', 'i.e.', 'vs.', 'p.s', 'a.m.', 'p.m.']
