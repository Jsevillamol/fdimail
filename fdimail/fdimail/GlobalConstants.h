#ifndef GCONSTANTS
#define GCONSTANTS


const int 
	START_ELEM = 10,
	MAILS_X_PAGE = 10,
	MAX_USERS = 20,//N of users
	MAX_RECIPIENTS = 10,//N of users who can be sent the same mail at once
	MAX_FASTNAMES = 10,
	HORIZONTAL = 79,
	CENSORED_CHARS = 26,
	PASSWORD_MIN_LENGTH = 4;

const char forbidden[CENSORED_CHARS] =
{
	',', ';', '.', ':', '-',
	'_', '{', '}', '[', ']', 
	'*', '/', '?', '=', ')',
	'(', '&', '%', '$', '#',
	'@', '"', '|', '!', ' ',
	'+'
};

#endif // !GCONSTANTS