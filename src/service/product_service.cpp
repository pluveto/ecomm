/**
 * @file product_service.cpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-20
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */
#include <ecomm/service/product_service.hpp>
#include <ecomm/model/book_product.hpp>
#include <ecomm/model/food_product.hpp>
#include <ecomm/model/dress_product.hpp>

#include <openssl/md5.h>
#include <stdio.h>
#include <ecomm/util.hpp>

namespace ecomm
{
    namespace service
    {
        product_service::product_service(ecomm::ioc_container *const iocc) : base_service(iocc)
        {
            this->_storage_service = iocc->resolve<storage_service>("storage_service");
        }

        model::product_abstract *product_service::build(std::string type)
        {
            if ("food" == type)
            {
                return new model::food_product();
            }
            if ("dress" == type)
            {
                return new model::dress_product();
            }
            if ("book" == type)
            {
                return new model::book_product();
            }
            throw "Bad product type.";
            return nullptr;
        }

        size_t product_service::update(std::u16string key, std::string val, std::u16string where_key, std::string where_val, size_t uid)
        {

            auto db = this->_storage_service->storage();
            model::product_abstract *u = nullptr;
            auto s = u"update products "
                     "set ";
            std::u16string sql(s);
            sql += key;
            sql += std::u16string(u" = ? ");

            sql += u"where ";
            sql += where_key;
            sql += std::u16string(u" = ? ");

            sql += u"and uid = ?";

            try
            {
                *db << sql << val << where_val << uid;
            }
            catch (sqlite_exception &e)
            {
                std::cerr << e.get_code() << ": " << e.what() << " during "
                          << e.get_sql() << std::endl;
            }

            return sqlite3_changes(db->connection().get());
        }

        bool product_service::has(std::u16string key, std::string val, std::u16string extra_where)
        {
            auto tmp_item = this->get_by(key, val, extra_where);
            if (nullptr == tmp_item)
            {
                return false;
            }
            delete tmp_item;
            return true;
        }
        model::product_abstract *product_service::get_by(std::u16string key, std::string val, std::u16string extra_where)
        {

            auto db = this->_storage_service->storage();
            model::product_abstract *u = nullptr;
            auto s = u"select id,uid,price,discount,total_amount,available_amount,type,title,description,_ext_props from products "
                     "where ";
            std::u16string sql(s);
            sql += key;
            sql += std::u16string(u" = ?");
            sql += (extra_where);
            try
            {
                *db << sql
                    << val >>
                    [&](size_t id,
                        size_t uid,
                        double price,
                        double discount,
                        double total_amount,
                        double available_amount,
                        std::string type,
                        std::string title,
                        std::string description,
                        std::string _ext_props)
                {
                    u = this->build(type);
                    u->id = id;
                    u->uid = uid;
                    u->price = price;
                    u->discount = discount;
                    u->total_amount = total_amount;
                    u->available_amount = available_amount;
                    u->type = type;
                    u->title = title;
                    u->description = description;
                    u->from_ext_props(_ext_props);
                };
            }
            catch (sqlite_exception &e)
            {
                std::cerr << e.get_code() << ": " << e.what() << " during "
                          << e.get_sql() << std::endl;
            }

            return u;
        }

        std::vector<model::product_abstract *> *product_service::search_by(std::u16string key, std::string val, std::u16string extra_where)
        {
            auto db = this->_storage_service->storage();
            auto list = new std::vector<model::product_abstract *>();
            spdlog::debug("Query product list...");
            model::product_abstract *u = nullptr;
            auto s = u"select id,uid,price,discount,total_amount,available_amount,type,title,description,_ext_props from products";
            std::u16string sql(s);
            if (key.size() > 0)
            {
                sql += u" where ";
                sql += key;
                sql += u" like '%' || ? || '%'";
            }
            sql += (extra_where);

            try
            {
                *db << sql
                    << val >>
                    [&](size_t id,
                        size_t uid,
                        double price,
                        double discount,
                        double total_amount,
                        double available_amount,
                        std::string type,
                        std::string title,
                        std::string description,
                        std::string _ext_props)
                {
                    u = this->build(type);
                    u->id = id;
                    u->uid = uid;
                    u->price = price;
                    u->discount = discount;
                    u->total_amount = total_amount;
                    u->available_amount = available_amount;
                    u->type = type;
                    u->title = title;
                    u->description = description;
                    u->from_ext_props(_ext_props);
                    list->push_back(u);
                };
            }
            catch (sqlite_exception &e)
            {
                std::cerr << e.get_code() << ": " << e.what() << " during "
                          << e.get_sql() << std::endl;
            }
            spdlog::debug("{} items found", list->size());

            return list;
        }
        std::vector<model::product_abstract *> *product_service::list_by(std::u16string key, std::string val, std::u16string extra_where)
        {
            auto db = this->_storage_service->storage();
            auto list = new std::vector<model::product_abstract *>();
            spdlog::debug("Query product list...");
            model::product_abstract *u = nullptr;
            auto s = u"select id,uid,price,discount,total_amount,available_amount,type,title,description,_ext_props from products";
            std::u16string sql(s);
            if (key.size() > 0)
            {
                sql += u" where ";
                sql += key;
                sql += u" = ?";
            }
            sql += (extra_where);

            try
            {
                if (key.size() > 0)
                {
                    *db << sql
                        << val >>
                        [&](size_t id,
                            size_t uid,
                            double price,
                            double discount,
                            double total_amount,
                            double available_amount,
                            std::string type,
                            std::string title,
                            std::string description,
                            std::string _ext_props)
                    {
                        u = this->build(type);
                        u->id = id;
                        u->uid = uid;
                        u->price = price;
                        u->discount = discount;
                        u->total_amount = total_amount;
                        u->available_amount = available_amount;
                        u->type = type;
                        u->title = title;
                        u->description = description;
                        u->from_ext_props(_ext_props);
                        list->push_back(u);
                    };
                }
                else
                {
                    *db << sql >>
                        [&](size_t id,
                            size_t uid,
                            double price,
                            double discount,
                            double total_amount,
                            double available_amount,
                            std::string type,
                            std::string title,
                            std::string description,
                            std::string _ext_props)
                    {
                        u = this->build(type);
                        u->id = id;
                        u->uid = uid;
                        u->price = price;
                        u->discount = discount;
                        u->total_amount = total_amount;
                        u->available_amount = available_amount;
                        u->type = type;
                        u->title = title;
                        u->description = description;
                        u->from_ext_props(_ext_props);
                        list->push_back(u);
                    };
                }
            }
            catch (sqlite_exception &e)
            {
                std::cerr << e.get_code() << ": " << e.what() << " during "
                          << e.get_sql() << std::endl;
            }
            spdlog::debug("{} items found", list->size());

            return list;
        }
        bool product_service::save(model::product_abstract *m)
        {
            spdlog::debug("save...");
            auto db = this->_storage_service->storage();
            printf("m->type = %s\n", m->type.c_str());
            if (m->id > 0)
            {
                spdlog::debug("updating...");

                spdlog::debug("updating {}...", m->type);

                *db << u"update products "
                       u"set    uid = ?, price = ?, discount = ?, total_amount = ?,"
                       u"       available_amount = ?, type = ?, title = ?, description = ?, _ext_props = ? "
                       u"where id = ?"
                    << m->uid
                    << m->price
                    << m->discount
                    << m->total_amount
                    << m->available_amount
                    << m->type
                    << m->title
                    << m->description
                    << m->to_ext_props()

                    << m->id;
            }
            else
            {
                spdlog::debug("creating");

                spdlog::debug("creating {}...", ((model::book_product *)m)->type);
                *db << u"insert into products (uid, price, discount, total_amount, available_amount, "
                       u"                      type, title, description, _ext_props) values (?,?,?,?,?, ?,?,?,?); "
                    << m->uid
                    << m->price
                    << m->discount
                    << m->total_amount
                    << m->available_amount
                    << m->type
                    << m->title
                    << m->description
                    << m->to_ext_props();

                m->id = db->last_insert_rowid();
            }
            spdlog::debug("product id = {} is saved.", m->id);
            return true;
        }

    }
}