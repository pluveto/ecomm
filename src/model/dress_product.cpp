#include <string>
#include <cstdint>
#include <ecomm/model/dress_product.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
namespace ecomm
{
    namespace model
    {
        std::string dress_product::to_ext_props()
        {
            nlohmann::json j;
            j["size"] = this->size;
            j["brand"] = this->brand;
            return j.dump();
        }

        void dress_product::from_ext_props(std::string ext_props)
        {
            nlohmann::json j = nlohmann::json::parse(ext_props);
            this->size = j["size"].get<std::string>();
            this->brand = j["brand"].get<std::string>();
        }

    }
}
