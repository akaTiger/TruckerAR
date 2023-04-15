#include "ar_dos.h"

int main() {
  sqlite3 *db;
  int rc;
  bool debug = true;
  if (debug) {
    std::string command = "rm -rf ./test.db";
    system(command.c_str());
  }

  rc = sqlite3_open("./test.db", &db);

  if (rc) {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    return (0);
  } else {
    fprintf(stdout, "Opened database successfully\n");
  }

  std::cout << "create table: " << createTable(db) << std::endl;
  std::cout << "read to database: " << readToDatabase("real.csv", db)
            << std::endl;

  bundle *myAr = span_selector(2023, 2023, 4, 4, 1, 3, db);
  std::cout << "total cargo weight: " << count_addable(myAr, "WEIGHT_IN_KG")
            << std::endl;
  std::cout << "most conmon use car: " << count_string_appear(myAr, "TRUCK", 0)
            << std::endl;
  std::cout << "jobs > 10t: " << count_counter_type_num(myAr, "WEIGHT_IN_KG", 1, 20000)
            << std::endl;
  std::cout << "jobs related: " << count_size(myAr) << std::endl;
  sqlite3_close(db);

  return 0;
}