#include <Errors.hpp>

using namespace std;

namespace picoJSON {
  SyntaxException::SyntaxException(string& msg) : msg_(msg), suggestion_(""), line_(0) {}

  SyntaxException::SyntaxException(string& msg, unsigned int line) : msg_(msg), suggestion_(""), line_(line) {}


  SyntaxException::SyntaxException(string& msg, string suggestion) : msg_(msg), suggestion_(suggestion), line_(0) {}

  SyntaxException::SyntaxException(string& msg, string suggestion, unsigned int line) : msg_(msg), suggestion_(suggestion), line_(line) {}

  const char* SyntaxException::message() const noexcept {
        string* error = new string("");
        
        if (line_ != 0)
          (*error) += "At line: " + to_string(line_) + " -- ";

        (*error) += " ERROR Unexpected Token: \"" + msg_ + "\" .\n";
        
        if (suggestion_.compare("") != 0)
          (*error) += "Did you mean: \"" + suggestion_ + "\"?\n";
        return error->c_str();
  }

  ParserException::ParserException(string msg) : msg_(msg) {}

  const char* ParserException::message() const noexcept {
    string* error = new string("");
    (*error) += " ERROR Unexpected Token: \"" + msg_ + "\" .\n";
    return error->c_str();
  }
}
