/**
 * @file app.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief Application class
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
#include <ecomm/service_router.hpp>

namespace ecomm
{
    class app
    {
    private:
        app_conf *_config;
        ioc_container *_iocc;
        intepreter *_intepreter;
        service_router * _service_router;

    public:
        app() = default;
        ~app();
        /**
         * @brief Initialize application (Read config, set up ioc container...)
         * 
         */
        void init();
        /**
         * @brief Run application
         * 
         */
        void run();
        /**
         * @brief Print application welcome message.
         * 
         */
        void welcome();
        /**
         * @brief Read configuration and apply to application
         * 
         * @param path 
         */
        void config(std::string path);
        /**
         * @brief Get application config
         * 
         * @return app_conf* 
         */
        app_conf *config();
        /**
         * @brief Get application ioc container
         * 
         * @return ioc_container* 
         */
        ioc_container *iocc();
    };
}