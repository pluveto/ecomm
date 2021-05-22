#include <ecomm/handler/register_handler.hpp>
#include <ecomm/util.hpp>
#include <regex>
#include <vector>
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
            
            if (this->_user_service->has_login())
            {
                printf("You've logged in.\n");
                return;
            }

            if (args.size() != 4)
            {
                printf("Invalid arguments, number of args unexpected.\n");
                return;
            }
            std::string type_num = args[1];
            std::string username = args[2];
            std::string password = args[3];

            if (!util::in_array(type_num, {"1", "2"}))
            {
                printf("Invalid user type %s. Allowed type: 1 for customer, 2 for business.\n", type_num.c_str());
                return;
            }

            if (!std::regex_match(username, std::regex("^[A-Za-z_]+[0-9A-Za-z.@_]*$")))
            {
                printf("Invalid username. Allowed chars: 0-9, a-Z, `@`, `.` and start with letters.\n");
                return;
            }
            if (!std::regex_match(password, std::regex("^[0-z]+$")))
            {
                printf("Invalid password. Allowed chars: 0-9, a-Z\n");
                return;
            }
            if (password.size() < 8)
            {
                printf("Invalid password. Too simple. Expecting >= 8 chars.\n");
                return;
            }
            auto existing_user = this->_user_service->get_by(u"username", username);
            if (nullptr != existing_user)
            {
                printf("Invalid username. Duplicated.\n");
                spdlog::error("duplicated with user {}.", existing_user->id);
                return;
            }
            delete existing_user;
            auto user_type = std::vector<std::string>{"admin", "customer", "business"}[std::stoi(type_num)];
            auto user = this->_user_service->sign_up(user_type, username, password);
            if (user == nullptr)
            {
                printf("Failed to register!\n");
            }
        }
        std::string register_handler::help() const
        {
            auto help_text = "-- register --\n"
                             "  {cmd} TYPE USERNAME PASSWORD\n"
                             "      Register a user\n"
                             "  Available TYPE: \n"
                             "      1. customer. \n"
                             "      2. business. \n"
                             "  Example: \n"
                             "  {cmd} 1 pluveto dfpdsgXC2gfh\n";

            return help_text;
        }
        std::string register_handler::desc() const
        {
            return "Sign up a user account.";
        }
    }
}