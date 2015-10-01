/*************************************
/  FILE:FileContentModify.cpp
/  TIME:2015-10-01 13:45:09
/AUTHOR:TL
/  INFO:
/*************************************/
#include "FileContentModify.h"
#include <fstream>
#include <iostream>
using namespace std;

FileContentModify::FileContentModify(const string& input_path, 
                                     const string& suffix, 
                                     const vector<pair<int, string>>& insert_content)
  :all_files_(input_path,suffix),insert_content_(insert_content)
{
  all_files_.listAllSubfolders();
}

void FileContentModify::InsertIntoFile()
{
  sort(insert_content_.begin(), insert_content_.end(),
       [](const pair<int, string> &a, const pair<int, string>&b) { return a.first < b.first; });
  int file_num = all_files_.GetFileNum();
  if(insert_content_.size() < 1) return;
  for (int i = 0; i < file_num; ++i)
  {
    string name = all_files_.getFileName(i);
    ifstream ifs(name);
    ofstream ofs("./out.txt");
    int id = 0,cnt=0;
    bool end_insert = false;
    if(insert_content_[id].first==-1)
    {
      end_insert = true;
      ++id;
    }
    while (1)
    {
      while(id<insert_content_.size() && insert_content_[id].first == cnt)
      {
        ofs << insert_content_[id].second << endl;
        ++id;
      }
      string str;
      if(getline(ifs,str))
        ofs << str << endl;
      else break;
      ++cnt;
    }
    if(id < insert_content_.size()) ofs << insert_content_[id++].second << endl;
    if(end_insert) ofs << insert_content_[0].second << endl;
    ifs.close();
    ofs.close();
    cnt += id;
    ifs.open("./out.txt");
    ofs.open(name.c_str());
    while (cnt--)
    {
      string str;
      getline(ifs, str);
      ofs << str << endl;
    }
    ifs.close();
    ofs.close();
  }
  cout << "insert success:" << file_num << endl;;
}
