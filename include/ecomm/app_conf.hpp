/**
 * @file app_conf.hpp
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
#include <regex>
#include <nlohmann/json.hpp>
namespace ecomm
{
    class app_conf
    {
    private:
        std::string _name;
        std::string _db_name;
        std::string _motd;

    public:
        //Properties
        std::string name();
        std::string db_name();
        std::string motd();
        // Methods
        static void from_json(const nlohmann::json &j, app_conf &conf);
    };
}