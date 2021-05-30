/**
 * @file cart_service.cpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief                                                                                                                                                                   
 * @date 2021-05-29
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */
#include <ecomm/service/cart_service.hpp>
#include <openssl/md5.h>
#include <stdio.h>
#include <ecomm/util.hpp>

namespace ecomm
{
    namespace service
    {
        cart_service::cart_service(ecomm::ioc_container *const iocc) : base_service(iocc)
        {
            this->_storage_service = iocc->resolve<storage_service>("storage_service");
            this->_product_service = iocc->resolve<product_service>("product_service");
        }

        size_t cart_service::update(std::u16string key, std::string val, std::u16string where_key, std::string where_val, size_t uid)
        {

            auto db = this->_storage_service->storage();

            model::cart_item *u = nullptr;

            auto s = u"update cart_items "
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
        model::cart_item *cart_service::create(size_t user_id, size_t product_id)
        {
            auto tmp_product = this->_product_service->get_by(u"id", std::to_string(product_id));
            auto m = new model::cart_item();
            m->id = 0; // wait to be updated when insert
            m->title = tmp_product->title;
            m->uid = user_id;
            m->pid = product_id;
            m->price = tmp_product->real_price();
            m->amount = 1;
            delete tmp_product;
            spdlog::debug("create cart item, pid = {}", product_id);
            return m;
        }
        void cart_service::remove(size_t user_id, size_t product_id)
        {
            auto db = this->_storage_service->storage();
            auto s = u"delete from cart_items where uid = ? and pid = ?";
            auto sql = std::u16string(s);
            try
            {
                *db << sql
                    << user_id
                    << product_id;
            }
            catch (sqlite_exception &e)
            {
                std::cerr << e.get_code() << ": " << e.what() << " during "
                          << e.get_sql() << std::endl;
            }
        }
        model::cart_item *cart_service::get_by_uid_pid(size_t user_id, size_t product_id)
        {
            auto db = this->_storage_service->storage();
            model::cart_item *m = nullptr;
            auto s = u"select id,title,uid,pid,amount from cart_items where uid = ? and pid = ?";
            auto sql = std::u16string(s);
            try
            {
                *db << sql
                    << user_id
                    << product_id >>
                    [&](size_t id, std::string title, size_t uid, size_t pid, size_t amount)
                {
                    m = new model::cart_item();
                    m->id = id;
                    m->title = title;
                    m->uid = uid;
                    m->pid = pid;
                    m->amount = amount;
                };
            }
            catch (sqlite_exception &e)
            {
                std::cerr << e.get_code() << ": " << e.what() << " during "
                          << e.get_sql() << std::endl;
            }
            auto tmp_product = this->_product_service->get_by(u"id", std::to_string(product_id));
            if (nullptr == m)
            {
                /* m = new model::cart_item();
                m->id = 0; // wait to be updated when insert
                m->title = tmp_product->title;
                m->uid = user_id;
                m->pid = product_id;
                m->amount = 1; */
            }
            else
            {
                m->price = tmp_product->real_price();
            }

            delete tmp_product;

            return m;
        }
        std::vector<model::cart_item *> *cart_service::list_by(std::u16string key, std::string val, std::u16string extra_where)
        {
            auto db = this->_storage_service->storage();
            if (nullptr == db)
            {
                spdlog::debug("nullptr == db !!!!!!!");
            }
            auto list = new std::vector<model::cart_item *>();
            spdlog::debug("Query product list...");
            model::cart_item *u = nullptr;
            auto s = u"select id,title,uid,pid,amount from cart_items";
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
                        [&](size_t id, std::string title, size_t uid, size_t pid, size_t amount)
                    {
                        auto m = new model::cart_item();
                        m->id = id;
                        m->title = title;
                        m->uid = uid;
                        m->pid = pid;

                        auto tmp_product = this->_product_service->get_by(u"id", std::to_string(pid));

                        m->price = tmp_product->real_price();

                        delete tmp_product;

                        m->amount = amount;
                        list->push_back(m);
                    };
                }
                else
                {
                    *db << sql >>
                        [&](size_t id, std::string title, size_t uid, size_t pid, size_t amount)
                    {
                        auto m = new model::cart_item();
                        m->id = id;
                        m->title = title;
                        m->uid = uid;
                        m->pid = pid;
                        m->amount = amount;

                        auto tmp_product = this->_product_service->get_by(u"id", std::to_string(pid));

                        m->price = tmp_product->real_price();

                        delete tmp_product;

                        list->push_back(m);
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
        bool cart_service::save(model::cart_item *m)
        {
            spdlog::debug("save...");
            auto db = this->_storage_service->storage();
            try
            {

                if (m->id > 0)
                {
                    spdlog::debug("updating...");

                    *db << u"update cart_items "
                           u"set    title = ?, uid = ?, pid = ?, amount = ?"
                           u"where  id = ?"
                        << m->title
                        << m->uid
                        << m->pid
                        << m->amount

                        << m->id;
                }
                else
                {
                    spdlog::debug("creating");
                    *db << u"insert into cart_items (title,uid,pid,amount) values (?,?,?,?); "
                        << m->title
                        << m->uid
                        << m->pid
                        << m->amount;

                    m->id = db->last_insert_rowid();
                }
            }

            catch (sqlite_exception &e)
            {
                std::cerr << e.get_code() << ": " << e.what() << " during "
                          << e.get_sql() << std::endl;
            }

            spdlog::debug("product id = {} is saved.", m->id);
            return true;
        }

    }
}