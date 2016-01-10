#include <string>
#include <fstream>
#include <unordered_map>

class DataExtract
{
public:
  DataExtract();
  ~DataExtract();
  DataExtract(const std::string& file_in, const std::string &op_type,
              const char &c=' ');
  void OpOnString();
  typedef void(DataExtract::*funPtr)(const std::string &);
protected:
  void Increase(const std::string&);
  void IncreaseFirstNumber(const std::string &);
  //aux function
  void ErrorOutput();
private:
  //std::string input_file_name, output_file_name;
  char separator;
  std::unordered_map<std::string, int> op_map;
  funPtr func_ptr;
  std::ofstream ofs;
  std::ifstream ifs;
};

