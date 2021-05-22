/**
 * @file product_handler.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-22
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */

#include <ecomm/handler/base_handler.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

namespace ecomm
{
    namespace handler
    {

        class product_handler : public base_handler
        {
        public:
            product_handler(ecomm::ioc_container *const iocc);
            void handle(std::vector<std::string> args);
            std::string desc() const;
        };

    }
}