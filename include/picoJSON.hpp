#ifndef PICOJSON_HPP_
#define PICOJSON_HPP_

#include <picoJSON/Content.hpp>
#include <picoJSON/JSON.hpp>
#include <picoJSON/JSONArray.hpp>
#include <picoJSON/JSONBool.hpp>
#include <picoJSON/JSONNull.hpp>
#include <picoJSON/JSONNumber.hpp>
#include <picoJSON/JSONObject.hpp>
#include <picoJSON/JSONProperty.hpp>
#include <picoJSON/JSONString.hpp>
#include <picoJSON/Lexer.hpp>
#include <picoJSON/Parser.hpp>
#include <picoJSON/Reader.hpp>

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

namespace picoJSON {}
#endif
