#include "ar_dos.h"

int createTable(sqlite3 *db) {
  char *zErrMsg = 0;
  int rc;
  std::string sql =
      "CREATE TABLE REPORT("
      "ID UNSIGNED BIG INT PRIMARY KEY NOT NULL,"
      "GAME TEXT NOT NULL,"
      "START_CITY TEXT NOT NULL,"
      "END_CITY TEXT NOT NULL,"
      "CARGO TEXT NOT NULL,"
      "WEIGHT_IN_KG BIG INT NOT NULL,"
      "DISTANCE_IN_KM BIG INT NOT NULL,"
      "PROFIT BIG INT NOT NULL,"
      "DAMAGE INT NOT NULL,"
      "REAL_TIME_TAKEN BIG INT NOT NULL,"
      "FUEL_USAGE DOUBLE NOT NULL,"
      "YEAR BIG INT NOT NULL,"
      "MONTH INT NOT NULL,"
      "DAY INT NOT NULL,"
      "TRUCK TEXT NOT NULL"
      ");";
  rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
  return rc;
}

int readToDatabase(std::string filename, sqlite3 *db) {
  std::ifstream file(filename);
  std::string line;
  std::vector<std::string> rows;
  char *zErrMsg = 0;
  int rc;
  while (std::getline(file, line, '\n')) {
    rows.push_back(line);
  }
  for (auto element : rows) {
    std::stringstream ss(element);
    std::vector<std::string> single_row;
    int counter = 0;
    int convert_number[] = {4, 6, 7, 15};
    while (std::getline(ss, line, ',')) {
      if (std::find(std::begin(convert_number), std::end(convert_number),
                    counter) != std::end(convert_number)) {
        std::string temp;
        for (unsigned long i = 0; i < line.size(); ++i) {
          if ((line[i] >= '0' && line[i] <= '9') || line[i] == '.') {
            temp = temp + line[i];
          }
        }
        line = temp;
      }
      single_row.push_back(line);
      counter++;
    }
    // 0000-00-00
    std::string year = single_row[23].substr(0, 4);
    std::string month = single_row[23].substr(5, 2);
    std::string day = single_row[23].substr(8, 2);

    std::string sql =
        "INSERT INTO REPORT (ID, GAME, START_CITY, END_CITY, CARGO, "
        "WEIGHT_IN_KG, DISTANCE_IN_KM, PROFIT, DAMAGE, REAL_TIME_TAKEN, "
        "FUEL_USAGE, YEAR, MONTH, DAY, TRUCK) VALUES (" +
        single_row[21] + ", '" + single_row[0] + "', '" + single_row[1] +
        "', '" + single_row[2] + "', '" + single_row[3] + "', " +
        single_row[4] + ", " + single_row[6] + ", " + single_row[7] + ", " +
        single_row[10] + ", " + single_row[11] + ", " + single_row[15] + ", " +
        year + ", " + month + ", " + day + ", '" + single_row[12] + "');";
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
  }
  return rc;
}