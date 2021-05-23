/**
 * @file balance_handler.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-20
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */

#pragma once

#include <ecomm/handler/base_handler.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <ecomm/service/user_service.hpp>

namespace ecomm
{
    namespace handler
    {

        class balance_handler : public base_handler
        {
        private:
            service::user_service *_user_service;

        public:
            balance_handler(ecomm::ioc_container *const iocc);
            void handle(std::vector<std::string> args);
            std::string help() const;
            std::string desc() const;
        };
        

    }
}