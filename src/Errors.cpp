#include <picoJSON/Errors.hpp>
#include <sstream>
#include <string>
#include <string_view>

namespace picoJSON {
const std::string_view SyntaxException::message() const noexcept {
  std::stringstream error;

  if (line_ != 0)
    error << "At line: " + std::to_string(line_) + " -- ";

  error << " ERROR Unexpected Token: \"" << msg_ << "\" .\n";

  if (suggestion_ != "")
    error << "Did you mean: \"" << suggestion_ << "\"?\n";

  return error.str();
}

} // namespace picoJSON
