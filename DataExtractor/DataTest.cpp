#include "DataExtract.h"
#include "ListAllFile.h"
#include "TimeExtractor.h"
using namespace std;

int main(int argc,char **argv)
{
  if(argc < 2) return 0;
  enum METHOD {increase};
  string in_file = ".\\input\\gargoyle.bou", out_file = ".\\output\\gargoyle.bou";
  char sepatator = ',';
  METHOD method = increase;
  DataExtract data(in_file, out_file, sepatator, method);
  //data.opOnString();

  //get all file name
  FileSys all_file(argv[1]);
  all_file.ListALLFileByLevel();

  //time extract
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
  vector<string> all_file_name = all_file.GetAllFileName();
  for(int i = 0;i < all_file_name.size();++i)
  {
    tim.ExtractTime(all_file_name[i]);
  }
  return 0;
}
