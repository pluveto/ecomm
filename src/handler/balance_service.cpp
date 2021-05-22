#include <ecomm/handler/product_handler.hpp>

#include <regex>

namespace ecomm
{
    namespace handler
    {
        product_handler::product_handler(ecomm::ioc_container *const iocc) : base_handler(iocc)
        {
            this->_callback = std::bind(&product_handler::handle, this, std::placeholders::_1);
        }

        void product_handler::handle(std::vector<std::string> args)
        {
          if(args.size() == 1){
              printf("Type `help %s` for details.\n", args[0].c_str());
              return;
          }
        }

        std::string product_handler::desc() const
        {
            return "Product commands.";
        }
    }
}