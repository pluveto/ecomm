/**
 * @file service_router.cpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-20
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */

#include <ecomm/service_router.hpp>
#include <spdlog/spdlog.h>
#include <ecomm/intepreter.hpp>
#include <ecomm/handler/help_handler.hpp>
#include <ecomm/service/storage_service.hpp>
#include <ecomm/service/crypto_service.hpp>
#include <ecomm/service/user_service.hpp>
#include <ecomm/service/product_service.hpp>
#include <ecomm/service/cart_service.hpp>

namespace ecomm
{
    service_router::service_router(ioc_container *const iocc)
    {
        spdlog::debug("service_router::service_router(iocc)");
        iocc->bind<service_router>("service_router", this);
        this->_iocc = iocc;
    }
    void service_router::init()
    {
        using namespace ecomm::service;
        auto iocc = this->_iocc;

        spdlog::debug("service_router::init()");

        /**
         * Released in service_router::~service_router()
         * 
         */
        iocc->bind<storage_service>("storage_service", new storage_service(iocc));
        iocc->bind<crypto_service>("crypto_service", new crypto_service(iocc));
        iocc->bind<user_service>("user_service", new user_service(iocc));
        iocc->bind<product_service>("product_service", new product_service(iocc));
        iocc->bind<cart_service>("cart_service", new cart_service(iocc));
    }

    service_router::~service_router()
    {
        using namespace ecomm::service;
        auto iocc = this->_iocc;

        iocc->unbind<storage_service>("storage_service", true);
        iocc->unbind<crypto_service>("crypto_service", true);
        iocc->unbind<user_service>("user_service", true);
        iocc->unbind<product_service>("product_service", true);
        iocc->unbind<cart_service>("cart_service", true);
    }
} // namespace ecomm
