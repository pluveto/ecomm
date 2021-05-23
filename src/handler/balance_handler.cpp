/**
 * @file balance_handler.cpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-22
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */
#include <ecomm/handler/balance_handler.hpp>
#include <ecomm/util.hpp>
#include <regex>

namespace ecomm
{
    namespace handler
    {
        balance_handler::balance_handler(ecomm::ioc_container *const iocc) : base_handler(iocc)
        {
            this->_user_service = iocc->resolve<service::user_service>("user_service");

            this->_callback = std::bind(&balance_handler::handle, this, std::placeholders::_1);
        }

        void balance_handler::handle(std::vector<std::string> args)
        {
            auto current_user = this->_user_service->current_user();

            if (nullptr == current_user)
            {
                printf("You're expected to have logged in.\n");
                return;
            }
            if (args.size() == 1)
            {
                printf("User:    %s\n", current_user->username.c_str());
                printf("Balance: %.2f\n", current_user->balance);
                return;
            }
            if (args.size() == 2 && args[1] == "recharge")
            {
                printf("What amount of money to recharge: ");
                double amount;
                int max_try = 3;
                int current_try = 0;
                if (!util::expect_number_max_try(amount, 0.01, 10000.00, 3, "Input amount: "))
                {
                    return;
                }
                if(!this->_user_service->recharge(current_user, amount)){
                    printf("Failed to recharge.\n");
                    return;
                }
                return;
            }
            printf("Invalid command, type `help %s` for helping.\n", args[0].c_str());
            return;
        }

        std::string balance_handler::desc() const
        {
            return "Balance query & recharge.";
        }

        std::string balance_handler::help() const
        {
            auto help_text = "-- balance --\n"
                             "  {cmd}"
                             "      View current balance\n"
                             "  {cmd} recharge \n"
                             "      Charge money into your account."
                             "      Example: \n"
                             "    > {cmd} recharge\n"
                             "      (and then input amount)100.00\n";
            return help_text;
        }
    }
}