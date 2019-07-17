#include <locale>

#include "kstring.h"
#include "karray.h"
#include "kregexp.h"
#include "kalgoritm.h"

#include "clogreader.h"

int main(int argc, char const* argv[])
{
	typedef unsigned long long uint64_t;

	setlocale(LC_ALL,"");

	using namespace kzr;

	if (! (argc > 1) ) {
		printf("\n* help {begin} *\n"
			"\n[arguments]\n"
			"  -i [filename] the full path to the log file.\n"
			"  -f [string] the search expression.\n"
			"\n[results]\n"
			"  the output of results will be written on this screen.\n"
			"\n* help {end} *\n\n");
		system("pause");
		return 0;
	}

	String filename, expr_val;
	{
		bool is_file = false, is_expr = false;

		for(int i(1); i < argc; ++i) {
			String s(argv[i]);

			if (is_file) {
				filename = s;
				is_file = false;
			} else if (is_expr) {
				expr_val = s;
				is_expr = false;
			}

			if (s == "-i") {
				is_file = true;
			} else if (s == "-f") {
				is_expr = true;
			}

			if (filename.size() && expr_val.size()) {
				break;
			}
		}

		if (filename.empty() || expr_val.empty()) {
			printf("Invalid parse args! Please run again with empty args for this help.\n");
			system("pause");
			return 0;
		}

		FILE* file = fopen(filename.c_str(), "r");

		if (file) {
			fclose(file);
		} else {
			printf("not found log file!\n");
			system("pause");
			return 0;
		}
	}

	{
		CLogReader log;
		if ( !log.Open(filename.c_str()) ) {
			return 0;
		}

		if ( !log.SetFilter(expr_val.c_str()) ) {
			return 0;
		}

		const int max_len = 1024;
		char str[max_len];

		bool found = false;
		uint64_t row = 0;

		while ( !log.eof() ) {
			++row;

			if ( log.GetNextLine(&str[0], max_len) ) {
				if (!found) {
					found = true;
					printf("Search Results:\n");
				}

				printf("[row: %llu ] %s\n", row, &str[0]);
			}
		}
	}

	system("pause");

	return 0;
}
