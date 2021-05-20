#include <ecomm/model/user_model.hpp>

#include <cstring>
#include <memory>
#include <ctime>

namespace ecomm
{
    namespace model
    {
        // getters

        uint64_t user_model::id()
        {
            return this->_id;
        }

        std::string user_model::role()
        {
            return this->_role;
        }

        double user_model::balance()
        {
            return this->_balance;
        }

        std::string user_model::username()
        {
            return std::string(this->_username);
        }

        std::string user_model::password()
        {
            return std::string(this->_password);
        }

        uint64_t user_model::created_at()
        {
            return this->_created_at;
        }

        uint64_t user_model::updated_at()
        {
            return this->_updated_at;
        }
        // setters

        void user_model::id(uint64_t id)
        {
            this->_id = id;
        }

        bool user_model::role(std::string role)
        {
            if (role.size() > sizeof(this->_role) - 1)
            {
                return false;
            }
            auto s = role.c_str();
            strcpy(this->_role, s);
            return true;
        }

        void user_model::balance(double balance)
        {
            this->_balance = balance;
        }
        
        bool user_model::username(std::string username)
        {
            if (username.size() > sizeof(this->_username) - 1)
            {
                return false;
            }
            auto s = username.c_str();
            strcpy(this->_username, s);
            return true;
        }

        bool user_model::password(std::string password)
        {
            if (password.size() > sizeof(this->_password) - 1)
            {
                return false;
            }
            auto s = password.c_str();
            strcpy(this->_password, s);
            return true;
        }

        void user_model::created()
        {
            this->_created_at = std::time(nullptr);
        }

        void user_model::updated()
        {
            this->_updated_at = std::time(nullptr);
        }

    }
}