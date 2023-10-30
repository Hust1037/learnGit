//
// Created by what's wrong on 10/21/2023.
//
#pragma once
#include <string>
#include <variant>
#include<map>
#include<vector>
#include <sstream>
//#define JsonObject std::map<std::string ,JsonElement>
//#define JsonArray std::vector<JsonElement>
namespace civitasv{
    using std::map;
    using std::vector;
    using std::string;
    namespace json{
        class JsonElement{
        public:
            enum class type{
                JSON_OBJECT,
                JSON_ARRAY,
                JSON_NUMBER,
                JSON_STRING,
                JSON_BOOL,
                JSON_NULL
            };
            union Value{
                map<std::string ,JsonElement*>* value_object;
                vector<JsonElement*>* value_array;
                std::string* value_string;
                float value_number;
                bool value_bool;
            };

            JsonElement(map<std::string ,JsonElement*>* object) : Type_(type::JSON_OBJECT) { value(object); }

            JsonElement(vector<JsonElement*>* array) : Type_(type::JSON_ARRAY) { value(array); }

            JsonElement(string* value_string):Type_(type::JSON_STRING) { value(value_string); }
            JsonElement(float number) : Type_(type::JSON_NUMBER) { value(number); }
            JsonElement(bool val) : Type_(type::JSON_BOOL) { value(val); }
            JsonElement():Type_(type::JSON_NULL){};
            void value(map<std::string ,JsonElement*> *value_object)
            {
                Type_=type::JSON_OBJECT;
                value_.value_object=value_object;
            }
            void value(vector<JsonElement*>* value_array)
            {
                Type_=type::JSON_OBJECT;
                value_.value_array=value_array;
            }
            void value(string *str)
            {
                Type_=type::JSON_STRING;
                value_.value_string=str;
            }
            void  value(bool BOOL)
            {
                Type_=type::JSON_BOOL;
                value_.value_bool=BOOL;
            }
            void  value(float num)
            {
                Type_=type::JSON_NUMBER;
                value_.value_bool=num;
            }

            map<std::string ,JsonElement*>* GetObject(){
                return value_.value_object;

            }
            vector<JsonElement*>* GetArray()
            {
                return value_.value_array;
            }
            std::string* GetStirng()
            {
                return value_.value_string;
            }
            float GetNumber()
            {
                return value_.value_number;

            }
            bool GetBool(){
                return value_.value_bool;
            }
            //将JSON Element转换成为JSON字符串
            std::string Dumps() {
                std::stringstream ss;
                /*
                 * std::stringstream 是 C++ 标准库中的一个类，它提供了一个方便的接口来进行字符串流操作。
                 * 它通常用于将各种数据类型（如整数、浮点数、字符串等）转换为字符串，或者将字符串解析为不同的数据类型。
                 */
                switch (Type_) {
                    case type::JSON_OBJECT:
                        ss << *(value_.value_object);
                        break;
                    case type::JSON_ARRAY:
                        ss << *(value_.value_array);
                        break;
                    case type::JSON_STRING:
                        ss << '\"' << *(value_.value_string) << '\"';
                        break;
                    case type::JSON_NUMBER:
                        ss << value_.value_number;
                        break;
                    case type::JSON_BOOL:
                        ss << (value_.value_bool == true ? "true" : "false");
                        break;
                    case type::JSON_NULL:
                        ss << "null";
                        break;
                    default:
                        break;
                }
                return ss.str();
            }
            friend std::ostream& operator<<(std::ostream& os, const std::map<std::string, JsonElement *>& object) {
                os << "{";
                for (auto iter = object.begin(); iter != object.end(); iter++) {
                    os << '\"' << iter->first << '\"' << ": " << iter->second->Dumps();
                    if (iter != --object.end()) {
                        os << ", ";
                    }
                }
                os << "}";
                return os;
            }

            friend std::ostream& operator<<(std::ostream& os, const std::vector<JsonElement*>& array) {
                os << "[";
                for (size_t i = 0; i < array.size(); i++) {
                    os << array[i]->Dumps();
                    if (i != array.size() - 1) {
                        os << ", ";
                    }
                }
                os << "]";
                return os;
            }


        private:
            type Type_;
            Value value_;
        };
    };
}


