#include "ar_dos.h"

static int callback(void *data, int argc, char **argv, char **azColName) {
  int i;
  bundle *myAr = (bundle *)data;
  (*myAr)[std::stoul(argv[0])] = std::map<std::string, std::string>();

  for (i = 0; i < argc; i++) {
    if (i != 0) {
      (*myAr)[std::stoul(argv[0])][azColName[i]] = argv[i];
    }
  }
  return 0;
}

bundle *date_selector(unsigned long year, int month, int date, sqlite3 *db) {
  char *zErrMsg = 0;
  int rc;
  bundle *data = new bundle;
  std::string sql =
      "SELECT * FROM REPORT WHERE YEAR = " + std::to_string(year) +
      " AND MONTH = " + std::to_string(month) +
      " AND DAY = " + std::to_string(date) + ";";
  rc = sqlite3_exec(db, sql.c_str(), callback, data, &zErrMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
  }
  return data;
}

bundle *span_selector(unsigned long year_start, unsigned long year_end,
                      unsigned month_start, unsigned month_end,
                      unsigned date_start, unsigned date_end, sqlite3 *db) {
  char *zErrMsg = 0;
  int rc;
  bundle *data = new bundle;
  std::string sql =
      "SELECT * FROM REPORT WHERE YEAR >= " + std::to_string(year_start) +
      " AND YEAR <= " + std::to_string(year_end) +
      " AND MONTH >= " + std::to_string(month_start) +
      " AND MONTH <= " + std::to_string(month_end) +
      " AND DAY >= " + std::to_string(date_start) +
      " AND DAY <= " + std::to_string(date_end) + ";";
  rc = sqlite3_exec(db, sql.c_str(), callback, data, &zErrMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
  }
  return data;
}
