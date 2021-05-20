#include <ecomm/handler/register_handler.hpp>

#include <regex>

namespace ecomm
{
    namespace handler
    {
        register_handler::register_handler(ecomm::ioc_container *const iocc) : base_handler(iocc)
        {
            this->_user_service = iocc->resolve<service::user_service>("user_service");

            this->_callback = std::bind(&register_handler::handle, this, std::placeholders::_1);
        }

        void register_handler::handle(std::vector<std::string> args)
        {

            if (args.size() != 2)
            {
                printf("Invalid arguments. Usage:\n");
                printf("\tregister USERNAME PASSWORD\n");
                return;
            }
            std::string username = args[0];
            std::string password = args[1];

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
            if(password.size() < 8){
                printf("Invalid password. Too simple. Expecting >= 8 chars.\n");
                return;
            }
            this->_user_service->sign_up(username, password);
        }
        std::string register_handler::help() const
        {
            auto help_text = "{cmd}:\n"
                             "\t{cmd} USERNAME PASSWORD\t register user with username=USERNAME and password=PASSWORD\n";
            return help_text;
        }
        std::string register_handler::desc() const
        {
            return "Sign up a user account.";
        }
    }
}