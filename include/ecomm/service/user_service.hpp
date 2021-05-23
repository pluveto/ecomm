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

#include <ecomm/model/user_abstract.hpp>
#include <ecomm/model/customer_user.hpp>
#include <ecomm/model/business_user.hpp>
#include <ecomm/service/base_service.hpp>
#include <ecomm/service/crypto_service.hpp>
#include <ecomm/service/storage_service.hpp>

namespace ecomm
{
    namespace service
    {

        class user_service : public base_service
        {
        private:
            crypto_service *_crypto_service;
            storage_service *_storage_service;

        public:
            user_service(ecomm::ioc_container *const iocc);
            model::user_abstract *login(std::string username, std::string password);
            void logout();
            model::user_abstract *get_by(std::u16string key, std::string val);
            model::user_abstract *sign_up(std::string user_type, std::string username, std::string password);
            model::user_abstract *current_user();
            std::string hash_password(std::string password);
            bool save(model::user_abstract *user);
            bool recharge(model::user_abstract *user, double amount);
            bool pay(model::user_abstract *user, double amount);
            bool has_login();
            static model::user_abstract *build(std::string user_type);
        };
    }
}