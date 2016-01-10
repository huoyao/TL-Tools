
#include "ListAllFile.h"
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
  if(argc < 2) return 0;

  //get all file name
  FileSys all_file(argv[1]);
  all_file.ListALLFileByLevel();
  vector<string> all_file_name = all_file.GetAllFileName();

  cout << all_file_name.size() << endl;
  for(size_t i = 0; i < all_file_name.size(); i++)
  {
    cout << i << ",";
    string file = all_file_name[i];
    string str,out_dir,file_name;
    string out_put_name = to_string(i);
    while(out_put_name.size() < 4) out_put_name = "0" + out_put_name;
    size_t pos = file.find_last_of("\\");
    size_t dot_pos = file.find_last_of(".");
    out_dir = file.substr(0, pos);
    file_name = out_dir+"-new\\"+out_put_name+file.substr(dot_pos, file.size()-dot_pos);

    std::ifstream is(file, std::ifstream::binary);
    if(is)
    {
      // get length of file:
      is.seekg(0, is.end);
      int length = is.tellg();
      is.seekg(0, is.beg);

      std::string str;
      str.resize(length, ' '); // reserve space
      char* begin = &*str.begin();

      is.read(begin, length);
      is.close();
      std::ofstream os(file_name, std::ofstream::binary);
      os << str;
      os.close();
    } else
    {
      std::cout << "Could not open test.txt\n";
    }
  }


  return 0;
}
