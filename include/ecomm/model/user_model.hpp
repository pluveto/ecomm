#pragma once

#include <stdio.h>
#include <stdint.h>
#include <string>

namespace ecomm
{
    namespace model
    {

        class user_model
        {
        private:
            uint64_t _id;
            char _role[8];
            double _balance;
            char _username[32];
            char _password[48];
            uint64_t _created_at;
            uint64_t _updated_at;

        public:
            // getters
            uint64_t id();
            std::string role();
            double balance();
            std::string username();
            std::string password();
            uint64_t created_at();
            uint64_t updated_at();

            //setters
            void id(uint64_t id);
            bool role(std::string role);
            void balance(double balance);
            bool username(std::string username);
            bool password(std::string password);
            void created();
            void updated();
        };
    }
}
