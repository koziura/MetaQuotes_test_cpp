#include "clogreader.h"
#include "kalgoritm.h"
#include <stdio.h>
/*!
 * \brief The log_wrapper_t struct
 */
struct LogWrapper_t {
	FILE* m_file;
	bool m_eof;
	kzr::RedExpArray_t m_rgxarr;
};

CLogReader::CLogReader()
{
	m_lw = new LogWrapper_t;
	m_lw->m_file = null_ptr;
	m_lw->m_eof = true;
}

CLogReader::~CLogReader()
{
	Close();
	delete m_lw;
	m_lw = null_ptr;
}

bool CLogReader::Open(const char* filename)
{
	if (m_lw->m_file) {
		fclose(m_lw->m_file);
		m_lw->m_file = null_ptr;
	}
	m_lw->m_file = fopen(filename, "r");
	m_lw->m_eof = !m_lw->m_file;
	return m_lw->m_file != null_ptr;
}

void CLogReader::Close()
{
	if (m_lw->m_file) {
		fclose(m_lw->m_file);
		m_lw->m_file = null_ptr;
	}
	m_lw->m_rgxarr.clear();
}

bool CLogReader::eof() const
{
	return m_lw->m_eof;
}

bool CLogReader::SetFilter(const char* filter)
{
	bool res;
	m_lw->m_rgxarr = kzr::findSearchMask(filter, &res);

	//*
	printf("\n#[!] Search query:\n");
	for (kzr::uint_t i (0); i < m_lw->m_rgxarr.size(); ++i) {
		const kzr::RegExp& rgxp( m_lw->m_rgxarr.at(i) );
		printf("  rgxp[%d] val: %s\n", i, rgxp.val.c_str());
	}
	printf("# Search query[!]\n\n");
	//*/

	return res;
}

bool CLogReader::GetNextLine(char* buf, const int bufsize)
{
	if ( !m_lw->m_file ) {
		m_lw->m_eof = true;
		return false;
	}

	if ( !fgets(buf, bufsize, m_lw->m_file) ) {
		m_lw->m_eof = true;
		return false;
	}

	for (kzr::uint_t i (0); i < m_lw->m_rgxarr.size(); ++i) {
		if ( !kzr::regExpQuery( m_lw->m_rgxarr.at(i), buf) ) {
			return false;
		}
	}
	return true;
}
