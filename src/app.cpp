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

        /*
        * Released in app::~app()
        */
        this->_iocc = new ioc_container();

        // Init service router
        /*
        * Released in app::~app()
        */
        this->_service_router = new service_router(this->_iocc);
        this->_service_router->init();

        // Init intepreter (with command router)
        /*
        * Released in app::~app()
        */
        this->_intepreter = new intepreter(this->_iocc);

        this->_iocc->bind<intepreter>("intepreter", this->_intepreter);

        this->_intepreter->init();
    }

    void app::run()
    {
        spdlog::debug("run");
        this->welcome();
        this->_intepreter->repl();
    }

    void app::welcome()
    {
        spdlog::debug("welcome");
        std::cout << this->_config->motd();
    }

    void app::config(std::string path)
    {
        spdlog::debug("config");
        try
        {
            std::ifstream i(path);
            nlohmann::json j;
            i >> j;
            auto conf = new ecomm::app_conf();
            ecomm::app_conf::from_json(j, *conf);
            this->_config = conf;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Failed to start: " << e.what() << '\n';
            std::cerr << "Please read the documents and start it correctly.";
            exit(1);
        }
    }
    app_conf *app::config()
    {
        return this->_config;
    }

    ioc_container *app::iocc()
    {
        return this->_iocc;
    }

    app::~app()
    {
        delete this->_intepreter;
        delete this->_service_router;
        delete this->_config;
        delete this->_iocc;
    }
}