/**
 * @file ioc_container.cpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-20
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */

// G++ 的模板函数不支持分离编译，所以带有泛型的函数已经定义在同名的头文件中。
#include <ecomm/ioc_container.hpp>

namespace ecomm
{
    bool ioc_container::unbind(std::string name, bool free)
    {
        auto o = this->resolve<void>(name);
        spdlog::debug("unbind {}: {}", name, o != nullptr);
        if (nullptr == o)
        {
            return false;
        }
        if (free)
        {
            delete o;
        }
        this->_container.erase(name);
        return true;
    }
}