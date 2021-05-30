/**
 * @file command_router.cpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-20
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */

#include <ecomm/command_router.hpp>
#include <spdlog/spdlog.h>
#include <ecomm/intepreter.hpp>
#include <ecomm/handler/help_handler.hpp>
#include <ecomm/handler/login_handler.hpp>
#include <ecomm/handler/register_handler.hpp>
#include <ecomm/handler/exit_handler.hpp>
#include <ecomm/handler/product_handler.hpp>
#include <ecomm/handler/cart_handler.hpp>
#include <ecomm/handler/passwd_handler.hpp>
#include <ecomm/handler/logout_handler.hpp>
#include <ecomm/handler/balance_handler.hpp>
namespace ecomm
{
    command_router::command_router(ioc_container *const iocc)
    {
        spdlog::debug("command_router::command_router(iocc)");
        this->_iocc = iocc;
    }
    void command_router::init()
    {
        using namespace ecomm::handler;
        auto iocc = this->_iocc;
        auto i = iocc->resolve<intepreter>("intepreter");
        spdlog::debug("command_router::init()");
        /*
        * Released in command_router::~command_router()
        */
        i->handlers()->bind<base_handler>("help", new help_handler(iocc));
        i->handlers()->bind<base_handler>("reg", new register_handler(iocc));
        i->handlers()->bind<base_handler>("login", new login_handler(iocc));
        i->handlers()->bind<base_handler>("logout", new logout_handler(iocc));
        i->handlers()->bind<base_handler>("quit", new exit_handler(iocc));
        i->handlers()->bind<base_handler>("passwd", new passwd_handler(iocc));
        i->handlers()->bind<base_handler>("prod", new product_handler(iocc));
        i->handlers()->bind<base_handler>("bal", new balance_handler(iocc));
        i->handlers()->bind<base_handler>("cart", new cart_handler(iocc));
    }

    command_router::~command_router()
    {
    }
} // namespace ecomm
