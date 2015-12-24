#include "TimeExtractor.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

TimeExtractor::TimeExtractor() {
}

TimeExtractor::~TimeExtractor() {
}

void TimeExtractor::init() {
  int num_double = prefix_double.size(), num_int = prefix_int.size();
  for(size_t i = 0;i < num_double;++i)
    str_map_double[prefix_double[i]] = i;
  for(size_t i = 0;i < num_int;++i)
    str_map_int[prefix_int[i]] = i;

  for(size_t i = 0;i < prefix_double.size();++i)
    need_doule.insert(prefix_double[i]);
  for(size_t i = 0;i < prefix_int.size();++i)
    need_int.insert(prefix_int[i]);
}

void TimeExtractor::ExtractTime(const std::string &file) {
  SetFileName(file);
  GenerateOutDir(file_path);
  ifstream ifs(file_path);
  vector<int> res_int[100];
  vector<double> res_double[100];
  string str, strin;
  //get data line by line
  while(getline(ifs, str)) {
    istringstream isstr(str);
    isstr >> strin;
    if(need_int.count(strin) == 0 && need_doule.count(strin) == 0) continue;
    bool is_int = need_int.count(strin) > 0;
    string str_word;
    int value_int;
    double value_double;
    while(isstr >> str_word) {
      if(FindValueInALine(str_word, is_int, value_int, value_double))
        break;
    }
    if(is_int)
      res_int[str_map_int[strin]].push_back(value_int);
    else
      res_double[str_map_double[strin]].push_back(value_double);
  }
  ifs.close();
  //write to file
  for(size_t i = 0;i < prefix_double.size();++i)
    Out2FileDouble(prefix_double, res_double, i);
  for(size_t i = 0;i < prefix_int.size();++i)
    Out2FileInt(prefix_int, res_int, i);
}

void TimeExtractor::GenerateOutDir(const std::string&file) {
  int pos=file.find_last_of("\\");
  int dot_pos = file.find_last_of(".");
  out_dir = file.substr(0, pos);
  file_name = file.substr(pos + 1, dot_pos-pos-1)+"-";
}

bool TimeExtractor::FindValueInALine(const string &str_word, bool &is_int, int &value_int, double &value_double) {
  if(str_word.length() == 0 || str_word[0]<'0' || str_word[0]>'9') return false;
  if(is_int)
    value_int = stoi(str_word);
  else
    value_double = stod(str_word);
  return true;
}

void TimeExtractor::Out2FileDouble(const vector<string> &prefix_double, const vector<double> res_t[], const int &i) {
  string filename = out_dir+"\\";
  filename = filename +file_name+ prefix_double[i].substr(0, prefix_double[i].size() - 1) + ".txt";
  ofstream ofs(filename);
  for(size_t id = 0;id < res_t[i].size();++id)
    ofs << res_t[i][id] << endl;
  ofs.close();
}

void TimeExtractor::Out2FileInt(const vector<string> &prefix_double, const vector<int> res_t[], const int &i) {
  string filename = out_dir + "\\";
  filename = filename +file_name+ prefix_double[i].substr(0, prefix_double[i].size()) + ".txt";
  ofstream ofs(filename);
  for(size_t id = 0;id < res_t[i].size();++id)
    ofs << res_t[i][id] << endl;
  ofs.close();
}