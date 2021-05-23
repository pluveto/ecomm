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

#pragma once

#include <ecomm/handler/base_handler.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

#include <ecomm/model/user_abstract.hpp>
#include <ecomm/service/product_service.hpp>

namespace ecomm
{
    namespace handler
    {

        class product_handler : public base_handler
        {
        private:
            model::user_abstract *_current_user;
            service::product_service *_product_service;

        public:
            product_handler(ecomm::ioc_container *const iocc);
            void handle(std::vector<std::string> args);
            void handle_add(std::vector<std::string> &args);
            void handle_view(std::vector<std::string> &args);
            void handle_edit(std::vector<std::string> &args);
            void handle_remove(std::vector<std::string> &args);
            void handle_list(std::vector<std::string> &args);
            void handle_search(std::vector<std::string> &args);
            void handle_discount(std::vector<std::string> &args);
            std::string desc() const;
            std::string help() const;
        };
    }
}