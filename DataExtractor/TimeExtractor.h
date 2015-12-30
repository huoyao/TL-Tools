#ifndef __TIMEEXTRACTOR_H__
#define __TIMEEXTRACTOR_H__
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class TimeExtractor{
public:
  TimeExtractor();
  ~TimeExtractor();
  TimeExtractor(const std::string & file,
                const std::vector<std::string> & double_prefix,
                const std::vector<std::string>& int_prefix):
                prefix_double(double_prefix), prefix_int(int_prefix), file_path(file) {
    init();
  };
  TimeExtractor(const std::vector<std::string> & double_prefix,
                const std::vector<std::string>& int_prefix):
                prefix_double(double_prefix), prefix_int(int_prefix) {
    init();
  };
  void ExtractTime(const std::string &file);

protected:
  inline void SetFileName(const std::string &file) { file_path = file; };
  void init();
  void GenerateOutDir(const std::string&file_name);
  void Out2FileInt(const std::vector<std::string> &prefix_double, const std::vector<int> res_t[], const size_t &i);
  void Out2FileDouble(const std::vector<std::string> &prefix_double, const std::vector<double> res_t[], const size_t &i);
  bool FindValueInALine(const std::string &str_word, bool &is_int, int &value_int, double &value_double);

private:
  std::vector<std::string> prefix_double, prefix_int;
  std::unordered_map<std::string, size_t> str_map_double;
  std::unordered_map<std::string, size_t> str_map_int;
  std::unordered_set<std::string> need_int;
  std::unordered_set<std::string> need_doule;
  std::string file_path,out_dir,file_name,file_type;
};



#endif