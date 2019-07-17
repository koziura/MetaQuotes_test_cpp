#ifndef __KZR_STRING_H__
#define __KZR_STRING_H__
#ifndef null_ptr
#define null_ptr 0
#endif
/*!
 * Namespace by Kozura(c) Inc.
 */
namespace kzr {
typedef unsigned int uint_t;
typedef unsigned char uchar_t;
/*!
 * \brief The Lock class
 */
class Lock {
	friend class String;
	inline Lock() { }
	inline Lock(const Lock&) { }
};
/*!
 * \brief The String class
 */
class String: virtual private Lock {
	char* m_cstr;
	uint_t m_len;
	uchar_t m_reserve;

public:
	/*! */
	~String();
	/*!
	 * \brief String
	 */
	String();
	/*!
	 * \brief String
	 * \param str
	 */
	String(const char* str);
	/*!
	 * \brief String
	 * \param str
	 */
	String(const String& str);
	/*!
	 * \brief operator =
	 * \param str
	 * \return
	 */
	String& operator =(const char* str);
	/*!
	 * \brief operator =
	 * \param str
	 * \return
	 */
	String& operator =(const String& str);
	/*!
	 * \brief operator +=
	 * \param ch
	 * \return
	 */
	String& operator +=(const char ch);
	/*!
	 * \brief operator +=
	 * \param str
	 * \return
	 */
	String& operator +=(const char* str);
	/*!
	 * \brief operator +=
	 * \param str
	 * \return
	 */
	String& operator +=(const String& str);
	/*!
	 * \brief operator +
	 * \param str
	 * \return
	 */
	String& operator +(const String& str);
	/*!
	 * \brief operator +
	 * \param str
	 * \return
	 */
	String& operator +(const char* str);
	/*!
	 * \brief operator ==
	 * \param str
	 * \return
	 */
	bool operator ==(const String& str);
	/*!
	 * \brief size
	 * \return
	 */
	uint_t size() const;
	/*!
	 * \brief at
	 * \param pos
	 * \return
	 */
	const char& at(const uint_t& pos) const;
	/*!
	 * \brief operator []
	 * \param pos
	 * \return
	 */
	char& operator [](const uint_t& pos);
	/*!
	 * \brief c_str
	 * \return
	 */
	const char* c_str() const;
	/*!
	 * \brief empty
	 * \return
	 */
	bool empty() const;
	/*!
	 * \brief isNull
	 * \return
	 */
	bool isNull() const;
	/*!
	 * \brief clear
	 */
	void clear();
};
/*!
 * \brief operator +
 * \param c_str
 * \param str
 * \return
 */
static inline String operator +(const char* c_str, const String& str);
/*!
 * \brief operator ==
 * \param c_str
 * \param str
 * \return
 */
static inline bool operator ==(const char* c_str, const String& str);
} // Namespace by Kozura(c) Inc.
#endif //__KZR_STRING_H__
