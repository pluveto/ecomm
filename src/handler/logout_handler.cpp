#include <ecomm/handler/logout_handler.hpp>

#include <regex>

namespace ecomm
{
    namespace handler
    {
        logout_handler::logout_handler(ecomm::ioc_container *const iocc) : base_handler(iocc)
        {
            this->_user_service = iocc->resolve<service::user_service>("user_service");

            this->_callback = std::bind(&logout_handler::handle, this, std::placeholders::_1);
        }

        void logout_handler::handle(std::vector<std::string> args)
        {
            if (!this->_user_service->has_login())
            {
                printf("You're not logged in.\n");
                return;
            }
            this->_user_service->logout();
        }
        std::string logout_handler::help() const
        {
            auto help_text = "{cmd}:\n"
                             "  {cmd} USERNAME PASSWORD"
                             "      log in user.\n";
            return help_text;
        }
        std::string logout_handler::desc() const
        {
            return "Sign in a user account.";
        }
    }
}