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
    void intepreter::init()
    {
        spdlog::debug("intepreter :: init()");
        if (nullptr == this->_iocc)
        {
            spdlog::error("null iocc");
        }
        this->_cmd_handlers = new ioc_container();
        this->_iocc->bind<ioc_container>("command_handlers", this->_cmd_handlers);

        auto cmd_router = new command_router(this->_iocc);
        this->_iocc->bind<command_router>("command_router", cmd_router);
        cmd_router->init();
    }
    void intepreter::relp()
    {
        for (;;)
        {
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
            return false;
        }
        return true;
    }

    void intepreter::parse_execute_statement(std::string raw)
    {
        std::vector<std::string> tokens = ecomm::util::str_split(raw, " ");
        if (tokens.size() == 0)
        {
            // printf("Empty command.\n");
            return;
        }
        for (int i = 0; i < tokens.size(); i++)
        {
            util::str_trim(tokens[i]);
        }

        std::string operation = tokens[0];
        auto handler = _cmd_handlers->resolve<handler::base_handler>(operation);
        if (handler == nullptr)
        {
            printf("Unknown command: %s\n", operation.c_str());
            // ecomm::util::print_map_key(_handlers);
            return;
        }
        auto args = std::vector<std::string>(tokens.begin() + 1, tokens.end());
        handler->call(args);
        return;
    }
    ioc_container *intepreter::handlers()
    {
        return this->_cmd_handlers;
    }

} // namespace ecomm
