/**
 * @file crypto_service.cpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-20
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */
#include <ecomm/service/crypto_service.hpp>

#include <openssl/md5.h>
#include <stdio.h>

namespace ecomm
{
    namespace service
    {
        crypto_service::crypto_service(ecomm::ioc_container *const iocc) : base_service(iocc)
        {
        }

        std::string crypto_service::md5(std::string str, std::string sau)
        {
            str += sau;
            // str to md5
            unsigned char result[MD5_DIGEST_LENGTH];
            size_t str_size = str.size();
            auto buffer = str.c_str();
            MD5((unsigned char *)buffer, str_size, result);

            // md5 to hex
            char hex_result[MD5_DIGEST_LENGTH * 2 + 1];
            for (int8_t i = 0; i < MD5_DIGEST_LENGTH; i++)
            {
                sprintf(hex_result + 2 * i, "%02x", result[i]);
            }
            return std::string(hex_result);
        }
    }
}