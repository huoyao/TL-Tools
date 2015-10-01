/*************************************
/  FILE:FileContentModify.h
/  TIME:2015-10-01 13:45:09
/AUTHOR:TL
/  INFO:
/*************************************/

#ifndef __FileContentModify_H__
#define __FileContentModify_H__
#include "ListAllFiles.h"


class FileContentModify
{
public:
  FileContentModify()
  {
  };

  ~FileContentModify()
  {
  };
  FileContentModify(const std::string& input_path,
                    const std::string &suffix,
                    const std::vector<std::pair<int, std::string>> &insert_content);
  void InsertIntoFile();
private:
  ListAllFiles all_files_;
  std::vector<std::pair<int, std::string>> insert_content_;
};

#endif
