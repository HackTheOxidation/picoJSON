#include <iostream>
#include <picoJSON/JSONArray.hpp>
#include <picoJSON/picoJSON.hpp>
#include <stdlib.h>
#include <string>

using namespace picoJSON;
using namespace std;

int main(void) {
  cout << "##### TESTING - picoJSON #####" << endl << endl;
  try {
    Parser parser("config.json");
    cout << "----- LEXING COMPLETED -----" << endl;

    cout << "----- LEXED TOKENS: -----" << endl;
    parser.printTokens();
    cout << endl;

    cout << "----- LEXED TOKENS (Short format): -----" << endl;
    parser.print();

    Content content = parser.getContent();
    cout << "----- PARSING COMPLETED -----" << endl << endl;
    ;

    cout << endl;
    cout << "----- TESTING TYPE INFERENCE -----" << endl;
    vector<JSONProperty *> properties = content.getProperties();
    cout << "----- TYPE INFERENCING SUCCESSFUL -----" << endl;

    cout << "----- TESTING EXTRACTION -----" << endl;
    for (JSONProperty *prop : properties) {
      cout << *prop << endl;
    }

    cout << endl << "Does num exist? " << content.search("num") << endl;
    float num = content["num"].asNumber();
    cout << endl << "Value of num: " << num << endl;

    cout << endl << "Does arr exist? " << content.search("arr") << endl;
    JSON &arr = content["arr"];
    cout << endl << "Value of arr: ";
    arr.print();
    cout << endl;

    cout << "----- EXTRACTION SUCCESSFUL -----" << endl;

  } catch (SyntaxException e) {
    cout << "An error occured" << endl;
    cout << e.message() << endl;
    cout << "FAILURE - Test could not finish." << endl;
    return -1;
  }

  cout << endl;
  cout << "----- SUCCES - Test ran without encountering errors. -----" << endl;

  return 0;
}
