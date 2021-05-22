#include <ecomm/handler/base_handler.hpp>

namespace ecomm
{
    namespace handler
    {
        base_handler::base_handler(ecomm::ioc_container *const iocc)
        {
            this->_iocc = iocc;
        }
        void base_handler::call(std::vector<std::string> args)
        {
            _callback(args);
        }
        std::string base_handler::help() const
        {
            auto help_text = "{cmd}:\n"
                             "\tNot provided yet.\n";
            return help_text;
        }
        std::string base_handler::desc() const
        {
            return "Not provided yet.";
        }

        
        bool base_handler::available() const
        {
            return true;
        }
    }
}