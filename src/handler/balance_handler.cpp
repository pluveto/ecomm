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
            if (args.size() == 2 && args[1] == "charge")
            {
                printf("What amount of money to charge?\n");
                double amount;
                std::cin >> amount;
                if (std::cin.fail())
                {
                    printf("Invalid input, expecting number.\n");
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    return;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (amount <= 0 || amount > 10000.0)
                {
                    printf("Invalid number input, not in range 0 < x <= 10000.\n");
                    return;
                }
                current_user->balance += amount;
                this->_user_service->save(current_user);
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
                             "  {cmd} charge \n"
                             "      Charge money into your account."
                             "      Example: \n"
                             "    > {cmd} charge\n"
                             "      (and then input amount)100.00\n";
            return help_text;
        }
    }
}