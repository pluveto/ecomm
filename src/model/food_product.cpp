#include <string>
#include <cstdint>
#include <ecomm/model/food_product.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
namespace ecomm
{
    namespace model
    {
        std::string food_product::to_ext_props()
        {
            nlohmann::json j;
            j["expired_at"] = this->expired_at;
            j["manufactured_at"] = this->manufactured_at;
            return j.dump();
        }

        void food_product::from_ext_props(std::string ext_props)
        {
            nlohmann::json j = nlohmann::json::parse(ext_props);
            this->expired_at = j["expired_at"].get<time_t>();
            this->manufactured_at = j["manufactured_at"].get<time_t>();
        }

    }
}
