/**
 * @file cart_handler.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-29
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

#include <ecomm/service/user_service.hpp>
#include <ecomm/service/product_service.hpp>
#include <ecomm/service/cart_service.hpp>

namespace ecomm
{
    namespace handler
    {

        class cart_handler : public base_handler
        {
        private:
            service::user_service *_user_service;
            service::product_service *_product_service;
            service::cart_service * _cart_service;

            model::user_abstract * _current_user;

        public:
            cart_handler(ecomm::ioc_container *const iocc);
            void handle(std::vector<std::string> args);
            void handle_view();
            void handle_add(model::product_abstract* prod, size_t amount);
            void handle_remove(model::product_abstract* prod, size_t amount);
            void handle_set(model::product_abstract* prod, size_t amount);
            std::string help() const;
            std::string desc() const;
        };
        

    }
}