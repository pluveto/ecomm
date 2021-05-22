/**
 * @file base_service.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-19
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

#include <ecomm/ioc_container.hpp>

namespace ecomm
{
    namespace service
    {
        class base_service
        {
        protected:
            ioc_container *_iocc;

        public:
            base_service(ecomm::ioc_container *const iocc);
        };
    }

}