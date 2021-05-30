/**
 * @file cart_service.hpp
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
#include <ecomm/service/product_service.hpp>
#include <ecomm/model/cart_item.hpp>

namespace ecomm
{
    namespace service
    {
        class cart_service : public base_service
        {
        private:
            storage_service *_storage_service;
            product_service *_product_service;
        
        public:
            cart_service(ecomm::ioc_container *const iocc);
            model::cart_item *get_by_uid_pid(size_t uid, size_t pid);
            model::cart_item *create(size_t uid, size_t pid);
            void remove(size_t uid, size_t pid);
            model::cart_item *get_by(std::u16string key, std::string val, std::u16string extra_where = u"");            
            size_t update(std::u16string key, std::string val,std::u16string where_key, std::string where_val, size_t uid) ;
            std::vector<model::cart_item *> *list_by(std::u16string key = u"", std::string val = "", std::u16string extra_where = u"");            
            bool save(model::cart_item *u);
        };
    }
}
