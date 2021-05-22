#include <ecomm/handler/passwd_handler.hpp>

#include <regex>

namespace ecomm
{
    namespace handler
    {
        passwd_handler::passwd_handler(ecomm::ioc_container *const iocc) : base_handler(iocc)
        {
            this->_user_service = iocc->resolve<service::user_service>("user_service");
            this->_callback = std::bind(&passwd_handler::handle, this, std::placeholders::_1);
        }

        void passwd_handler::handle(std::vector<std::string> args)
        {
            if (args.size() != 1)
            {
                printf("Type `help %s` for details.\n", args[0].c_str());
                return;
            }
            auto current_user = this->_user_service->current_user();
            if (nullptr == current_user)
            {
                printf("You're expected to have logged in.\n");
                return;
            }
            std::string new_password;
            std::cout << "Input new password:" << std::endl;
            std::getline(std::cin, new_password);
            if (!std::regex_match(new_password, std::regex("^[0-z]+$")))
            {
                printf("Invalid password. Allowed chars: 0-9, a-Z\n");
                return;
            }
            if (new_password.size() < 8)
            {
                printf("Invalid password. Too simple. Expecting >= 8 chars.\n");
                return;
            }
            spdlog::info("new password is {}", new_password);
            auto hashed_password = this->_user_service->hash_password(new_password);
            current_user->password = hashed_password;
            this->_user_service->save(current_user);
        }

        std::string passwd_handler::desc() const
        {
            return "Change password.";
        }
    }
}