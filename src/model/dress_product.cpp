#include <string>
#include <cstdint>
#include <ecomm/model/dress_product.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
namespace ecomm
{
    namespace model
    {
         std::string dress_product::detail() const
        {
            std::stringstream ss;
            ss << "\033[36mName:        \033[0m" << title << std::endl;
            ss << "\033[36mSize:        \033[0m" << size << std::endl;
            ss << "\033[36mBrand:       \033[0m" << brand << std::endl;            
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
