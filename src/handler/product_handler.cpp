/**
 * @file product_handler.cpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-23
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */

#include <ecomm/handler/product_handler.hpp>

#include <regex>
#include <ecomm/util.hpp>
#include <ctime>

#include <ecomm/model/food_product.hpp>
#include <ecomm/model/dress_product.hpp>
#include <ecomm/model/book_product.hpp>

namespace ecomm
{
    namespace handler
    {
        product_handler::product_handler(ecomm::ioc_container *const iocc) : base_handler(iocc)
        {
            this->_callback = std::bind(&product_handler::handle, this, std::placeholders::_1);
            this->_product_service = iocc->resolve<service::product_service>("product_service");
        }

        void product_handler::handle(std::vector<std::string> args)
        {
            this->_current_user = this->_iocc->resolve<model::user_abstract>("current_user");

            if (args.size() == 1)
            {
                printf("Type `help %s` for details.\n", args[0].c_str());
                return;
            }
            if (args.size() == 2)
            {
                if (args[1] == "add")
                {
                    this->handle_add(args);
                    return;
                }
                else if (args[1] == "remove")
                {
                    this->handle_remove(args);
                    return;
                }
                else if (args[1] == "list")
                {
                    this->handle_list(args);
                    return;
                }
                else if (args[1] == "discount")
                {
                    this->handle_discount(args);
                    return;
                }
                printf("Type `help %s` for details.\n", args[0].c_str());
            }

            if (args.size() == 3)
            {
                if (args[1] == "view")
                {
                    this->handle_view(args);
                    return;
                }
                else if (args[1] == "edit")
                {
                    this->handle_edit(args);
                    return;
                }
                else if (args[1] == "list")
                {
                    this->handle_list(args);
                    return;
                }
                else if (args[1] == "search")
                {
                    this->handle_search(args);
                    return;
                }
                printf("Type `help %s` for details.\n", args[0].c_str());
            }
        }

        void product_handler::handle_view(std::vector<std::string> &args)
        {
            std::string id_str = args[2];
            if (!util::is_integer(id_str))
            {
                printf("Invalid id: not a integer.\n");
                return;
            }
            int id = std::atoi(id_str.c_str());
            if (id <= 0)
            {
                printf("Invalid id: out of range.\n");
                return;
            }
            auto prod = this->_product_service->get_by(u"id", std::to_string(id));
            if (nullptr == prod)
            {
                printf("Not found.\n");
                return;
            }
            std::cout << prod->detail();
            delete prod;
        }
        void product_handler::handle_add(std::vector<std::string> &args)
        {
            if (nullptr == this->_current_user)
            {
                printf("Please login.\n");
                return;
            }
            if ("business" != this->_current_user->role)
            {
                printf("Permission denied for this operation. Role not permitted.\n");
                return;
            }
            printf("Available product types:\n"
                   "1. Food\n"
                   "2. Dress\n"
                   "3. Book\n"
                   "Choose type: ");
            int type_num = 0;
            if (!util::expect_number_max_try(type_num, 1, 3, 3, "Choose a type: "))
            {
                return;
            }
            std::string type = std::vector<std::string>{"food", "dress", "book"}[type_num - 1];
            printf("Selected type: %s\n", type.c_str());

            double price = 0;
            printf("Set price: ");
            if (!util::expect_number_max_try(price, 0.01, 10000000000000.00, 3, "Set price: "))
            {
                return;
            }

            double discount = 0.00;
            printf("Set discount: ");
            if (!util::expect_number_max_try(discount, 0.00, 0.99, 3, "Set discount: "))
            {
                return;
            }

            double total_amount = 0;
            printf("Set total amount: ");
            if (!util::expect_number_max_try(total_amount, 0.01, 10000000000000.00, 3, "Set total amount: "))
            {
                return;
            }

            double available_amount = total_amount;

            std::string title;
            printf("Write down product name (title for display): \n");
            if (!util::expect_string_max_try(title, 1, 128, 3, "Write down product name (title for display): \n"))
            {
                return;
            }

            std::string description;
            printf("Write down product description: \n");
            if (!util::expect_string_max_try(description, 0, 2048, 3, "Write down product description: \n"))
            {
                return;
            }
            std::string _ext_props;

            model::product_abstract *new_product;
            size_t uid = this->_current_user->id;

            if (type == "food")
            {
                time_t current_ts, expired_at, manufactured_at;
                current_ts = std::time(0);
                printf("Input expiration time: ");
                if (!util::expect_datetime_max_try(expired_at, current_ts, current_ts + 100L * 365L * 24L * 3600L, 3L, "Input expiration time: "))
                {
                    return;
                }
                printf("Input manufacture time: ");

                if (!util::expect_datetime_max_try(manufactured_at, current_ts, current_ts + 100L * 365L * 24L * 3600L, 3L, "Input manufacture time: "))
                {
                    return;
                }

                new_product = new model::food_product(uid, price, discount, total_amount, available_amount, type, title, description, expired_at, manufactured_at);
            }
            else if (type == "dress")
            {
                std::string size;
                printf("Write dress size: \n");
                if (!util::expect_string_max_try(size, 1, 32, 3, "Write dress size: \n"))
                {
                    return;
                }

                std::string brand;
                printf("Write dress brand: \n");
                if (!util::expect_string_max_try(brand, 1, 32, 3, "Write dress brand: \n"))
                {
                    return;
                }

                new_product = new model::dress_product(uid, price, discount, total_amount, available_amount, type, title, description, size, brand);
            }
            else if (type == "book")
            {

                std::string author;
                printf("Write book author: \n");
                if (!util::expect_string_max_try(author, 1, 32, 3, "Write book author: \n"))
                {
                    return;
                }

                std::string press;
                printf("Write book press: \n");
                if (!util::expect_string_max_try(press, 1, 32, 3, "Write book press: \n"))
                {
                    return;
                }

                std::string isbn;
                printf("Write book isbn: \n");
                if (!util::expect_string_max_try(isbn, 1, 32, 3, "Write book isbn: \n"))
                {
                    return;
                }

                new_product = new model::book_product(uid, price, discount, total_amount, available_amount, type, title, description, author, press, isbn);
                new_product->id = 0;
                spdlog::debug("new_product created.");
            }
            else
            {
                throw("Unexpected type.");
                return;
            }
            printf("new_product type : %s\n", new_product->type.c_str());
            this->_product_service->save(new_product);
            delete new_product;
        }

        void product_handler::handle_edit(std::vector<std::string> &args)
        {
            if (nullptr == this->_current_user)
            {
                printf("Please login.\n");
                return;
            }
            if ("business" != this->_current_user->role)
            {
                printf("Permission denied for this operation.\n");
                return;
            }
            std::string id_str = args[2];
            if (!util::is_integer(id_str))
            {
                printf("Invalid id: not a integer.\n");
                return;
            }
            int id = std::atoi(id_str.c_str());
            if (id <= 0)
            {
                printf("Invalid id: out of range.\n");
                return;
            }
            std::u16string uid_limit = u" and uid = " + util::int_to_u16string(this->_current_user->id);
            auto prod = this->_product_service->get_by(u"id", std::to_string(id), uid_limit);
            if (nullptr == prod)
            {
                printf("Not found or not your product.\n");
                return;
            }
            printf("Available operation:\n"
                   "1. Edit price\n"
                   "2. Edit discount\n"
                   "3. Increase stock\n"
                   "4. Decrease stock\n"
                   "Choose type: ");
            int type = 0;
            if (!util::expect_number_max_try(type, 1, 4, 3, "Choose a operation: "))
            {
                delete prod;
                return;
            }
            if (type == 1)
            {

                double price = 0;
                printf("Set price: ");
                if (!util::expect_number_max_try(price, 0.01, 10000000000000.00, 3, "Set price: "))
                {
                    delete prod;
                    return;
                }
                prod->price = price;
                this->_product_service->save(prod);
                delete prod;
                return;
            }
            else if (type == 2)
            {
                double discount = 0.00;
                printf("Set discount: ");
                if (!util::expect_number_max_try(discount, 0.00, 0.99, 3, "Set discount: "))
                {
                    delete prod;
                    return;
                }
                prod->discount = discount;
                this->_product_service->save(prod);
                delete prod;
                return;
            }
            else if (type == 3)
            {
                double increase_amount = 0;
                printf("Set increase amount: ");
                if (!util::expect_number_max_try(increase_amount, 0.01, 10000000000000.00, 3, "Set increase amount: "))
                {
                    delete prod;
                    return;
                }

                prod->total_amount += increase_amount;
                prod->available_amount += increase_amount;
                this->_product_service->save(prod);
                delete prod;
                return;
            }
            else if (type == 4)
            {
                double decrease_amount = 0;
                printf("Set increase amount: ");
                double max_decrease = prod->available_amount;
                if (!util::expect_number_max_try(decrease_amount, 0.01, max_decrease, 3, "Set increase amount: "))
                {
                    delete prod;
                    return;
                }

                prod->total_amount -= decrease_amount;
                prod->available_amount -= decrease_amount;
                this->_product_service->save(prod);
                delete prod;
                return;
            }
        }

        void product_handler::handle_search(std::vector<std::string> &args)
        {
            spdlog::debug("product_handler::handle_search");
            if (args.size() == 3)
            {
                auto keyword = args[2];
                std::u16string additional_condition = u"";
                auto list = this->_product_service->search_by(u"title", keyword, additional_condition);
                if (list->size() == 0)
                {
                    printf("No result.\n");
                }
                else
                {
                    for (auto i : *list)
                    {
                        std::cout << i->brief();
                        delete i;
                    }
                }
                delete list;
            }
        }
        void product_handler::handle_list(std::vector<std::string> &args)
        {
            spdlog::debug("product_handler::handle_list");
            std::u16string additional_condition = u"";
            if (args.size() == 3)
            {
                if (args[2] == "my")
                {

                    if (nullptr == this->_current_user)
                    {
                        printf("Please login.\n");
                        return;
                    }
                    additional_condition = u" and uid = " + util::int_to_u16string(this->_current_user->id);
                }
                printf("Unknown operation.\n");
                return;
            }
            spdlog::debug("fetch list");
            auto list = this->_product_service->list_by(u"", "", additional_condition);
            if (list->size() == 0)
            {
                printf("No result.\n");
            }
            else
            {
                for (auto i : *list)
                {
                    std::cout << i->brief();
                    delete i;
                }
            }
            delete list;
        }

        void product_handler::handle_remove(std::vector<std::string> &args)
        {

            if (nullptr == this->_current_user)
            {
                printf("Please login.\n");
                return;
            }
            if ("business" != this->_current_user->role)
            {
                printf("Permission denied for this operation.\n");
                return;
            }
        }

        void product_handler::handle_discount(std::vector<std::string> &args)
        {
            if (nullptr == this->_current_user)
            {
                printf("Please login.\n");
                return;
            }
            if ("business" != this->_current_user->role)
            {
                printf("Permission denied for this operation. Role not permitted.\n");
                return;
            }
            printf("You're going to perform a batch discount action\n"
                   "Available product types:\n"
                   "1. Food\n"
                   "2. Dress\n"
                   "3. Book\n"
                   "Choose type: ");
            int type_num = 0;
            if (!util::expect_number_max_try(type_num, 1, 3, 3, "Choose a type: "))
            {
                return;
            }
            std::string type = std::vector<std::string>{"food", "dress", "book"}[type_num - 1];
            printf("Selected type: %s\n", type.c_str());

            double discount = 0.00;
            printf("Set discount: ");
            if (!util::expect_number_max_try(discount, 0.00, 0.99, 3, "Set discount: "))
            {
                return;
            }

            size_t aff = this->_product_service->update(u"discount", std::to_string(discount), u"type", type, (this->_current_user->id));
            printf("%ld products affected.\n", aff);
            return;
        }
        std::string product_handler::desc() const
        {
            return "Product commands.";
        }
        std::string product_handler::help() const
        {
            auto help_text = "-- product --\n"
                             "  {cmd} add\n"
                             "      add product.\n"
                             "  {cmd} remove\n"
                             "      remove product.\n"
                             "  {cmd} list\n"
                             "      list products.\n"
                             "  {cmd} list my\n"
                             "      list your products.\n";
            return help_text;
        }
    }
}