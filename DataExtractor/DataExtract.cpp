#include "DataExtract.h"
#include <sstream>
#include <iostream>
using namespace std;

DataExtract::DataExtract()
{
}

DataExtract::~DataExtract()
{
  ifs.close();
  ofs.close();
}

DataExtract::DataExtract(const std::string& file_in, const std::string &file_out,
                         const char &c,const int&method):input_file_name(file_in),
                         output_file_name(file_out),
                         separator(c),
                         ofs(file_out),
                         ifs(file_in)
{
  switch(method)
  {
  case 0:
    func_ptr = &DataExtract::increase;
  default:
    break;
  }
}

void DataExtract::increase(string &line)
{
  istringstream isstr(line);
  int tmp;
  char c;
  while(isstr >> tmp)
  {
    ++tmp;
    ofs << tmp;
    isstr >> c;
    ofs << c;
  }
}

void DataExtract::opOnString()
{
  string line;
  while(getline(ifs, line))
  {
    (this->*func_ptr)(line);
  }
}