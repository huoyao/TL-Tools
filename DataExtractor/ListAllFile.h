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
  FileSys():file_name_by_1stlevel(nullptr) {}
  ~FileSys();
  FileSys(const string &path)
    :input_path(path), file_name_by_1stlevel(nullptr) {};
  void ListAllFileByFirtLevel();
  void ListALLFileByLevel(const int& level=INT_MAX);
  vector<string> GetFileName(const int &id) { return file_name_by_1stlevel[id]; }
  vector<string> GetAllFileName() { return all_file_name; }
private:
  vector<string> *file_name_by_1stlevel,first_level_path,all_file_name;
  string input_path;
};

#endif
