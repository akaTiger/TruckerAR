#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

typedef std::map<unsigned long, std::map<std::string, std::string>> bundle;
bundle *date_selector(unsigned long year, int month, int date, sqlite3 *db);
bundle *span_selector(unsigned long year_start, unsigned long year_end,
                      unsigned month_start, unsigned month_end,
                      unsigned date_start, unsigned date_end, sqlite3 *db);
int createTable(sqlite3 *db);
int readToDatabase(std::string filename, sqlite3 *db);
unsigned long count_addable(bundle *target, std::string key);
std::string count_string_appear(bundle *target, std::string key, int mode);
unsigned long count_counter_type_num(bundle *target, std::string key, int mode,
                                     long value);
unsigned long count_size(bundle *target);