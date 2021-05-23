/**
 * @file command_router.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief Map command to handlers
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
    class command_router
    {
    private:
        ioc_container *_iocc;

    public:
        command_router(ioc_container *const iocc);
        /**
         * @brief Map handler
         * 
         */
        void init();
        ~command_router();
    };

} // namespace ecomm
