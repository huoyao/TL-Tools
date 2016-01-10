/*
2015-4-1 09:37:21
2015-03-31 14:30--17:00 at Kujiale
get all subfolders and files withn it, rename these files and delete
the duplicate ones, then, move them into a new folders. Meanwhile output
the duplicate ones int target folder .
*/

#include <fstream>
#include <iostream>
#include "Dirent.h"
#include "ListAllFile.h"
using namespace std;

void FileSys::ListAllFileByFirtLevel() {
  DIR *dir = opendir(input_path.c_str());
  if(dir == NULL) {
    cout << "input folder name format error.\n";
    exit(1);
  }
  dirent *entry = readdir(dir);
  while(entry) {
    if(entry->d_type == DT_DIR && entry->d_name[0] != '.') first_level_path.push_back(input_path + '\\' + entry->d_name);
    entry = readdir(dir);
  }
  file_name_by_1stlevel = new vector<string>[first_level_path.size()];
  for(int i = 0;i < first_level_path.size();++i) {
    dir = opendir(first_level_path[i].c_str());
    entry = readdir(dir);
    while(entry) {
      if(entry->d_type == DT_REG) {
        string name = first_level_path[i] + "/" + string(entry->d_name);
        file_name_by_1stlevel[i].push_back(name);
      }
      entry = readdir(dir);
    }
  }
}

void FileSys::ListALLFileByLevel(const int & level) {
  vector<string> mid_path[2];
  mid_path[0].push_back(input_path.c_str());
  int vec_id = 0;
  dirent *entry;
  DIR *dir;
  for(int i = 0;i < level;++i) {
    if(mid_path[vec_id].size() < 1) break;
    for(int id = 0;id < mid_path[vec_id].size();++id)
    {
      dir = opendir(mid_path[vec_id][id].c_str());
      entry = readdir(dir);
      while(entry) {
        string name = mid_path[vec_id][id] + "\\" + string(entry->d_name);
        if(entry->d_type == DT_REG) {  
          all_file_name.push_back(name);
        } else if(entry->d_type == DT_DIR && entry->d_name[0] != '.')
        {
          mid_path[1 - vec_id].push_back(name);
        }
        entry = readdir(dir);
      }
    }
    mid_path[vec_id].clear();
    vec_id = 1 - vec_id;
  }
}


FileSys::~FileSys() {
  if(file_name_by_1stlevel) delete[] file_name_by_1stlevel;
}
