#include <string>
#include <cstdint>
#include <ecomm/model/food_product.hpp>
#include <ecomm/util.hpp>
#include <nlohmann/json.hpp>
#include <iostream>

namespace ecomm
{
    namespace model
    {
        std::string food_product::detail() const
        {
            std::stringstream ss;
            ss << "\033[36mName:        \033[0m" << title << std::endl;
            ss << "\033[36mExpiration:  \033[0m" << util::timestamp_to_date_string(expired_at) << std::endl;
            ss << "\033[36mManufacture: \033[0m" << util::timestamp_to_date_string(manufactured_at) << std::endl;
            ss << "\033[36mOrigin price:\033[0m" << price << std::endl;
            ss << "\033[36mSpecial:     \033[0m" << real_price_str() << std::endl;
            ss << "\033[36mID:          \033[0m" << id << std::endl;
            ss << "\033[36mSeller ID:   \033[0m" << uid << std::endl;
            ss << "\033[36mDiscount:    \033[0m" << discount_str() << " off" << std::endl;
            ss << "\033[36mTotal:       \033[0m" << total_amount << std::endl;
            ss << "\033[36mAvailable:   \033[0m" << available_amount << std::endl;
            ss << "\033[36mType:        \033[0m" << type << std::endl;
            ss << "\033[36mDescription: \033[0m" << description << std::endl;
            return ss.str();
        }
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
