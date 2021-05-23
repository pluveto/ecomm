/**
 * @file intepreter.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief User interactiviation intepreter class
 * @version 0.1
 * @date 2021-05-23
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */

#pragma once

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

        /**
         * @brief Print prompt to console
         * 
         */
        void print_prompt();
        /**
         * @brief Read from user input
         * 
         * @return true string successfuly read
         * @return false failed on cin
         */
        bool read_input();

        /**
         * @brief Parse line which is input by user to statement and execute it
         * 
         * @param raw raw user input
         */
        void parse_execute_statement(std::string raw);

    public:
        intepreter(ioc_container *const iocc);

        /**
         * @brief Initialize intepreter
         * 
         */
        void init();

        /**
         * @brief Start read-eval-print-loop
         * 
         */
        void repl();

        /**
         * @brief Get container for command handlers
         * 
         * @return ioc_container* 
         */
        ioc_container *handlers();

        ~intepreter() = default;
    };

} // namespace ecomm
