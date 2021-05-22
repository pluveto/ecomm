/**
 * @file product_service.hpp
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

namespace ecomm
{
    namespace service
    {
        class product_service : public base_service
        {
        public:
            product_service(ecomm::ioc_container *const iocc);
        };

    }
}