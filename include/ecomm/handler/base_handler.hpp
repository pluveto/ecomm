/**
 * @file base_handler.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-19
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

#include <ecomm/ioc_container.hpp>

typedef std::function<void(std::vector<std::string>)> statement_callback;

namespace ecomm
{
    namespace handler
    {
        class base_handler
        {
        protected:
            statement_callback _callback;
            ioc_container *_iocc;

        public:
            base_handler(ecomm::ioc_container * const iocc);
            void call(std::vector<std::string> args);
            virtual std::string help() const;
            virtual std::string desc() const;
            virtual bool available() const;
        };
        
    }

}