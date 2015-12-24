/*************************************
/  FILE:ListAllFiles.cpp
/  TIME:2015-10-01 13:24:42
/AUTHOR:TL
/  INFO:
/*************************************/
#include "ListAllFiles.h"
#include "dirent.h"
#include <iostream>

using namespace std;

ListAllFiles::ListAllFiles(const string& path,const string&suffix)
  :input_path_(path),suffix_(suffix)
{
  
}


void ListAllFiles::listAllSubfolders()
{
  string tmp_path = "";
  DIR *dir;
  dirent *entry;
  queue<string> mid_path;
  mid_path.push(input_path_);
  while(!mid_path.empty())
  {
    tmp_path = mid_path.front();
    mid_path.pop();
    dir = opendir(tmp_path.c_str());
    if(dir == nullptr)
    {
      cout << "input folder name error.\n";
      exit(1);
    }
    entry = readdir(dir);
    while(entry)
    {
      if(entry->d_type == DT_DIR && entry->d_name[0] != '.') mid_path.push(tmp_path + '/' + entry->d_name);
      if(entry->d_type == DT_REG)
      {
        string suffix_name = string(entry->d_name);
        suffix_name = suffix_name.substr(suffix_name.length() - suffix_.length(), suffix_name.length());
        if(suffix_=="" || suffix_name==suffix_)
        {
          string name = tmp_path + "/" + string(entry->d_name);
          all_filename_.push_back(name);
        }
      }
      entry = readdir(dir);
    }
  }
}

string ListAllFiles::getFileName(const size_t& id)
{
  return all_filename_[id];
}
