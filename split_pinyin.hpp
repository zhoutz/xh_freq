#pragma once

#include "dbg.h"
#include <algorithm>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

const vector<string> chinese_yunmu = {
    "iong", "uang", "iang",        //
    "ang",  "eng",  "ing",  "ong", //
    "uan",  "uai",  "iao",  "ian", //
    "ua",   "uo",   "ia",          //
    "ai",   "ei",   "ui",   "ao",  "ou", "iu", "ie",
    "ue",   "er",   "an",   "en",  "in", "un", //
    "a",    "o",    "e",    "i",   "u",  "v"   //
};

const vector<string> chinese_shengmu = {
    "b", "p", "m",  "f",  "d",  "t", "n", "l", "g", "k", "h", "j",
    "q", "x", "zh", "ch", "sh", "r", "z", "c", "s", "y", "w"};

// delete number, split by slash
// input will not be empty
inline vector<string_view> split_token(string_view token) {
  vector<string_view> ret;
  int start = 0;
  for (int i = 0; i < token.size(); ++i) {
    if (isdigit(token[i]) || token[i] == '/') {
      if (i > start) {
        ret.push_back(token.substr(start, i - start));
      }
      start = i + 1;
    }
  }
  if (start < token.size()) {
    ret.push_back(token.substr(start));
  }
  return ret;
}

// split pinyin sequence
// e.g. "zhong1guo2" -> "zh", "ong", "g", "uo"
inline vector<string_view> split_pinyin(string_view pinyin, int rows_id) {
  string_view ret_sm, ret_ym;
  bool found = false;
  for (auto const &ym : chinese_yunmu) {
    if (pinyin.ends_with(ym)) {
      ret_ym = ym;
      ret_sm = pinyin.substr(0, pinyin.size() - ym.size());
      found = true;
      break;
    }
  }
  if (!found)
    dbg("not found yunmu", pinyin, rows_id);

  // if have shengmu
  if (ret_sm.size() > 0) {
    if (count(chinese_shengmu.begin(), chinese_shengmu.end(), ret_sm) == 0) {
      dbg("not found shengmu", pinyin, rows_id);
    }
    return {ret_sm, ret_ym};
  }

  // only yunmu, no shengmu
  if (pinyin == "er") {
    return {"e", "r"};
  } else {
    return {ret_ym.substr(0, 1), ret_ym};
  }
}
