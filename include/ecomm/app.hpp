/**
 * @file app.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-20
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */
#pragma once
#include <string>
#include <ecomm/app_conf.hpp>
#include <ecomm/ioc_container.hpp>
#include <ecomm/intepreter.hpp>

namespace ecomm
{
    class app
    {
    private:
        app_conf *_config;
        ioc_container *_iocc;
        intepreter *_intepreter;

    public:
        app() = default;
        void init();
        void run();
        void welcome();
        void config(std::string path);
        app_conf *config();
        ioc_container *iocc();
    };
}