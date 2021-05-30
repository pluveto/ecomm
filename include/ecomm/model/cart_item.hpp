/**
 * @file cart_item.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-30
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
        class cart_item
        {
        public:
            size_t id;
            std::string title;
            size_t uid;
            size_t pid;
            size_t amount;
            // read only
            double price;
        };

    }
}