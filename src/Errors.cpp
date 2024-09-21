#include <Errors.hpp>
#include <string>

namespace picoJSON {
const std::string_view SyntaxException::message() const noexcept {
  std::string error;

  if (line_ != 0)
    error += "At line: " + std::to_string(line_) + " -- ";

  error += " ERROR Unexpected Token: \"" + std::string(msg_) + "\" .\n";

  if (suggestion_ != "")
    error += "Did you mean: \"" + std::string(suggestion_) + "\"?\n";
  return error;
}

} // namespace picoJSON
