#include "kalgoritm.h"
#include <cstring>
#include <memory.h>
#include <stdlib.h>
/*!
 * Namespace by Kozura(c) Inc.
 */
namespace kzr {
bool fuzzySearch(const char* pattern, const char* string) {
	if (!pattern || !string || *pattern == '\0') {
		return false;
	}

	const char* b = pattern;
	const char* s = string;

	while ( *s != '\0' ) {
		if (*b == *s) {
			++b;
			if (*b == '\0') {
				return true;
			}
		}
		++s;
	}
	return false;
}

bool strictSearch(const char* pattern, const char* string) {
	if (!pattern || !string) {
		return false;
	}

	int sz1 = strlen(pattern);
	int sz2 = strlen(string);

	if (string[sz2-1] == '\n') {
		--sz2;
	}

	if (sz1 != sz2) {
		return false;
	}

	const char* b = pattern;
	const char* s = string;

	while ( *s != '\0' && *s != '\n' ) {
		if (*b == *s) {
			++b;
			++s;
		} else {
			return false;
		}
	}
	return true;
}

bool otherSearch(const RegExp& rgxp, const char* string) {
	if (!rgxp.val.size() || !string || rgxp.val.at(0) == '\0') {
		return false;
	}

	if (rgxp.beg == smAsterisk && rgxp.end != smAsterisk) {
		const char* b = rgxp.val.c_str();
		const char* s = string;
		uint_t index = 0;

		while ( *s != '\0' && *s != '\n' ) {
			if (*b == *s) {
				++b;
				++index;
			} else {
				if ( (index >= rgxp.val.size()-1)
					 && (*s != '\0' && *s != '\n')
					 && (rgxp.end == smQuestion) )
				{
					return true;
				}
			}
			++s;
		}
	}

	if (rgxp.beg != smAsterisk && rgxp.end == smAsterisk) {
		const char* b = rgxp.val.c_str();
		const char* s = string;
		uint_t index = 0;

		while ( *s != '\0' && *s != '\n' ) {
			++index;

			if (*b == *s) {
				++b;
				if (index >= rgxp.val.size()) {
					return true;
				}
			} else {
				if (rgxp.beg != smQuestion && index < rgxp.val.size()-1) {
					return false;
				}

				if (index > 1) {
					return false;
				}
			}
			++s;
		}
	}
	return false;
}

bool regExpQuery(const RegExp& rgxp, const char* string) {
	if ( rgxp.beg == smAsterisk && rgxp.end == smAsterisk ) {
		return fuzzySearch( rgxp.val.c_str(), string );
	} else if ( rgxp.beg == smNone && rgxp.end == smNone ) {
		return strictSearch( rgxp.val.c_str(), string );
	}
	return otherSearch( rgxp, string );
}

RedExpArray_t findSearchMask(const char* in_str, bool* res) {
	if (res) {
		*res = false;
	}

	const uint_t str_sz = strlen(in_str);

	RedExpArray_t rgxp_array;

	if (!str_sz) {
		return rgxp_array;
	}

	char* prstr = new char[str_sz];
	memset(prstr, 0, str_sz);

	uchar_t c;
	const char* c_it = in_str;
	uint_t ast_cnt = 0, qst_cnt = 0, pos = 0;

	RegExp rgxp;

	while ( *c_it != '\0') {
		c = *c_it;
		++c_it;

		if ( (c > 0 && c < 32) ) {
			delete[] prstr;
			rgxp_array.clear();
			return rgxp_array;
		}

		if ( c == '*' ) {
			++ast_cnt;

			if ( ast_cnt && !(ast_cnt % 2) ) {
				prstr[pos++] = '*';
			}

			if (*c_it == '\0') {
				if ( rgxp.beg == smEmpty ) {
					rgxp.beg = smNone;
				}

				if ( ast_cnt % 2 ) {
					rgxp.end = smAsterisk;

					if ( str_sz == 1 ) {
						rgxp.beg = smAsterisk;
					}
				} else {
					rgxp.end = smNone;
				}

				rgxp.val = prstr;
				rgxp_array.addItem(rgxp);
			}
		} else if ( c == '?' ) {
			++qst_cnt;

			if ( qst_cnt && !(qst_cnt % 2) ) {
				prstr[pos++] = '?';
			}

			if (*c_it == '\0') {
				if ( rgxp.beg == smEmpty ) {
					rgxp.beg = smNone;
				}

				if ( qst_cnt % 2 ) {
					rgxp.end = smQuestion;
				} else {
					rgxp.end = smNone;
				}

				rgxp.val = prstr;
				rgxp_array.addItem(rgxp);
			}
		} else {
			if ( ast_cnt ) {
				if ( ast_cnt % 2 ) {
					if ( rgxp.beg == smEmpty ) {
						rgxp.beg = smAsterisk;
					} else if ( rgxp.end == smEmpty ) {
						rgxp.end = smAsterisk;
						rgxp.val = prstr;
						rgxp_array.addItem(rgxp);
						pos = 0;
						memset(prstr, 0, str_sz);
						rgxp.reset();
						rgxp.beg = smAsterisk;
					}
				} else if ( rgxp.beg == smEmpty ) {
					rgxp.beg = smNone;
				}

				prstr[pos++] = c;
				ast_cnt = 0;
			} else if ( qst_cnt ) {
				if ( qst_cnt % 2 ) {
					if ( rgxp.beg == smEmpty ) {
						rgxp.beg = smAsterisk;
					} else if ( rgxp.end == smEmpty ) {
						rgxp.end = smAsterisk;
						rgxp.val = prstr;
						rgxp_array.addItem(rgxp);
						pos = 0;
						memset(prstr, 0, str_sz);
						rgxp.reset();
						rgxp.beg = smAsterisk;
					}
				} else if ( rgxp.beg == smEmpty ) {
					rgxp.beg = smNone;
				}

				prstr[pos++] = c;
				qst_cnt = 0;
			} else {
				prstr[pos++] = c;

				if ( *c_it == '\0' ) {
					if ( rgxp.beg == smEmpty ) {
						rgxp.beg = smNone;
					}

					if ( rgxp.end == smEmpty ) {
						rgxp.end = smNone;
					}

					rgxp.val = prstr;
					rgxp_array.addItem(rgxp);
				}
			}
		}
	}

	if (res) {
		*res = true;
	}

	delete[] prstr;
	prstr = null_ptr;
	return rgxp_array;
}
} // Namespace by Kozura(c) Inc.
