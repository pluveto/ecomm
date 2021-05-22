/**
 * @file product_service.cpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-20
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */
#include <ecomm/service/product_service.hpp>

#include <openssl/md5.h>
#include <stdio.h>

namespace ecomm
{
    namespace service
    {
        product_service::product_service(ecomm::ioc_container *const iocc) : base_service(iocc)
        {
        }

    }
}