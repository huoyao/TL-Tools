#include "DataExtract.h"
#include "ListAllFile.h"
#include "TimeExtractor.h"
#include <iostream>
using namespace std;

#define DATAEXTRACT
//#define TIMEEXTRACT

int main(int argc,char **argv)
{
  //get all file name
  if(argc < 2) {
    cout << "No parameters!\n";
    return 0;
  }
  FileSys all_file(argv[1]);
  all_file.ListALLFileByLevel();
  vector<string> all_file_name = all_file.GetAllFileName();
  cout << "all file: " << all_file_name.size() << endl;

  //data mdf
#ifdef DATAEXTRACT
  char sepatator = ' ';
  if(argc == 4) sepatator = argv[3][0];
  for(size_t i = 0;i < all_file_name.size();++i)
  {
    //DataExtract data(argv[1], argv[2], sepatator);
    DataExtract data(all_file_name[i], argv[2], sepatator);
    data.OpOnString();
    cout << i << ",";
  }
#endif

  //time extract
#ifdef TIMEEXTRACT
  int num_double = argc>2?stoi(argv[2]):-1;
  int num_int = argc > num_double + 3 ? stoi(argv[num_double + 3]) : -1;
  vector<string> double_prefix, int_prefix;
  for(int i = 3;i < num_double + 3;++i)
  {
    double_prefix.push_back(argv[i]);
  }
  for(int i = num_double + 3;i < argc;++i)
  {
    int_prefix.push_back(argv[i]);
  }
  TimeExtractor tim(double_prefix,int_prefix);
  for(int i = 0;i < all_file_name.size();++i)
  {
    tim.ExtractTime(all_file_name[i]);
    cout << i << ",";
  }
#endif

  return 0;
}
