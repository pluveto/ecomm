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

namespace ecomm
{
    namespace model
    {
        class user_abstract
        {
        public:
            size_t id;
            double balance;
            std::string username;
            std::string password;
            std::string role;
            std::string _ext_props;
            virtual ~user_abstract() = default;
            virtual std::string type() = 0;
            virtual std::string to_ext_props() = 0;
            virtual void from_ext_props(std::string ext_props) = 0;
        };

    }
}