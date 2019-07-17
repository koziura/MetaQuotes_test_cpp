#ifndef __KZR_ALGORITM_H__
#define __KZR_ALGORITM_H__
#include "karray.h"
#include "kregexp.h"
/*!
 * Namespace by Kozura(c) Inc.
 */
namespace kzr {
typedef Array<RegExp> RedExpArray_t;
/*!
 * \brief fuzzySearch
 * \param pattern
 * \param string
 * \return
 */
bool fuzzySearch(const char* pattern, const char* string);
/*!
 * \brief strictSearch
 * \param pattern
 * \param string
 * \return
 */
bool strictSearch(const char* pattern, const char* string);
/*!
 * \brief otherSearch
 * \param rgxp
 * \param string
 * \return
 */
bool otherSearch(const RegExp& rgxp, const char* string);
/*!
 * \brief regExpQuery
 * \param rgxp
 * \param string
 * \return
 */
bool regExpQuery(const RegExp& rgxp, const char* string);
/*!
 * \brief findSearchMask
 * \param in_str
 * \param res
 * \return
 */
RedExpArray_t findSearchMask(const char* in_str, bool* res=null_ptr);

} // Namespace by Kozura(c) Inc.
#endif // __KZR_ALGORITM_H__
