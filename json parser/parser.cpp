//
// Created by what's wrong on 10/21/2023.
//

#include "cmake-build-debug/Json_element.h"
#include "cmake-build-debug/parser.h"

namespace civitasv{
    namespace json{
        using JsonTokenType=Scanner::JsonTokenType;
        JsonElement* parser::Parser() {

            JsonElement* element=new JsonElement();
            JsonTokenType token_type= scanner_.scan();
            switch (token_type) {
                case JsonTokenType::END_OF_SOURCE:
                    break;
                case JsonTokenType::BEGIN_OBJECT: {
                    //解析object
                    std::map<std::string, JsonElement *> *object = ParseObject();
                    element->value(object);
                    break;

                }
                case JsonTokenType::BEGIN_ARRAY: {
                    std::vector<JsonElement *> *array = ParseArray();
                    element->value(array);
                    break;
                }
                case JsonTokenType::VALUE_STRING: {
                    std::string *str = new std::string(scanner_.Get_value_string());
                    element->value(str);
                    break;
                }
                case JsonTokenType::VALUE_NUMBER: {
                    float num = (scanner_.Get_value_number());
                    element->value(num);
                    break;
                }
                case JsonTokenType::LOGIC_TRUE: {
                    element->value(true);
                    break;
                }
                case JsonTokenType::LOGIC_FALSE: {
                    element->value(false);
                    break;
                }
                case JsonTokenType::LOGIC_NULL: {
                    break;
                }
                default:
                    break;
            }
                return element;
            }

            // ParseObject() 当前对象如果是对象，将其进行转换
            std::map<std::string, JsonElement *>* parser::ParseObject() {
                std::map<std::string, JsonElement *>* res=new std::map<std::string, JsonElement *>();
                JsonTokenType next=scanner_.scan();
                if(next==JsonTokenType::END_OBJECT) return res;
                scanner_.Roll_back();//未到结尾回退一步

                //    {
                //        "glossary":{
                //        "test":true
                //"hello":null
                //"hello2":"maomao"
                //}
                //
                //    }
                while (1) {
                    next = scanner_.scan();
                    if (next != JsonTokenType::VALUE_STRING)
                        throw std::logic_error("key must be a string");
                    string key = scanner_.Get_value_string();
                    next = scanner_.scan();
                    if (next != JsonTokenType::NAME_SEPRATOR) {
                        throw std::logic_error("Expected ':' in object!");
                    }
                    (*res)[key] = Parser();
                    next = scanner_.scan();
                    if (next == JsonTokenType::END_OBJECT) break;
                    if (next != JsonTokenType::VALUE_SEPRATOR) {
                        throw std::logic_error("Expected ',' in object!");
                    }
                }
                    return  res;

        }
        std::vector<JsonElement*> * parser::ParseArray() {
            std::vector<JsonElement*> * res=new std::vector<JsonElement*>();
            JsonTokenType next = scanner_.scan();
            if (next == JsonTokenType::END_ARRAY) {
                return res;
            }
            scanner_.Roll_back();
            while(1){
                res->push_back(Parser());
                next=scanner_.scan();
                if (next == JsonTokenType::END_ARRAY) {
                    break;
                }
                if (next != JsonTokenType::VALUE_SEPRATOR) {
                    throw std::logic_error("Expected ',' in Array!");
                }

            }
            return res;
        }

    }
}