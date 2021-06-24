# picoJSON - A tiny JSON parser written in C++

picoJSON is a very small library for parsing files with the JSON-format.
It is a header-include only library.

# Building the test

Run:
```
make test
```

# Integrating with your own project

Just copy picoJSON to an appropriate location in your project and include
`picoJSON.hpp`

# API Documentation

To read, lex and parse a .json-file create a `Parser` object as follows:

```
include "picoJSON.hpp" // Include the picoJSON header file to use all of the functionality

using namespace picoJSON; // Use the picoJSON namespace to avoid name resolution conflicts

try {
  Parser parser("<filename>.json"); // Replace <filename> with the actual name of the file that you want to parse.
} catch (exception e) {
  // Handle caught exception
}
```

If the file does not exist or if the file contains syntax errors an exception will be thrown.
Note, that the parser in picoJSON does not care about whitespace as long as the file begins with a json object (`{`) as expected.

To see how the Lexer in picoJSON has analyzed the file, you can print all the lexed tokens:

```
parser.printTokens();

parser.print(); // Short format
```

In picoJSON every json value is contained in a `JSON` object.
All the different json data-types has its own specialized class that inherits from the `JSON` class.
For example all valid numbers are contained in the `JSONNumber` class.

Properties are wrapped in the `JSONProperty` class, which has an identifier (`string`) and a `JSON` object.

To extract all the content in the parsed file use the method `getContent()`, which returns a `Content` object.
```
Content content = parser.getContent();
```

The `Content` object wraps the parsed json as a list (STL, `vector`) of `JSONProperty` pointers and provides functionality to extract values by identifiers/variable names.
The `getValue()` method returns a void pointer to the value of a `JSON` object.
A data-types is parsed as an argument, so the returned void pointer can safely be cast to a pointer of the desired data-type.
For example to get the value of the identifier `"num"`, which is a number (`float`):
```
float* num = (float *) content.getValue("num", picoJSON::Number); // picoJSON::Number
```
If no identifier `"num"` is found or if the expected type does not match then a `nullptr` will be returned, so remember to check the returned value.

The following table provides an overview of the json data-types, their wrapper class names in picoJSON and the corresponding data-types used in `C++`:
| picoJSON name | picoJSON class | C++ Data Type |
| ------------- | -------------- | ------------- |
| `picoJSON::Number` | `JSONNumber` | `float` |
| `picoJSON::Array` | `JSONArray` | `vector<JSON*>*` |
| `picoJSON::Null` | `JSONNull` | `int` |
| `picoJSON::True` | `JSONTrue` | `bool` |
| `picoJSON::False` | `JSONFalse` | `bool`|
| `picoJSON::String` | `JSONString` | `string` |
| `picoJSON::Object` | `JSONObject` | `vector<JSONProperty*>*` |

Another way to extract values is to use the `extractNumber()` and `extractString()` methods.
Similarly to the above example the value of the identifier `"num"` can be extracted:
```
float f = content.extractNumber("float");
```

The `extractNumber()` will return a float if the identifier `"num"` exists and has the type `picoJSON::Number`.
Otherwise `NULL` will be return, so again remember to check the returned value.

In the case of `extractString()` a `string` will be returned if the identifier exists and has the type `picoJSON::String`.
Otherwise `0` will be returned.
