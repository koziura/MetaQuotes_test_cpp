#ifndef __KZR_REGEXP_H__
#define __KZR_REGEXP_H__
#include "kstring.h"
/*!
 * Namespace by Kozura(c) Inc.
 */
namespace kzr {
/*!
 * \brief The SpecMark enum
 */
enum SpecMark {
	smNone, smAsterisk, smQuestion, smEmpty = 4
};
/*!
 * \brief The RegExp struct
 */
struct RegExp {
	/*!
	 * \brief RegExp
	 */
	RegExp();
	/*!
	 * \brief RegExp
	 * \param r
	 */
	RegExp(const RegExp& r);
	/*!
	 * \brief operator =
	 * \param r
	 * \return
	 */
	RegExp& operator =(const RegExp& r);
	/*!
	 * \brief reset
	 */
	void reset();

	String val;
	SpecMark beg, end;
};
} // Namespace by Kozura(c) Inc.
#endif // __KZR_REGEXP_H__
