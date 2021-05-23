/**
 * @file product_abstract.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-23
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */

#pragma once

#include <string>
#include <iostream>
#include <cstdint>
#include <iomanip>
namespace ecomm
{
    namespace model
    {
        /**
         * @details 
         * CREATE TABLE "products" (
         *  "id"	INTEGER NOT NULL UNIQUE,
         *  "uid"	INTEGER,
         *  "price"	REAL,
         *  "discount"	REAL,
         *  "total_amount"	REAL,
         *  "available_amount"	REAL,
         *  "type"	TEXT,
         *  "title"	TEXT,
         *  "description"	TEXT,
         *  "_ext_props"	TEXT,
         *  PRIMARY KEY("id" AUTOINCREMENT)
         * )
         * 
         */
        class product_abstract
        {
        public:
            size_t id;
            size_t uid;
            double price;
            double discount;
            double total_amount;
            double available_amount;
            std::string type;
            std::string title;
            std::string description;

            virtual std::string to_ext_props() = 0;
            virtual void from_ext_props(std::string ext_props) = 0;

            virtual std::string brief() const;
            virtual std::string detail() const;
            virtual std::string price_str() const;
            virtual std::string discount_str() const;
            virtual std::string real_price_str() const;
            virtual double real_price() const;
            virtual ~product_abstract();
            product_abstract();

            product_abstract(
                size_t uid,
                double price,
                double discount,
                double total_amount,
                double available_amount,
                std::string type,
                std::string title,
                std::string description)
                : uid(uid),
                  price(price),
                  discount(discount),
                  total_amount(total_amount),
                  available_amount(available_amount),
                  type(type),
                  title(title),
                  description(description) {}
        };

    }
}