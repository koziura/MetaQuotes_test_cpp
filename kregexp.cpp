#include "kregexp.h"
/*!
 * Namespace by Kozura(c) Inc.
 */
namespace kzr {
RegExp::RegExp(): beg(smEmpty), end(smEmpty) {
}

RegExp::RegExp(const RegExp& r): val(r.val), beg(r.beg), end(r.end) {
}

RegExp&RegExp::operator =(const RegExp& r) {
	val = r.val;
	beg = r.beg;
	end = r.end;
	return *this;
}

void RegExp::reset() {
	val.clear();
	beg = end = smEmpty;
}
} // Namespace by Kozura(c) Inc.
