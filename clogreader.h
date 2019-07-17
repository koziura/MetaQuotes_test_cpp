#ifndef CLOGREADER_H
#define CLOGREADER_H

class CLogReader {
public:
	CLogReader();
	~CLogReader();
	bool Open(const char* filename);                // открытие файла, false - ошибка
	void Close();                                   // закрытие файла
	bool SetFilter(const char *filter);             // установка фильтра строк, false - ошибка
	bool GetNextLine(char *buf, const int bufsize); // запрос очередной найденной строки,
	// buf - буфер, bufsize - максимальная длина
	// false - не найдено
	bool eof() const; // конец файла

private:
	struct LogWrapper_t* m_lw;
};

#endif // CLOGREADER_H
