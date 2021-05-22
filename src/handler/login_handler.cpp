#include <ecomm/handler/login_handler.hpp>

#include <regex>

namespace ecomm
{
    namespace handler
    {
        login_handler::login_handler(ecomm::ioc_container *const iocc) : base_handler(iocc)
        {
            this->_user_service = iocc->resolve<service::user_service>("user_service");

            this->_callback = std::bind(&login_handler::handle, this, std::placeholders::_1);
        }

        void login_handler::handle(std::vector<std::string> args)
        {
            if (this->_user_service->has_login())
            {
                printf("You've logged in.\n");
                return;
            }

            if (args.size() != 3)
            {
                printf("Invalid arguments. Usage:\n");
                printf("\t%s USERNAME PASSWORD\n", args[0].c_str());
                return;
            }
            std::string username = args[1];
            std::string password = args[2];

            if (!std::regex_match(username, std::regex("^[0-9A-Za-z.@]+$")))
            {
                printf("Invalid username. Allowed chars: 0-9, a-Z, `@` and `.`\n");
                return;
            }
            if (!std::regex_match(password, std::regex("^[0-z]+$")))
            {
                printf("Invalid password. Allowed chars: 0-9, a-Z\n");
                return;
            }
            auto u = this->_user_service->login(username, password);
            if (nullptr == u)
            {
                printf("Incorrect username or password.\n");
                return;
            }
            this->_iocc->bind("current_user", u);
        }
        std::string login_handler::help() const
        {
            auto help_text = "{cmd}:\n"
                             "  {cmd} USERNAME PASSWORD"
                             "      log in user.\n";
            return help_text;
        }
        std::string login_handler::desc() const
        {
            return "Sign in a user account.";
        }
    }
}