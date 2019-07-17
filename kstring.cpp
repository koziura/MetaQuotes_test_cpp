#include "kstring.h"
#include <memory.h>
#include <stdlib.h>
#include <cstring>
/*!
 * Namespace by Kozura(c) Inc.
 */
namespace kzr {
String::~String() {
	clear();
}

String::String(): m_cstr(null_ptr), m_len(0), m_reserve(1) {
}

String::String(const char* str): m_reserve(1) {
	m_len = strlen(str);
	m_cstr = (char*)malloc(m_len+m_reserve);
	memcpy(m_cstr, str, m_len);
	m_cstr[m_len] = 0;
}

String::String(const String& str) {
	m_len = str.size();
	m_reserve = str.m_reserve;
	m_cstr = (char*)malloc(m_len+m_reserve);
	memcpy(m_cstr, str.m_cstr, m_len);
	if (m_len) {
		m_cstr[m_len] = '\0';
	}
}

String&String::operator =(const char* str) {
	uint_t len = strlen(str);

	if (len != m_len) {
		clear();
	}
	m_len = len;
	m_cstr = (char*)malloc(m_len+m_reserve);
	if (m_len) {
		memcpy(m_cstr, str, m_len);
	}
	m_cstr[m_len] = '\0';
	return *this;
}

String&String::operator =(const String& str) {
	uint_t len = str.size();

	if (len != m_len) {
		clear();
	}
	m_len = len;
	m_reserve = str.m_reserve;
	m_cstr = (char*)malloc(m_len+m_reserve);
	if (m_len) {
		memcpy(m_cstr, str.c_str(), m_len);
	}
	m_cstr[m_len] = '\0';
	return *this;
}

String&String::operator +=(const char ch) {
	uint_t len = 1;

	if (m_cstr) {
		m_cstr = (char*)realloc(m_cstr, m_len+len+m_reserve);
	} else {
		m_cstr = (char*)malloc(len+m_reserve);
	}
	memcpy(m_cstr + m_len, &ch, len);
	m_len += len;
	m_cstr[m_len] = '\0';
	return *this;
}

String&String::operator +=(const char* str) {
	uint_t len = strlen(str);

	if (m_cstr) {
		m_cstr = (char*)realloc(m_cstr, m_len+len+m_reserve);
	} else {
		m_cstr = (char*)malloc(len+m_reserve);
	}
	memcpy(m_cstr + m_len, str, len);
	m_len += len;
	m_cstr[m_len] = '\0';
	return *this;
}

String&String::operator +=(const String& str) {
	uint_t len = str.size();

	if (m_cstr) {
		m_cstr = (char*)realloc(m_cstr, m_len+len+m_reserve);
	} else {
		m_cstr = (char*)malloc(len+m_reserve);
	}
	memcpy(m_cstr + m_len, str.m_cstr, len);
	m_len += len;
	m_cstr[m_len] = '\0';
	return *this;
}

String&String::operator +(const String& str) {
	return this->operator+=(str);
}

String&String::operator +(const char* str) {
	return this->operator+=(str);
}

bool String::operator ==(const String& str) {

	const char* pattern = m_cstr;
	const char* string = str.c_str();

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

uint_t String::size() const {
	return m_len;
}

const char&String::at(const uint_t& pos) const {
	return m_cstr[pos];
}

char&String::operator [](const uint_t& pos) {
	return m_cstr[pos];
}

const char*String::c_str() const {
	return m_cstr;
}

bool String::empty() const {
	return !m_len;
}

bool String::isNull() const {
	return m_cstr == null_ptr;
}

void String::clear() {
	if (m_cstr) {
		free(m_cstr);
	}
	m_len = 0;
	m_cstr = null_ptr;
}

String operator +(const char* c_str, const String& str) {
	return String(c_str) + str;
}

bool operator ==(const char* c_str, const String& str) {
	return String(c_str) == str;
}
} // Namespace by Kozura(c) Inc.
