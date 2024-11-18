#include <Reader.hpp>
#include <sstream>

namespace picoJSON {
Reader::Reader(const std::string_view file_name) : file_name_(file_name) {}

std::stringstream Reader::get_content() const {
  std::stringstream content;
  std::ifstream file;
  file.open(file_name_);

  if (!file.is_open())
    throw exception();

  std::string temp = "";
  while (getline(file, temp))
    content << temp;

  file.close();

  return content;
}
} // namespace picoJSON
