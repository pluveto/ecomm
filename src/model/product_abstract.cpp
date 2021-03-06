/**
 * @file product_abstract.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-23
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */

#include <ecomm/model/product_abstract.hpp>

#include <string>
#include <iostream>
#include <cstdint>
#include <iomanip>
namespace ecomm
{
    namespace model
    {
        std::string product_abstract::brief() const
        {
            std::stringstream ss;
            ss << "#" << id << " - \033[32m" << title << "\033[0m" << std::endl;
            ss << "    Price: \033[31m$" << real_price_str() << "\033[0m( " + discount_str() << " off, from " << price_str() << ")" << std::endl;
            return ss.str();
        }

        std::string product_abstract::detail() const
        {
            std::stringstream ss;
            ss << "\033[36mName:        \033[0m" << title << std::endl;
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

        std::string product_abstract::price_str() const
        {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << this->price;
            return ss.str();
        }

        std::string product_abstract::discount_str() const
        {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(0) << (100 * this->discount) << "%";
            return ss.str();
        }

        std::string product_abstract::real_price_str() const
        {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << this->real_price();
            return ss.str();
        }

        double product_abstract::real_price() const
        {
            return this->price * (1 - this->discount);
        }

        product_abstract::~product_abstract() {}
        product_abstract::product_abstract() {}

    }
}