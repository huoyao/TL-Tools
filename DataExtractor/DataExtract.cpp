#include "DataExtract.h"
#include <sstream>
#include <iostream>
using namespace std;

DataExtract::DataExtract() {
}

DataExtract::~DataExtract() {
  ifs.close();
  ofs.close();
}

DataExtract::DataExtract(const std::string& file_in, const std::string &op_type,
                         const char &c):
                         separator(c),
                         ifs(file_in) {
  ofs.open(op_type + "-" + file_in);
  op_map["increase"] = 0;
  op_map["increseFirst"] = 1;
  switch(op_map[op_type]) {
  case 0:
    func_ptr = &DataExtract::Increase;
    break;
  case 1:
    func_ptr = &DataExtract::IncreaseFirstNumber;
    break;
  default:
    ErrorOutput();
    break;
  }
}

// 0
void DataExtract::Increase(const string &line) {
  istringstream isstr(line);
  int tmp;
  char c;
  while(isstr >> tmp) {
    ++tmp;
    ofs << tmp;
    isstr >> c;
    ofs << c;
  }
}

// 1
void DataExtract::IncreaseFirstNumber(const std::string &line) {
  istringstream isstr(line);
  int tmp;
  isstr >> tmp;
  ++tmp;
  ofs << tmp;
  ofs << " ";
  string str;
  while(isstr >> str) {
    ofs << str;
  }
}


// default
void DataExtract::ErrorOutput() {
  cout << "parameters error!\n";
}

void DataExtract::OpOnString() {
  string line;
  while(getline(ifs, line)) {
    (this->*func_ptr)(line);
  }
}