#include <iostream>
#include "listAllFile.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "PicJoint.h"
using namespace std;

//#define TOBEADJUSTMENT

int main()
{
  FileSys filesys("I:\gpu-cpu");   //input file path
  string output_path("./output/");
  filesys.listAllSubfolders();
  double scl = 1;                   //scale parameter after joint
  int num_row = 1, num_col = 2;       //layout of picture joint
  tl::PicJiont CT(scl,num_row,num_col);
  //order to be adjust
  unordered_map<int, int> order = { { 0, 3 }, { 1, 1 }, { 2, 2 }, { 3, 0 } };
  for(size_t i = 0;i < filesys.getFileName(0).size();++i)
  {
    vector<string> filename;
    for(size_t k = 0;k < num_row*num_col;++k)
#ifdef TOBEADJUSTMENT
      filename.push_back(filesys.getFileName(order[k])[i]);
#else
      filename.push_back(filesys.getFileName(k)[i]);
#endif
    CT.RunColorTransfer(filename,output_path);
    if(i == 0) cout << "image:" << endl;
    cout << i << " ";
    if(i != 0 && i % 10==0) cout << endl;
  }
  cout <<endl<< "finished" << endl;
  for(size_t i = 0;i < num_row*num_col;++i)
  {
    string file = string("source image ") + to_string(i);
    cv::imshow(file, CT.GetImgeSouce(i));
  }
  cv::imshow("result image", CT.GetImgeTarget());
  cvWaitKey(0);
  cvDestroyAllWindows();
  return 0;
}
33
