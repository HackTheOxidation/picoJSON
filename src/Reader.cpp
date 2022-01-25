#include <Reader.hpp>

using namespace std;

namespace picoJSON {
Reader::Reader(string fileName) : fileName_(fileName) {}

string Reader::getContent() const {
  string content = "";
  fstream file;
  file.open(fileName_);

  if (!file.is_open())
    throw exception();

  string temp = "";
  while (getline(file, temp))
    content.append(temp);

  file.close();

  return content;
}
} // namespace picoJSON
