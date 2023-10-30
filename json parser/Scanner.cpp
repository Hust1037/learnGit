//
// Created by what's wrong on 10/21/2023.
//
#include"cmake-build-debug/scanner.h"
#include <stdexcept>
namespace civitasv{
    namespace json{
        bool Scanner::ISEND() {
            return current_ >=source.size();
        }
        char Scanner::Advance() {
            return source[current_++];
        }
        void Scanner::scantrue() {
            if(source.compare(current_,3,"rue")==0)
            {
                current_+=3;
            }
            else
                throw std::logic_error("scan true error");
        }
        void Scanner::scanfalse() {
            if(source.compare(current_,4,"alse")==0)
            {
                current_+=4;
            }
            else
                throw std::logic_error("scan false error");
        }
        void Scanner::scannull() {
            if(source.compare(current_,3,"ull")==0)
            {
                current_+=3;
            }
            else
                throw std::logic_error("scan null error");
        }
        void Scanner::scanstring()
        {
            //"test"
            size_t pos=current_;
            while(Peek()!='\"'&&!ISEND()){
                Advance();
            }
            if(ISEND())
            {
                throw std::logic_error("Invalid string :missing closing quote!");
            }
            Advance();
            value_string=source.substr(pos,current_-pos-1);
        }
        void Scanner::scannumber()  {
            size_t pos = current_ - 1;

            while (IsDigit(Peek())) {
                Advance();
            }

            // fractional part
            if (Peek() == '.' && IsDigit(PeekNext())) {
                Advance();
                while (IsDigit(Peek())) {
                    Advance();
                }
            }

            value_number = std::atof(source.substr(pos, current_ - pos).c_str());
        }
        void Scanner::Roll_back() {
            current_=prev_pos_;
        }
        Scanner::JsonTokenType Scanner::scan() { //从当前的token扫描触发，返回下一个token的type
            if(ISEND()){
                return JsonTokenType::END_OF_SOURCE;
            }
            prev_pos_ = current_;
            char c=Advance();
            switch (c) {
                case '[':
                    return JsonTokenType::BEGIN_ARRAY;
                case ']':
                    return JsonTokenType::END_ARRAY;
                case '{':
                    return JsonTokenType::BEGIN_OBJECT;
                case '}':
                    return JsonTokenType::END_OBJECT;
                case ':':
                    return JsonTokenType::NAME_SEPRATOR;
                case ',':
                    return JsonTokenType::VALUE_SEPRATOR;
                case 't':
                    scantrue();
                    return JsonTokenType::LOGIC_TRUE;
                case 'f':
                    scanfalse();
                    return JsonTokenType::LOGIC_FALSE;
                case 'n':
                    scannull();
                    return JsonTokenType::LOGIC_NULL;
                case '-':
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    scannumber();
                    return JsonTokenType::VALUE_NUMBER;
                case '\"':
                    scanstring();
                    return JsonTokenType::VALUE_STRING;
                case ' ':
                case '\r':
                case '\n':
                case '\t':
                    return scan();
                default:
                    // error
                    std::string message = "Unsupported Token: ";
                    message += c;
                    throw std::logic_error(std::string(message));
                    return JsonTokenType::ERROR;
            }
            return JsonTokenType();
        }


    }
}

