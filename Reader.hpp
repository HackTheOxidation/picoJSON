#ifndef READER_HPP
#define READER_HPP

#include "Token.hpp"
#include <fstream>
#include <iostream>

using namespace std;

namespace picoJSON {
  const string Whitespace = "\r\n\t ";
  const string Digits = "1234567890";

  class Reader {
    public:
      Reader(string fileName) : fileName_(fileName) {}

      string getContent() const {
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
      
    private:
      string fileName_;
  };
}

#endif
