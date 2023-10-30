#include <iostream>
#include<map>
#include<variant>
#include "cmake-build-debug/scanner.h"
#include "cmake-build-debug/parser.h"

using namespace std;
int main() {
    using namespace civitasv::json;
    auto source=R"(
    {
        "glossary":{
        "test":true
"hello":null
"hello2":"maomao"
}

    }

)";
    auto source1 = R"(
    {
      "name": "古月有三木",
      "university": "whu",
      "age": -22,
      "gender": "男",
      "isProgrammer": true,
      "skills": ["C++", "JS/TS", "Java"]
    }
  )";
auto source2="[1,2,3,4,5,\"hello\"]";
Scanner scanner(source);
Scanner::JsonTokenType type;
    while ((type = scanner.scan()) != Scanner::JsonTokenType::END_OF_SOURCE) {
        std::cout << "Type: " << type;
        if (type == Scanner::JsonTokenType::VALUE_NUMBER) {
            std::cout << " Value: " << scanner.Get_value_number();
        } else if (type == Scanner::JsonTokenType::VALUE_STRING) {
            std::cout << " Value: " << scanner.Get_value_string();
        }
        std::cout << '\n';
    }
   Scanner scanner1(source1);
    parser parser(scanner1);
     JsonElement * res=parser.Parser();
    std::map<std::string, JsonElement *>* obj=res->GetObject();
    res->Dumps();
    delete res;

}
