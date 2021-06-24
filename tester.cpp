#include "picoJSON.hpp"
#include <iostream>
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
    cout << "----- PARSING COMPLETED -----" << endl << endl;;

    cout << "----- PARSER OUTPUT -----" << endl;
    content.print();

    cout << endl;
    cout << "----- TESTING TYPE INFERENCE -----" << endl;
    vector<JSONProperty*> properties = content.getProperties();
    cout << "----- TYPE INFERENCING SUCCESSFUL -----" << endl;

    cout << "----- TESTING EXTRACTION -----" << endl;
    for (JSONProperty* prop : properties) {
      cout << *prop << endl;
    }
    
    cout << endl << "Does num exist? " << content.search("num") << endl;
    float* num = (float *) content.getValue("num", picoJSON::Number);
    cout << endl << "Value of num: " << *num << endl; 

    cout << endl << "Does arr exist? " << content.search("arr") << endl;
    JSONArray* arr = (JSONArray*) content.getValue("arr", picoJSON::Array);
    cout << endl << "Value of arr: ";
    arr->print(); 
    cout << endl;

    float f = content.extractNumber("float");

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
