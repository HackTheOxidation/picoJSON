#include <Parser.hpp>

using namespace std;

namespace picoJSON {
  Parser::Parser(string fileName) {
        Reader reader(fileName);
        Lexer lexer(reader.getContent());
        tokens_ = lexer.tokenize(); 
        currentTokenPair_ = nullptr;
        index_ = 0;
      }

  Parser::Parser(vector<pair<Token, string>*>* tokens) : tokens_(tokens), currentTokenPair_(nullptr), index_(0) {}

      Content Parser::getContent() {
        try {
          JSON* json = parseJSON();
          JSONObject* obj = static_cast<JSONObject*>(json);
          return *(new Content(obj->getValue()));
        } catch (exception e) {
          return *(new Content(nullptr));
        }
      }

      vector<pair<Token, string>*>* Parser::getTokens() const {
        return tokens_;
      }

      void Parser::printTokens() const {
        for (pair<Token, string>* p : *tokens_) {
          cout << "type: ";
          switch (p->first) {
            case STRING:
              cout << "STRING, ";
              break;
            case NUMBER:
              cout << "NUMBER, ";
              break;
            case WHITESPACE:
              cout << "WHITESPACE, ";
              break;
            case COLON:
              cout << "COLON, ";
              break;
            case COMMA:
              cout << "COMMA, ";
              break;
            case LPAREN:
              cout << "LPAREN, ";
              break;
            case RPAREN:
              cout << "RPAREN, ";
              break;
            case LBRACE:
              cout << "LBRACE, ";
              break;
            case RBRACE:
              cout << "RBRACE, ";
              break;
            case LCURLY:
              cout << "LCURLY, ";
              break;
            case RCURLY:
              cout << "RCURLY, ";
              break;
            case JSONTRUE:
              cout << "JSONTRUE, ";
              break;
            case JSONFALSE:
              cout << "JSONFALSE, "; 
              break;
            case JSONNULL:
              cout << "JSONNULL, ";
              break;
          }

          cout << "value: " << p->second << endl;
        }
      }

      void Parser::print() const {
        for (pair<Token, string>* p : *tokens_) {
          string tok = "";
          switch (p->first) {
            case STRING:
              tok = "STRING ";
              break;
            case NUMBER:
              tok = "NUMBER ";
              break;
            case JSONTRUE:
              tok = "JSONTRUE ";
              break;
            case JSONFALSE:
              tok = "JSONFALSE ";
              break;
            case JSONNULL:
              tok = "JSONNULL ";
              break;
            case WHITESPACE:
              continue;
            default:
              break;
          }

          if (tok != "") {
            cout << tok;
          }
          cout << p->second << " ";
        }
      }

}
