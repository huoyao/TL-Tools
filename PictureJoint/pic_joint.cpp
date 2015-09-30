#include "pic_joint.h"
#include <iostream>
#include <vector>
using namespace std;
using namespace tl;

PicJiont::PicJiont(void):scale(0.5),row_num(2),col_num(2){
  init();
}

PicJiont::PicJiont(const double &scal, const int& rows, const int&cols) : scale(scal), row_num(rows), col_num(cols)
{
  init();
}

void PicJiont::init()
{
  pic_num = row_num*col_num;
  image_souce_ = new cv::Mat[pic_num];
}

PicJiont::~PicJiont(void){
  delete[] image_souce_;
}

bool PicJiont::LoadImage(const vector<std::string> &imagename_souce)
{
  if(imagename_souce.size() == 0 || imagename_souce.size()!=pic_num) return false;
  for(size_t i = 0;i < imagename_souce.size();++i)
  {
    image_souce_[i] = cv::imread(imagename_souce[i]);
    if(image_souce_[i].empty()) return false;
  }
  width_target_ = 0;
  height_target_ = 0;
  for(size_t i = 0;i < pic_num;++i)
  {
    width_target_ = max(width_target_, image_souce_[i].cols);
    height_target_ = max(height_target_, image_souce_[i].rows);
  }
  height_target_ *= row_num;
  width_target_ *= col_num;
  image_target_ = cv::Mat(height_target_, width_target_, CV_8UC3);
  return true;
}

void PicJiont::AddPixel()
{
  int k = 0, idx = 0, idy = 0,idx_bak=0,idy_bak=0;
  for(size_t i = 0;i < row_num;++i)
  {
    idy_bak = 0;
    for(size_t j = 0;j < col_num;++j)
    {
      idx = idx_bak;
      for(size_t k0 = 0; k0<image_souce_[k].rows;++k0)
      {
        idy = idy_bak;
        for(size_t k1 = 0;k1<image_souce_[k].cols;++k1)
        {
          image_target_.at<cv::Vec3b>(idx, idy++) = image_souce_[k].at<cv::Vec3b>(k0, k1);
        }
        ++idx;
      }
      idy_bak += image_souce_[i*col_num + j].cols;
      ++k;
    }
    idx_bak += image_souce_[i*col_num].rows;
  }
}


void PicJiont::RunColorTransfer(const vector<std::string> &imagename_souce,string output_pth){
  if(!LoadImage(imagename_souce))
  {
    printf("Error load image\n");
    return;
  }
  AddPixel();
  cv::Size scal = cv::Size(image_target_.cols*scale, image_target_.rows*scale);
  cv::resize(image_target_, image_target_, scal);
  output_pth += imagename_souce[0].substr(imagename_souce[0].length() - 8, imagename_souce[0].length());
  cv::imwrite(output_pth, image_target_);
}


