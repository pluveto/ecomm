#include <ecomm/handler/exit_handler.hpp>

#include <ecomm/intepreter.hpp>

#include <regex>

namespace ecomm
{
    namespace handler
    {
        exit_handler::exit_handler(ecomm::ioc_container *const iocc) : base_handler(iocc)
        {
            this->_callback = std::bind(&exit_handler::handle, this, std::placeholders::_1);
        }

        void exit_handler::handle(std::vector<std::string> args)
        {
            auto i = this->_iocc->resolve<intepreter>("intepreter");
            i->exit_flag(1);
            exit(1);
        }

        std::string exit_handler::desc() const
        {
            return "Exit this application.";
        }
    }
}