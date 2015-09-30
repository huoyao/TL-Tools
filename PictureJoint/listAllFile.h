#ifndef _LISTALLFILE_H_
#define _LISTALLFILE_H_

#include <string>
#include <vector>
#include <unordered_map>
using std::string;
using std::vector;
using std::unordered_map;


class FileSys
{
public:
  FileSys(){}
  ~FileSys();
  FileSys(const string &path)
    :input_path(path){};
  void listAllSubfolders();
  vector<string> getFileName(const int &id){ return filename[id]; }
private:
  vector<string> *filename,mid_path;
  string input_path;
};

#endif