/**
 * @file user_abstract.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-23
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */

#pragma once

#include <string>
#include <cstdint>

#include <ecomm/model/user_abstract.hpp>

namespace ecomm
{
    namespace model
    {
        class business_user : public user_abstract
        {
        public:
            size_t id;
            double balance;
            std::string username;
            std::string password;
            std::string role;
            std::string _ext_props;

            std::string type() { return this->role; }
            std::string to_ext_props() { return ""; }
            void from_ext_props(std::string ext_props) {}
        };

    }
}