/**
 * @file storage_service.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-20
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */

#pragma once

#include <ecomm/service/base_service.hpp>
#include <sqlite3.h>
#include <sqlite_modern_cpp.h>

namespace ecomm
{
    namespace service
    {
        using namespace sqlite;

        class storage_service : public base_service
        {
            database *_storage;

        public:
            storage_service(ecomm::ioc_container *const iocc);
            /*             storage_service(ecomm::ioc_container *const iocc, storage_t *storage);
 */
            database *storage();
        };

    }
}