#ifndef PICOJSON_HPP_
#define PICOJSON_HPP_

#include "Reader.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "JSON.hpp"
#include "JSONProperty.hpp"
#include "JSON.cpp"
#include "JSONArray.hpp"
#include "JSONBool.hpp"
#include "JSONNull.hpp"
#include "JSONNumber.hpp"
#include "JSONObject.hpp"
#include "JSONString.hpp"
#include "Content.hpp"

using namespace std;

/*
 * SYNTAX:
 *
 * <json> := <value>
 * <value> := <object> | <array> | <bool> | <string> | <number> | <null>
 * <array> := "[" [<value>] {"," <value>}* "]"
 * <object> := "{" [<property>] {"," <property>}* "}"
 * <property> := <string> ":" <value>
 *
 */

namespace picoJSON {

}
#endif
