//
// Created by what's wrong on 10/21/2023.
//
#include<stdexcept>
#include <utility>
#include<variant>
#include <map>
#include<vector>
#include<string>
#include<string_view>
#include<sstream>
#include "scanner.h"
#include "Json_element.h"
namespace civitasv{
    using std::string;
    namespace json{
        class parser{
        public:
            parser(const Scanner& scanner) : scanner_(scanner) {};
            JsonElement* Parser();
        private:
            Scanner scanner_;
            std::map<std::string, JsonElement*>* ParseObject();
            std::vector<JsonElement*> * ParseArray();


        };
    }
}



