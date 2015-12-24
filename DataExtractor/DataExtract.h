#include <string>
#include <fstream>

class DataExtract
{
public:
  DataExtract();
  ~DataExtract();
  DataExtract(const std::string& file_in, const std::string &file_out,
              const char &,const int &);
  void increase(std::string&);
  void opOnString();
  typedef void(DataExtract::*funPtr)(std::string &);
private:
  std::string input_file_name, output_file_name;
  char separator;
  funPtr func_ptr;
  std::ofstream ofs;
  std::ifstream ifs;
};

