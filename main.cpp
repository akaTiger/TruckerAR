#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool createTable(sqlite3 *db) {
  char *zErrMsg = 0;
  int rc;
  std::string sql =
      "CREATE TABLE REPORT("
      "ID UNSIGNED BIG INT PRIMARY KEY NOT NULL,"
      "GAME TEXT NOT NULL,"
      "START_CITY TEXT NOT NULL,"
      "END_CITY TEXT NOT NULL,"
      "CARGO TEXT NOT NULL,"
      "WEIGHT_IN_KG INT NOT NULL"
      ");";
  rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
  if (rc) {
    return false;
  } else {
    return true;
  }
}

bool readToDatabase(std::string filename, sqlite3 *db) {
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
    while (std::getline(ss, line, ',')) {
      if (counter == 4) {
        std::string temp;
        for (unsigned long i = 0; i < line.size(); ++i) {
          if (line[i] >= '0' && line[i] <= '9') {
            temp = temp + line[i];
          }
        }
        line = temp;
      }
      single_row.push_back(line);
      counter++;
    }
    std::string sql =
        "INSERT INTO REPORT (ID, GAME, START_CITY, END_CITY, CARGO, "
        "WEIGHT_IN_KG) VALUES (" +
        single_row[21] + ", '" + single_row[0] + "', '" + single_row[1] +
        "', '" + single_row[2] + "', '" + single_row[3] + "', " +
        single_row[4] + ");";
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    std::cout << sql << std::endl;
  }
  std::cout << rc << std::endl;
  return true;
}

int main() {
  sqlite3 *db;
  int rc;
  rc = sqlite3_open("./test.db", &db);
  if (rc) {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    return (0);
  } else {
    fprintf(stdout, "Opened database successfully\n");
  }
  std::cout << createTable(db);
  readToDatabase("real.csv", db);
  return 0;
}