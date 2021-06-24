#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <iostream>
#include <exception>
#include <string>

using namespace std;

namespace picoJSON {
  class SyntaxException {
    public:
      SyntaxException(string& msg) : msg_(msg), suggestion_(""), line_(0) {}
      SyntaxException(string& msg, unsigned int line) : msg_(msg), suggestion_(""), line_(line) {}
      SyntaxException(string& msg, string suggestion) : msg_(msg), suggestion_(suggestion), line_(0) {}
      SyntaxException(string& msg, string suggestion, unsigned int line) : msg_(msg), suggestion_(suggestion), line_(line) {}

      const char* message() const noexcept {
        string* error = new string("");
        
        if (line_ != 0)
          (*error) += "At line: " + to_string(line_) + " -- ";

        (*error) += " ERROR Unexpected Token: \"" + msg_ + "\" .\n";
        
        if (suggestion_.compare("") != 0)
          (*error) += "Did you mean: \"" + suggestion_ + "\"?\n";
        return error->c_str();
      }

    private:
      string msg_;
      unsigned int line_;
      string suggestion_;
  };
}

#endif
