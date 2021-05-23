#include <string>
#include <cstdint>
#include <ecomm/model/book_product.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
namespace ecomm
{
    namespace model
    {
        std::string book_product::to_ext_props()
        {
            nlohmann::json j;
            j["author"] = this->author;
            j["press"] = this->press;
            j["isbn"] = this->isbn;
            return j.dump();
        }

        void book_product::from_ext_props(std::string ext_props)
        {
            nlohmann::json j = nlohmann::json::parse(ext_props);
            this->author = j["author"].get<std::string>();
            this->press = j["press"].get<std::string>();
            this->isbn = j["isbn"].get<std::string>();
        }

    }
}
