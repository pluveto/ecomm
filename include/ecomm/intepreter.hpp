#include <ecomm/ioc_container.hpp>
#include <ecomm/handler/base_handler.hpp>

namespace ecomm
{
    class intepreter
    {
    private:
        ioc_container *_iocc;
        std::string _input_buffer;
        ioc_container *_cmd_handlers;

        void print_prompt();
        bool read_input();
        void parse_execute_statement(std::string raw);

    public:
        intepreter(ioc_container *const iocc);

        void init();
        void relp();
        ioc_container *handlers();

        ~intepreter() = default;
    };

} // namespace ecomm
