//
// Created by what's wrong on 10/21/2023.
//

#ifndef COMMAND_LINE_SCANNER_H
#define COMMAND_LINE_SCANNER_H

#endif //COMMAND_LINE_SCANNER_H
//
// Created by what's wrong on 10/20/2023.
//
#include<stdexcept>
#include <utility>
#include<variant>
#include <map>
#include<vector>
#include<string>
#include <iostream>
#include<string_view>
#include<sstream>
//词法分析，识别JSON的各个TOKEN
namespace civitasv {
    using std::string;
    namespace json {
        class Scanner {
        public:
            Scanner(const std::string& source1):source(source1),current_(0){};
            Scanner(std::string&& source1) : source(std::move(source1)), current_(0) {}

            enum class JsonTokenType {
                BEGIN_OBJECT,//{
                END_OBJECT,//}
                VALUE_SEPRATOR, // ,
                NAME_SEPRATOR, // :
                VALUE_STRING, // "string"
                VALUE_NUMBER, // number
                LOGIC_TRUE,
                LOGIC_FALSE,
                LOGIC_NULL,

                BEGIN_ARRAY, //[
                END_ARRAY, //]

                END_OF_SOURCE,//EOF
                ERROR

            };
            friend std::ostream& operator<<(std::ostream& os,const JsonTokenType& type) {
                //运算符重载
                /*
                 * operator<< 函数定义 JsonTokenType 类对象以可读的形式输出到输出流
                 */
                switch (type) {
                    case JsonTokenType::BEGIN_ARRAY:
                        os << "[";
                        break;
                    case JsonTokenType::END_ARRAY:
                        os << "]";
                        break;
                    case JsonTokenType::BEGIN_OBJECT:
                        os << "{";
                        break;
                    case JsonTokenType::END_OBJECT:
                        os << "}";
                        break;
                    case JsonTokenType::VALUE_NUMBER:
                        os << "number";
                        break;
                    case JsonTokenType::VALUE_STRING:
                        os << "string";
                        break;
                    case JsonTokenType::LOGIC_NULL:
                        os << "NULL";
                        break;
                    case JsonTokenType::LOGIC_FALSE:
                        os << "False";
                        break;
                    case JsonTokenType::LOGIC_TRUE:
                        os << "True";
                        break;
                    case JsonTokenType::VALUE_SEPRATOR:
                        os << ",";
                        break;
                    case JsonTokenType::NAME_SEPRATOR:
                        os << ":";
                        break;
                    default:
                        throw std::logic_error("operator error");
                }
            }
            JsonTokenType scan();//从当前的token扫描触发，返回下一个token的type
            string Get_value_string(){return value_string;}
            float Get_value_number() {return value_number;}


            void Roll_back();

        private:
            string source;
            size_t current_; //目前处理的位置
            size_t prev_pos_;     ///< previous pos of processing character
            string value_string;
            float value_number;
            bool ISEND();
            char Advance();

            void scantrue();
            void scanfalse();
            void scannull();
            void scanstring();
            void scannumber();
            bool IsDigit(char c)
            {
                return c>='0'&&c<='9';
            }
            char Peek() {
                if(ISEND() )
                    return '\0';
                else
                    return source[current_];

            }
            char PeekNext(){
                if(current_+1>=source.size())
                    return '\0';
                return source[current_+1];
            }

        };
    }

}

