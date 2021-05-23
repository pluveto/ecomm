/**
 * @file app_conf.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief Application config class
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

        /**
         * @brief Get name
         * 
         * @return std::string 
         */
        std::string name();

        /**
         * @brief Get database file name
         * 
         * @return std::string 
         */
        std::string db_name();

        /**
         * @brief Get motd message
         * 
         * @return std::string 
         */
        std::string motd();

        // Methods

        /**
         * @brief Load config from json file
         * 
         * @param j json
         * @param conf config
         */
        static void from_json(const nlohmann::json &j, app_conf &conf);
    };
}