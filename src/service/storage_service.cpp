/**
 * @file storage_service.cpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-20
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */
#include <ecomm/service/storage_service.hpp>

#include <openssl/md5.h>
#include <stdio.h>
#include <ecomm/model/user_abstract.hpp>

namespace ecomm
{
    namespace service
    {

        
        storage_service::~storage_service() 
        {
            delete this->_storage;
        }
        

        storage_service::storage_service(ecomm::ioc_container *const iocc) : base_service(iocc)
        {
            using namespace ecomm::model;
            /**
             * Released in storage_service::~storage_service()
             * 
             */
            database *db = new database("test.db");
            this->_storage = db;
        }

        database *storage_service::storage()
        {
            return this->_storage;
        }

    }
}