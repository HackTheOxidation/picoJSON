#include <Lexer.hpp>

using namespace std;

namespace picoJSON {
Lexer::Lexer(string json) : json_(json) { tokenize(); }

vector<pair<Token, string> *> *Lexer::tokenize() {
  vector<pair<Token, string> *> *tokens = new vector<pair<Token, string> *>();

  unsigned int line = 1;
  bool isString = false;
  bool isNumber = false;
  bool isBool = false;
  bool isNull = false;
  bool decimal = false;
  bool exponent = false;
  string buffer = "";
  for (char c : json_) {
    if (c == EOF)
      break;
    else if (c == '{') {
      if (isString)
        buffer += c;
      else {
        buffer = c;
        tokens->push_back(new pair<Token, string>(LCURLY, buffer));
        buffer = "";
        line++;
      }
    } else if (c == '}') {
      if (isString)
        buffer += c;
      else {
        if (isNumber) {
          if (buffer[buffer.length() - 1] == 'e' ||
              buffer[buffer.length() - 1] == 'E')
            throw SyntaxException(buffer, line);

          if (buffer[buffer.length() - 1] == '-' ||
              buffer[buffer.length() - 1] == '+' ||
              buffer[buffer.length() - 1] == '.')
            throw SyntaxException(buffer, line);

          tokens->push_back(new pair<Token, string>(NUMBER, buffer));
          buffer = "";
          isNumber = false;
          decimal = false;
          exponent = false;
        } else if (isBool) {
          if (buffer.compare("true") == 0)
            tokens->push_back(new pair<Token, string>(JSONTRUE, buffer));
          else if (buffer.compare("false") == 0)
            tokens->push_back(new pair<Token, string>(JSONFALSE, buffer));
          else
            throw SyntaxException(buffer, line);

          isBool = false;
        } else if (isNull) {
          if (buffer.compare("null") == 0)
            tokens->push_back(new pair<Token, string>(JSONFALSE, buffer));
          else
            throw SyntaxException(buffer, "null", line);

          isNull = false;
        }

        buffer = c;
        tokens->push_back(new pair<Token, string>(RCURLY, buffer));
        buffer = "";
        line++;
      }
    } else if (c == '[') {
      if (isString)
        buffer += c;
      else {
        buffer = c;
        tokens->push_back(new pair<Token, string>(LBRACE, buffer));
        buffer = "";
      }
    } else if (c == ']') {
      if (isString)
        buffer += c;
      else {
        if (isNumber) {
          if (buffer[buffer.length() - 1] == 'e' ||
              buffer[buffer.length() - 1] == 'E')
            throw SyntaxException(buffer, line);

          if (buffer[buffer.length() - 1] == '-' ||
              buffer[buffer.length() - 1] == '+' ||
              buffer[buffer.length() - 1] == '.')
            throw SyntaxException(buffer, line);

          tokens->push_back(new pair<Token, string>(NUMBER, buffer));
          buffer = "";
          isNumber = false;
          decimal = false;
          exponent = false;
        } else if (isBool) {
          if (buffer.compare("true") == 0)
            tokens->push_back(new pair<Token, string>(JSONTRUE, buffer));
          else if (buffer.compare("false") == 0)
            tokens->push_back(new pair<Token, string>(JSONFALSE, buffer));
          else
            throw SyntaxException(buffer, line);

          isBool = false;
        } else if (isNull) {
          if (buffer.compare("null") == 0)
            tokens->push_back(new pair<Token, string>(JSONFALSE, buffer));
          else
            throw SyntaxException(buffer, "null", line);

          isNull = false;
        }

        buffer = c;
        tokens->push_back(new pair<Token, string>(RBRACE, buffer));
        buffer = "";
        line++;
      }
    } else if (c == '(') {
      if (isString)
        buffer += c;
      else {
        buffer = c;
        tokens->push_back(new pair<Token, string>(LPAREN, buffer));
        buffer = "";
      }
    } else if (c == ')') {
      if (isString)
        buffer += c;
      else {
        if (isNumber) {
          if (buffer[buffer.length() - 1] == 'e' ||
              buffer[buffer.length() - 1] == 'E')
            throw SyntaxException(buffer, line);

          if (buffer[buffer.length() - 1] == '-' ||
              buffer[buffer.length() - 1] == '+' ||
              buffer[buffer.length() - 1] == '.')
            throw SyntaxException(buffer, line);

          tokens->push_back(new pair<Token, string>(NUMBER, buffer));
          buffer = "";
          isNumber = false;
          decimal = false;
          exponent = false;
        } else if (isBool) {
          if (buffer.compare("true") == 0)
            tokens->push_back(new pair<Token, string>(JSONTRUE, buffer));
          else if (buffer.compare("false") == 0)
            tokens->push_back(new pair<Token, string>(JSONFALSE, buffer));
          else
            throw SyntaxException(buffer, line);

          isBool = false;
        } else if (isNull) {
          if (buffer.compare("null") == 0)
            tokens->push_back(new pair<Token, string>(JSONFALSE, buffer));
          else
            throw SyntaxException(buffer, "null", line);

          isNull = false;
        }

        buffer = c;
        tokens->push_back(new pair<Token, string>(RPAREN, buffer));
        buffer = "";
      }
    } else if (c == ',') {
      if (isString)
        buffer += c;
      else {
        if (isNumber) {
          if (buffer[buffer.length() - 1] == 'e' ||
              buffer[buffer.length() - 1] == 'E')
            throw SyntaxException(buffer, line);

          if (buffer[buffer.length() - 1] == '-' ||
              buffer[buffer.length() - 1] == '+' ||
              buffer[buffer.length() - 1] == '.')
            throw SyntaxException(buffer, line);

          tokens->push_back(new pair<Token, string>(NUMBER, buffer));
          buffer = "";
          isNumber = false;
          decimal = false;
          exponent = false;
        } else if (isBool) {
          if (buffer.compare("true") == 0)
            tokens->push_back(new pair<Token, string>(JSONTRUE, buffer));
          else if (buffer.compare("false") == 0)
            tokens->push_back(new pair<Token, string>(JSONFALSE, buffer));
          else
            throw SyntaxException(buffer, line);
          isBool = false;
        } else if (isNull) {
          if (buffer.compare("null") == 0)
            tokens->push_back(new pair<Token, string>(JSONNULL, buffer));
          else
            throw SyntaxException(buffer, "null", line);

          isNull = false;
        }
        buffer = c;
        tokens->push_back(new pair<Token, string>(COMMA, buffer));
        buffer = "";
        line++;
      }
    } else if (c == ':') {
      if (isString)
        buffer += c;
      else {
        buffer = c;
        tokens->push_back(new pair<Token, string>(COLON, buffer));
        buffer = "";
      }
    } else if (c == '\"') {
      if (isString && !isNumber && !isBool && !isNull) {
        tokens->push_back(new pair<Token, string>(STRING, buffer));
        buffer = "";
        isString = false;
      } else if (!isString && !isNumber && !isBool && !isNull) {
        isString = true;
      } else
        throw SyntaxException(buffer, line);
    } else if (c == '.') {
      if (isNumber && !buffer.empty() && !decimal) {
        buffer += c;
        decimal = true;
      } else if (isString) {
        buffer += c;
      } else
        throw SyntaxException(buffer, line);
    } else if (Whitespace.find(c) != string::npos) {
      if (isNumber) {
        if (buffer[buffer.length() - 1] == 'e' ||
            buffer[buffer.length() - 1] == 'E')
          throw SyntaxException(buffer, line);

        if (buffer[buffer.length() - 1] == '-' ||
            buffer[buffer.length() - 1] == '+' ||
            buffer[buffer.length() - 1] == '.')
          throw SyntaxException(buffer, line);

        tokens->push_back(new pair<Token, string>(NUMBER, buffer));
        buffer = "";
        isNumber = false;
        decimal = false;
        exponent = false;
        isBool = false;
      } else if (isString) {
        buffer += c;
      } else if (isBool) {
        if (buffer.compare("true") == 0)
          tokens->push_back(new pair<Token, string>(JSONTRUE, buffer));
        else if (buffer.compare("false") == 0)
          tokens->push_back(new pair<Token, string>(JSONFALSE, buffer));
        else
          throw SyntaxException(buffer, line);

        isBool = false;
      } else if (isNull) {
        if (buffer.compare("null") == 0)
          tokens->push_back(new pair<Token, string>(JSONNULL, buffer));
        else
          throw SyntaxException(buffer, line);

        isNull = false;
      }

      if ((c != ' ' && c != '\t') && !isString)
        line++;

    } else if (Digits.find(c) != string::npos) {
      if (!isString && !isNumber && !isBool && !isNull)
        isNumber = true;
      buffer += c;
    } else {
      if ((c == 'e' || c == 'E') && isNumber && !exponent) {
        buffer += c;
        exponent = true;
      } else if ((c == 't' || c == 'f') && !isString) {
        buffer += c;
        isBool = true;
      } else if ((c == 'n') && !isString) {
        buffer += c;
        isNull = true;
      } else if (c == '-' && !isString) {
        if (isNumber && (buffer[buffer.length() - 1] == 'e' ||
                         buffer[buffer.length() - 1] == 'E')) {
          buffer += c;
        } else
          throw SyntaxException(buffer, line);
      } else if (c == '+' && isNumber) {
        if (buffer[buffer.length() - 1] == 'e' ||
            buffer[buffer.length() - 1] == 'E') {
          buffer += c;
        } else
          throw SyntaxException(buffer, line);
      } else if (isString || isBool || isNull) {
        buffer += c;
      } else
        throw SyntaxException(buffer, line);
    }
  }

  return tokens;
}
} // namespace picoJSON
