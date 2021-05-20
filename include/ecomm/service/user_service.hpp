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

#pragma once

#include <ecomm/handler/base_handler.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

#include <ecomm/service/base_service.hpp>
#include <ecomm/service/crypto_service.hpp>
#include <ecomm/model/user_model.hpp>

namespace ecomm
{
    namespace service
    {

        class user_service : public base_service
        {
        private:
            crypto_service *_crypto_service;

        public:
            user_service(ecomm::ioc_container *const iocc);
            model::user_model *login(std::string username, std::string password);
            model::user_model *sign_up(std::string username, std::string password);
            bool save(model::user_model *user);
        };
    }
}