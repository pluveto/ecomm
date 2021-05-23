/**
 * @file ioc_container.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-19
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */
#pragma once

#include <string>
#include <unordered_map>
#include <spdlog/spdlog.h>

namespace ecomm
{
    class ioc_container
    {
    private:
        std::unordered_map<std::string, void *> _container;

    public:
        ioc_container() = default;

        /**
         * @brief Fetch object from container by name
         * 
         * @tparam T 
         * @param name 
         * @return T* 
         */
        template <typename T>
        T *resolve(std::string name);

        /**
         * @brief Bind object to container by name and object
         * 
         * @tparam T 
         * @param name 
         * @param value 
         * @return true 
         * @return false 
         */
        template <typename T>
        bool bind(std::string name, T *value);

        /**
         * @brief Cancel binding between name and object
         * 
         * @tparam T 
         * @param name 
         * @param free If true, unbind-object will be deleted
         * @return true 
         * @return false 
         */
        template <typename T>
        bool unbind(std::string name, bool free = true);

        /**
         * @brief Execute callback on every object in this container
         * 
         * @tparam T 
         * @param callback 
         */
        template <typename T>
        void foreach (std::function<bool(std::string, T)> callback);
    };

    template <typename T>
    T *ioc_container::resolve(std::string name)
    {
        spdlog::debug("resolving {}", name);
        auto x = this->_container.find(name);
        if (x == this->_container.end())
        {
            spdlog::warn("failed to resolve {}, not existing.", name);
            return nullptr;
        }
        return (T *)x->second;
    }
    template <typename T>
    bool ioc_container::bind(std::string name, T *value)
    {
        spdlog::debug("binding " + name);
        if (this->_container.find(name) != this->_container.end())
        {
            spdlog::error("failed to bind " + name + ": exists.");
            return false;
        }
        this->_container[name] = value;
        return true;
    }

    template <typename T>
    bool ioc_container::unbind(std::string name, bool free)
    {
        auto o = (T *)this->resolve<void>(name);
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

    template <typename T>
    void ioc_container::foreach (std::function<bool(std::string, T)> callback)
    {
        for (auto x : this->_container)
        {
            if (!callback(x.first, (T)x.second))
            {
                break;
            }
        }
    }
}
