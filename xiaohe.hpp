#pragma once

#include "dbg.h"
#include <algorithm>
#include <map>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

inline const map<string, string> xiaohe_map = {
    {"sh", "u"},  {"ch", "i"},   {"zh", "v"}, //
    {"iu", "q"},  {"ei", "w"},   {"uan", "r"},  {"ue", "t"},   {"un", "y"},
    {"uo", "o"},  {"ie", "p"},   {"ong", "s"},  {"iong", "s"}, {"ai", "d"},
    {"en", "f"},  {"eng", "g"},  {"ang", "h"},  {"an", "j"},   {"uai", "k"},
    {"ing", "k"}, {"uang", "l"}, {"iang", "l"}, {"ou", "z"},   {"ua", "x"},
    {"ia", "x"},  {"ao", "c"},   {"ui", "v"},   {"in", "b"},   {"iao", "n"},
    {"ian", "m"},
};

inline auto convert_pys_to_xiaohe(vector<string_view> const &pys, int row_id) {
  string ret_str;

  for (auto py : pys) {
    if (py.size() == 1) {
      ret_str += py;
    } else {
      auto it = xiaohe_map.find(string(py));
      if (it != xiaohe_map.end()) {
        ret_str += it->second;
      } else {
        dbg("xiaohe_not_in_map", py);
        dbg(pys, row_id);
      }
    }
  }

  return ret_str;
}
