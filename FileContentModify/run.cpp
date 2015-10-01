#include "FileContentModify.h"
#include <iostream>
using namespace std;

int main()
{
  string path, suffix;
  vector<pair<int, string>> insert_content;
  int num_insert;
  cout << "Please enter path to modify:";
  cin >> path;
  cout << "Please enter sufix to modify,\"all\" for all files:";
  cin >> suffix;
  cout << "how many lines to be insert:";
  cin >> num_insert;
  cout << "please enter insert line number(begin with 0) and content, split with a blank space.\n ";
  cout << "number -1 equals the end of file.\n";
  for(int i = 0;i < num_insert;++i)
  {
    int no;
    string str;
    cin >> no;
    getchar();
    getline(cin, str);
    if(no>-2)insert_content.push_back(pair<int, string>(no, str));
  }
  if(num_insert<1)
  {
    cout << "nothing to be issert, exit\n";
    return 0;
  }
  FileContentModify file_modify(path, suffix, insert_content);
  file_modify.InsertIntoFile();
  system("pause");
  return 0;
}