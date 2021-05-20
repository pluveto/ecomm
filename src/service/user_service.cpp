/**
 * @file user_service.cpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-20
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */
#include <ecomm/service/user_service.hpp>

#include <spdlog/spdlog.h>

namespace ecomm
{
    namespace service
    {
        user_service::user_service(ecomm::ioc_container *const iocc) : base_service(iocc)
        {
            this->_crypto_service = iocc->resolve<crypto_service>("crypto_service");
        }

        model::user_model *user_service::login(std::string username, std::string password)
        {
            spdlog::debug("try login with {}:{}", username, password);
            auto user = new model::user_model;
            user->updated();

            return user;
        }
        model::user_model *user_service::sign_up(std::string username, std::string password)
        {
            auto sault = "!R#@f32fdsffds";
            auto hashed_password = this->_crypto_service->md5(password, sault);
            spdlog::debug("try sign_up with {}:{}", username, password);
            spdlog::debug("hashed password: {}", hashed_password);
            auto user = new model::user_model;

            user->created();
            user->updated();
            user->role("user");
            user->balance(0);
            user->username(username);
            user->password(hashed_password);

            if (this->save(user))
            {
                return user;
            }
            return nullptr;
        }
        bool user_service::save(model::user_model *user)
        {
            spdlog::debug("user {} is saved.", user->username());
            return true;
        }
    }
}