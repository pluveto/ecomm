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

#include <ecomm/app_conf.hpp>
#include <ecomm/util.hpp>
#include <regex>
namespace ecomm
{
    //Properties
    std::string app_conf::name() { return this->_name; }
    std::string app_conf::db_name() { return this->_db_name; }
    std::string app_conf::motd()
    {
        auto motd =  std::regex_replace(this->_motd, std::regex("\\{name\\}"), this->_name);
        
        return motd;
    }
    // Methods
    void app_conf::from_json(const nlohmann::json &j, app_conf &conf)
    {
        j.at("name").get_to(conf._name);
        j.at("db_name").get_to(conf._db_name);
        std::vector<std::string> motds;
        j.at("motd").get_to(motds);
        conf._motd = ecomm::util::join(motds.begin(), motds.end(), "\n", "\n");
    }
}