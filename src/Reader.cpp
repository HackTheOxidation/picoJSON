#include <Reader.hpp>

using namespace std;

namespace picoJSON {
Reader::Reader(std::string file_name) : file_name_(file_name) {}

std::string Reader::get_content() const {
  std::string content = "";
  std::fstream file;
  file.open(file_name_);

  if (!file.is_open())
    throw exception();

  std::string temp = "";
  while (getline(file, temp))
    content.append(temp);

  file.close();

  return content;
}
} // namespace picoJSON
