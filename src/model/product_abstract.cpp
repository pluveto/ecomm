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
            ss << "#" << id << " - " << title << std::endl;
            ss << "    Price: $" << real_price_str() << "( " + discount_str() << " off, from " << price_str() << ")" << std::endl;
            return ss.str();
        }

        std::string product_abstract::detail() const
        {
            std::stringstream ss;
            ss << "title:     " << title << std::endl;
            ss << "ori price: " << price << std::endl;
            ss << "special:   " << real_price_str() << std::endl;
            ss << "id:        " << id << std::endl;
            ss << "seller id: " << uid << std::endl;
            ss << "discount:  " << discount_str() << " off" << std::endl;
            ss << "total:     " << total_amount << std::endl;
            ss << "available: " << available_amount << std::endl;
            ss << "type:      " << type << std::endl;
            ss << "desc:      " << description << std::endl;
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