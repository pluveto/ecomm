/**
 * @file base_service.cpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-20
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */
#include <ecomm/service/base_service.hpp>

namespace ecomm
{
    namespace service
    {
        base_service::base_service(ecomm::ioc_container *const iocc)
        {
            this->_iocc = iocc;
        }
    }
}