#ifndef GCONSTANTS
#define GCONSTANTS


const int MAX_MAILS = 20,//Mails per user
		MAX_ELEMS = 20,//Elems on the list
		MAX_USERS = 20,//N of users
		MAX_RECIPIENTS = 10,//N of users who can be sent the same mail at once
		MAX_FASTNAMES = 10,
		HORIZONTAL = 79,
		CENSORED_CHARS = 26,
		PASSWORD_MIN_LENGTH = 5;

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