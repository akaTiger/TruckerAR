#include "ar_dos.h"

unsigned long count_addable(bundle *target, std::string key) {
  unsigned long num = 0;
  for (auto element : *target) {
    for (auto element2 : element.second) {
      if (element2.first == key) {
        num += std::stoul(element2.second);
      }
    }
  }
  return num;
}

std::string count_string_appear(bundle *target, std::string key, int mode) {
  std::map<std::string, unsigned long> num;
  std::string result;
  for (auto element : *target) {
    for (auto element2 : element.second) {
      if (element2.first == key) {
        if (num.find(element2.second) == num.end()) {
          num[element2.second] = 1;
        } else {
          num[element2.second]++;
        }
      }
    }
  }
  switch (mode) {
    case 0:
      // max appear in num
      result =
          std::max_element(num.begin(), num.end(),
                           [](const std::pair<std::string, unsigned long> &p1,
                              const std::pair<std::string, unsigned long> &p2) {
                             return p1.second < p2.second;
                           })
              ->first;
      break;
    case 1:
      // min appear in num
      result =
          std::min_element(num.begin(), num.end(),
                           [](const std::pair<std::string, unsigned long> &p1,
                              const std::pair<std::string, unsigned long> &p2) {
                             return p1.second < p2.second;
                           })
              ->first;
      break;
  }
  return result;
}

unsigned long count_counter_type_num(bundle *target, std::string key, int mode,
                                     long value) {
  unsigned long num = 0;
  for (auto element : *target) {
    for (auto element2 : element.second) {
      if (element2.first == key) {
        switch (mode) {
          case 0:
            if (std::stol(element2.second) == value) {
              num++;
            }
            break;
          case 1:
            if (std::stol(element2.second) >= value) {
              num++;
            }
            break;
          case 2:
            if (std::stol(element2.second) <= value) {
              num++;
            }
            break;
          case 3:
            if (std::stol(element2.second) > value) {
              num++;
            }
            break;
          case 4:
            if (std::stol(element2.second) < value) {
              num++;
            }
            break;
        }
      }
    }
  }
  return num;
}

unsigned long count_size(bundle *target) { return target->size(); }