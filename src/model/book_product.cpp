#include <string>
#include <cstdint>
#include <ecomm/model/book_product.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
namespace ecomm
{
    namespace model
    {
        std::string book_product::detail() const
        {
            std::stringstream ss;
            ss << "\033[36mName:        \033[0m" << title << std::endl;
            ss << "\033[36mAuthor:      \033[0m" << author << std::endl;
            ss << "\033[36mPress:       \033[0m" << press << std::endl;
            ss << "\033[36mISBN:        \033[0m" << isbn << std::endl;
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
