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
/* #include <ecomm/model/customer_user_model.hpp>
#include <ecomm/model/business_user_model.hpp>
#include <ecomm/model/admin_user_model.hpp> */

#include <spdlog/spdlog.h>
#include <wchar.h>
#include <stdio.h>

namespace ecomm
{
    namespace service
    {
        user_service::user_service(ecomm::ioc_container *const iocc) : base_service(iocc)
        {
            this->_crypto_service = iocc->resolve<crypto_service>("crypto_service");
            this->_storage_service = iocc->resolve<storage_service>("storage_service");
        }

        model::user_abstract *user_service::login(std::string username, std::string password)
        {
            spdlog::debug("try login with {}:{}", username, password);
            auto hashed_password = this->hash_password(password);
            auto user = this->get_by(u"username", username);
            if (nullptr == user)
            {
                spdlog::debug("No such user: {}", username);

                return nullptr;
            }
            if (hashed_password != user->password)
            {
                spdlog::debug("hashed password: {}, expected {}", hashed_password, user->password);
                return nullptr;
            }
            return user;
        }

        model::user_abstract *user_service::build(std::string user_type)
        {
            model::user_abstract *u;
            if (user_type == "customer")
            {
                u = new model::customer_user;
            }else
            if (user_type == "business")
            {
                u = new model::business_user;
            }else{
                throw "Unexpected user type.";
            }
            u->role = user_type;
            return u;
        }

        std::string user_service::hash_password(std::string password)
        {
            auto sault = "!R#@f32fdsffds";
            auto hashed_password = this->_crypto_service->md5(password, sault);
            return hashed_password;
        }

        model::user_abstract *user_service::sign_up(std::string user_type, std::string username, std::string password)
        {
            auto hashed_password = this->hash_password(password);
            spdlog::debug("try sign_up with {}:{}", username, password);
            spdlog::debug("hashed password: {}", hashed_password);
            auto user = user_service::build(user_type);

            user->balance = 0;
            user->username = username;
            user->password = hashed_password;

            this->save(user);
            return user;
        }
        bool user_service::save(model::user_abstract *u)
        {
            auto db = this->_storage_service->storage();
            if (u->id > 0)
            {
                *db << u"update users "
                       "set username = ?, password = ?, balance = ?, role = ?"
                       "where id = ?"
                    << u->username
                    << u->password
                    << u->balance
                    << u->role

                    << u->id;
            }
            else
            {
                *db << u"insert into users (username, password, balance, role) values (?, ?, ?, ?);"
                    << u->username
                    << u->password
                    << u->balance
                    << u->role;

                u->id = db->last_insert_rowid();
            }
            spdlog::debug("user {} is saved.", u->username);
            return true;
        }

        bool user_service::recharge(model::user_abstract *user, double amount)
        {
            if (amount < 0)
            {
                return false;
            }
            user->balance += amount;
            return this->save(user);
        }

        bool user_service::pay(model::user_abstract *user, double amount)
        {
            if (amount < 0)
            {
                return false;
            }
            if (user->balance - amount < 0)
            {
                return false;
            }
            user->balance -= amount;
            return this->save(user);
        }

        model::user_abstract *user_service::get_by(std::u16string key, std::string val)
        {

            auto db = this->_storage_service->storage();
            model::user_abstract *u = nullptr;
            auto s = u"select id, balance, username, password, role from users "
                     "where ";
            std::u16string sql(s);
            sql += key;
            sql += std::u16string(u" = ?");

            try
            {
                *db << sql
                    << val >>
                    [&](size_t id, double balance, std::string username, std::string password, std::string role) {
                        u = this->build(role);
                        u->id = id;
                        u->balance = balance;
                        u->username = username;
                        u->password = password;
                    };
            }
            catch (sqlite_exception &e)
            {
                std::cerr << e.get_code() << ": " << e.what() << " during "
                          << e.get_sql() << std::endl;
            }

            return u;
        }

        void user_service::logout()
        {
            this->_iocc->unbind<model::user_abstract>("current_user");
        }
        model::user_abstract *user_service::current_user()
        {
            return this->_iocc->resolve<model::user_abstract>("current_user");
        }

        bool user_service::has_login()
        {
            return nullptr != this->_iocc->resolve<model::user_abstract>("current_user");
        }
    }
}