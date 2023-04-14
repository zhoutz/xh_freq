#pragma once

#include "dbg.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

constexpr string_view data_path = "freq.txt";

inline auto extract_data() {
  ifstream data(data_path);
  vector<pair<string, double>> ret;
  string _, pinyin, line;
  double freq;
  int line_num;
  double sum = 0;
  // int loop_cnt = 1;
  while (getline(data, line)) {
    auto iss = istringstream(line);
    iss >> line_num >> _ >> _ >> freq;

    if (!iss.good()) {
      dbg("iss not good BEFORE pinyin!");
    }

    iss >> pinyin;

    if (!iss.good()) {
      // dbg("iss not good after read pinyin");
      pinyin = "";
    }

    ret.push_back({pinyin, freq - sum});
    sum = freq;
    // if (line_num != loop_cnt) {
    //   dbg("line_num != loop_cnt", line_num, loop_cnt);
    //   break;
    // }
    // ++loop_cnt;

    // if (line_num == 10)break;

    // if(pinyin=="uu"){
    //   dbg(line_num);
    // }
  }

  return ret;
}
