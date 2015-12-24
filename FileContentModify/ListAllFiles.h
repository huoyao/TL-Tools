/*************************************
/  FILE:ListAllFiles.h
/  TIME:2015-10-01 13:24:42
/AUTHOR:TL
/  INFO:
/*************************************/

#ifndef __ListAllFiles_H__
#define __ListAllFiles_H__
#include <string>
#include <queue>


class ListAllFiles
{
public:
  ListAllFiles()
  {
  };

  ~ListAllFiles()
  {
  };

  explicit ListAllFiles(const std::string& path,const std::string&suffix);
  void listAllSubfolders();
  std::string getFileName(const size_t& id);
  size_t GetFileNum() { return all_filename_.size(); }
private:
  std::vector<std::string> all_filename_;
  std::string input_path_,suffix_;
};

#endif
