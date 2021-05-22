#include <ecomm/handler/help_handler.hpp>

#include <regex>

namespace ecomm
{
    namespace handler
    {
        help_handler::help_handler(ecomm::ioc_container *const iocc) : base_handler(iocc)
        {
            this->_callback = [this](std::vector<std::string> args) {
                if (args.size() == 1)
                {
                    this->print_commands();
                    return;
                }
                if (args.size() == 2)
                {
                    this->print_command_help(args[1]);
                    return;
                }
                printf("Invalid input.\n");
                printf("Type `help` for command list, type`help CMD_NAME` for details of specific command.\n");
            };
        }
        std::string help_handler::desc() const
        {
            return "Show help text.";
        }

        void help_handler::print_commands() const
        {
            auto iocc = this->_iocc;
            auto command_handlers = iocc->resolve<ioc_container>("command_handlers");

            command_handlers->foreach<base_handler *>([](std::string cmd_name, base_handler *handler) -> bool {
                auto desc = std::regex_replace(handler->desc(), std::regex("\\{cmd\\}"), cmd_name);
                printf("\033[36m%8s\033[0m - %s\n", cmd_name.c_str(), desc.c_str());
                return true;
            });
            printf("For details, visit: https://www.less-bug.com/posts/e_comm/\n");
        }
        void help_handler::print_command_help(std::string cmd_name) const
        {
            auto iocc = this->_iocc;
            auto command_handlers = iocc->resolve<ioc_container>("command_handlers");

            auto handler = command_handlers->resolve<base_handler>(cmd_name);
            if (nullptr == handler)
            {
                printf("Unknown command: %s\n", cmd_name.c_str());
                return;
            }
            auto help = std::regex_replace(handler->help(), std::regex("\\{cmd\\}"), cmd_name);
            printf("%s\n", help.c_str());
        }
    }
}