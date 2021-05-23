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
#include <ecomm/model/product_abstract.hpp>
#include <ecomm/service/storage_service.hpp>

namespace ecomm
{
    namespace service
    {
        class product_service : public base_service
        {
        private:
            storage_service *_storage_service;

        public:
            product_service(ecomm::ioc_container *const iocc);
            model::product_abstract *get_by(std::u16string key, std::string val, std::u16string extra_where = u"");
            size_t update(std::u16string key, std::string val,std::u16string where_key, std::string where_val, size_t uid) ;
            std::vector<model::product_abstract *> *list_by(std::u16string key = u"", std::string val = "", std::u16string extra_where = u"");
            std::vector<model::product_abstract *> *search_by(std::u16string key = u"", std::string val = "", std::u16string extra_where = u"");
            model::product_abstract *build(std::string type);
            bool save(model::product_abstract *u);
        };
        

    }
}