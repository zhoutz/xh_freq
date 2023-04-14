#pragma once

#include "dbg.h"
#include <algorithm>
#include <cctype>
#include <map>
#include <string>
#include <utility>
#include <vector>
using namespace std;

inline map<char, double> key_hist;

inline void add_char_to_hist(char ch, double freq) {
  if (!isalpha(ch)) {
    dbg("error in add_to_hist, encounter non letter");
  }
  auto it = key_hist.find(ch);
  if (it == key_hist.end()) {
    key_hist[ch] = freq;
  } else {
    it->second += freq;
  }
}

inline void add_str_to_hist(string s, double freq) {
  double freqq = freq / s.size();
  for (auto ch : s) {
    add_char_to_hist(ch, freqq);
  }
}

inline void prt_hist() {
  vector<pair<char, double>> v(key_hist.begin(), key_hist.end());
  sort(v.begin(), v.end(), [](auto l, auto r) { return l.second > r.second; });
  for(auto p:v){
    dbg(p);
  }
}
