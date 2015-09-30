/*
2015-4-1 09:37:21
2015-03-31 14:30--17:00 at Kujiale
get all subfolders and files withn it, rename these files and delete
the duplicate ones, then, move them into a new folders. Meanwhile output
the duplicate ones int target folder .
*/

#include <fstream>
#include <iostream>
#include "dirent.h"
#include "listAllFile.h"
using namespace std;

void FileSys::listAllSubfolders()
{
  DIR *dir = opendir(input_path.c_str());
  if(dir == NULL)
  {
    cout << "input folder name format error.\n";
    exit(1);
  }
  dirent *entry = readdir(dir);
  while(entry)
  {
    if(entry->d_type == DT_DIR && entry->d_name[0]!='.') mid_path.push_back(input_path + '/'+entry->d_name);
    entry = readdir(dir);
  }
  filename = new vector<string>[mid_path.size()];
  for(int i = 0;i < mid_path.size();++i)
  {
    dir = opendir(mid_path[i].c_str());
    entry = readdir(dir);
    while(entry)
    {
      if(entry->d_type == DT_REG)
      {
        string name = mid_path[i] + "/" + string(entry->d_name);
        filename[i].push_back(name);
      }
      entry = readdir(dir);
    }
  }
}

FileSys::~FileSys()
{
  delete[] filename;
}