#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <Eigen/Core>
#include <Eigen/Dense>

namespace tl
{
  class PicJiont
  {
  public:
    PicJiont(void);
    PicJiont(const double &,const int&, const int&);
    ~PicJiont(void);
    void init();
    bool LoadImage(const std::vector<std::string> &imagename_souce);
    void AddPixel();
    void RunColorTransfer(const std::vector<std::string> &imagename_souce,std::string );
    cv::Mat GetImgeSouce(const int &id){ return image_souce_[id]; }
    cv::Mat GetImgeTarget(){ return image_target_; }
  private:
    int height_target_, width_target_;
    double scale;                   //user define default:0.5
    int row_num, col_num,pic_num;   //user define  default:2*2
    cv::Mat *image_souce_;
    cv::Mat image_target_;
  };
}
33
