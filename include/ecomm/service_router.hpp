/**
 * @file service_router.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief Add services to app ioc container
 * @version 0.1
 * @date 2021-05-23
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */

#pragma once

#include <unordered_map>

#include <ecomm/ioc_container.hpp>

namespace ecomm
{
    class service_router
    {
    private:
        ioc_container *_iocc;

    public:
        service_router(ioc_container *const iocc);

        /**
         * @brief Initialize service router
         * 
         */
        void init();
        ~service_router() = default;
    };

} // namespace ecomm
