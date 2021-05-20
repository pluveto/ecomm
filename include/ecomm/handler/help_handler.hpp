/**
 * @file login_handler.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-19
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

        class help_handler : public base_handler
        {
        public:
            help_handler(ecomm::ioc_container *const iocc);
            std::string desc() const;
            void print_commands() const;
            void print_command_help(std::string cmd_name) const;
        };

    }
}