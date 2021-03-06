/**
 * @file intepreter.cpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-20
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */
#include <spdlog/spdlog.h>

#include <ecomm/util.hpp>
#include <ecomm/intepreter.hpp>
#include <ecomm/command_router.hpp>

namespace ecomm
{

    intepreter::intepreter(ioc_container *const iocc)
    {
        this->_iocc = iocc;
    }

    intepreter::~intepreter()
    {
        delete this->_cmd_handlers;
        delete this->_cmd_router;
    }

    void intepreter::init()
    {
        spdlog::debug("intepreter :: init()");
        if (nullptr == this->_iocc)
        {
            spdlog::error("null iocc");
        }
        /*
         * Release in intepreter::~intepreter()
         */
        this->_cmd_handlers = new ioc_container();
        this->_iocc->bind<ioc_container>("command_handlers", this->_cmd_handlers);

        /*
         * Release in intepreter::~intepreter()
         */
        auto cmd_router = new command_router(this->_iocc);
        this->_iocc->bind<command_router>("command_router", cmd_router);

        this->_cmd_router = cmd_router;
        this->_cmd_router->init();

        this->exit_flag(false);
    }
    void intepreter::repl()
    {
        for (;;)
        {            
            if (this->exit_flag())
            {
                break;
            }
            this->print_prompt();
            if (!this->read_input())
            {
                printf("Bad input!\n");
                continue;
            }
            this->parse_execute_statement(this->_input_buffer);
        }
    }
    void intepreter::print_prompt()
    {
        printf("> ");
    }

    bool intepreter::read_input()
    {
        std::getline(std::cin, this->_input_buffer);
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
        return true;
    }

    void intepreter::parse_execute_statement(std::string raw)
    {
        std::vector<std::string> tokens = ecomm::util::str_split(raw, " ");
        if (tokens.size() == 0)
        {
            printf("Empty command.\n");
            return;
        }
        for (int i = 0; i < tokens.size(); i++)
        {
            util::str_trim(tokens[i]);
        }

        std::string cmd = tokens[0];
        auto handler = _cmd_handlers->resolve<handler::base_handler>(cmd);
        if (handler == nullptr)
        {
            printf("Unknown command: %s\n", cmd.c_str());
            // ecomm::util::print_map_key(_handlers);
            return;
        }
        if (!handler->available())
        {
            printf("Disabled command.\n");
            // ecomm::util::print_map_key(_handlers);
            return;
        }
        //auto args = std::vector<std::string>(tokens.begin() + 1, tokens.end());
        handler->call(tokens);
        return;
    }
    ioc_container *intepreter::handlers()
    {
        return this->_cmd_handlers;
    }

    bool intepreter::exit_flag()
    {
        return this->_exit_flag;
    }

    void intepreter::exit_flag(bool val)
    {
        this->_exit_flag = val;
    }
    

} // namespace ecomm
