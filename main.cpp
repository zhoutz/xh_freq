#include "extract_data.hpp"
#include "split_pinyin.hpp"
#include "xiaohe.hpp"
#include "dbg.h"
#include "key_hist.hpp"
#include <ranges>
using namespace std;

int main() {
  // dbg(split_token("de/di4"));
  // dbg(split_token("le/liao3/liao4"));

  auto words = extract_data();
  // for (auto const &i : pinyin_freq | views::take(10)) {
  //   dbg(i);
  // }
  // for (int i = 0; i < 255; ++i) {
  for (int i = 0; i < 8000; ++i) {
    // for (int i = 0; i < words.size(); ++i) {
    auto const &cur_word = words[i];
    if (cur_word.first.empty()) {
      continue;
    }
    auto tokens = split_token(cur_word.first);
    // dbg(i+1,tokens);
    string keys;
    for (auto token : tokens) {
      if (token == "uu")
        continue;
      auto pys = split_pinyin(token, i + 1);
      // dbg(i + 1, token, pys);
      keys+=convert_pys_to_xiaohe(pys, i + 1);
    }
    add_str_to_hist(keys, cur_word.second);
  }
  prt_hist();
}
