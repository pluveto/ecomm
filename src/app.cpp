/**
 * @file app.cpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-20
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */
#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

#include <ecomm/app.hpp>
#include <ecomm/service_router.hpp>

namespace ecomm
{
    void app::init()
    {
        spdlog::debug("init");
        spdlog::cfg::load_env_levels();

        this->_iocc = new ioc_container();

        // Init service router
        auto o_service_router = new service_router(this->_iocc);
        o_service_router->init();

        // Init intepreter (with command router)

        this->_intepreter = new intepreter(this->_iocc);

        this->_iocc->bind<intepreter>("intepreter", this->_intepreter);

        this->_intepreter->init();
        //ecomm::statement::statement_register::applyTo(this);
        //ecomm::service::service_register::applyTo(this);
    }

    void app::run()
    {
        spdlog::debug("run");
        this->welcome();
        this->_intepreter->relp();
    }

    void app::welcome()
    {
        spdlog::debug("welcome");
        std::cout << this->_config->motd();
    }
    void app::config(std::string path)
    {
        spdlog::debug("config");
        std::ifstream i(path);
        nlohmann::json j;
        i >> j;
        auto conf = new ecomm::app_conf();
        ecomm::app_conf::from_json(j, *conf);
        this->_config = conf;
    }
    app_conf *app::config()
    {
        return this->_config;
    }

    ioc_container *app::iocc()
    {
        return this->_iocc;
    }

}