#include <ecomm/handler/cart_handler.hpp>
#include <ecomm/util.hpp>
#include <regex>
#include <vector>
namespace ecomm
{
    namespace handler
    {
        cart_handler::cart_handler(ecomm::ioc_container *const iocc) : base_handler(iocc)
        {
            this->_user_service = iocc->resolve<service::user_service>("user_service");
            this->_product_service = iocc->resolve<service::product_service>("product_service");
            this->_cart_service = iocc->resolve<service::cart_service>("cart_service");
            this->_callback = std::bind(&cart_handler::handle, this, std::placeholders::_1);
        }

        void cart_handler::handle(std::vector<std::string> args)
        {
            if (!this->_user_service->has_login())
            {
                printf("Please logged in.\n");
                return;
            }
            this->_current_user = this->_user_service->current_user();
            if (this->_current_user->type() == "business")
            {
                printf("Only for customer.\n");
                return;
            }
            if (args.size() == 1)
            {
                this->handle_view();
                return;
            }
            else if (args.size() == 3 || args.size() == 4)
            {
                if (args.size() == 3)
                    args.push_back("1");
                auto op = args[1];
                auto id_str = args[2];
                auto amount_str = args[3];
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
                auto prod = this->_product_service->get_by(u"id", id_str);
                if (nullptr == prod)
                {
                    printf("No such product.\n");
                    return;
                }
                if (!util::is_integer(amount_str))
                {
                    printf("Invalid amount: not a integer.\n");
                    return;
                }

                int amount = std::atoi(amount_str.c_str());
                if (amount < 0)
                {
                    printf("Invalid amount: out of range.\n");
                    return;
                }
                // TODO: 余额检查

                if (op == "add")
                {
                    this->handle_add(prod, amount);
                }
                else if (op == "remove")
                {
                    this->handle_remove(prod, amount);
                }
                else if (op == "set")
                {
                    this->handle_set(prod, amount);
                }
                else
                {
                    printf("Unknow operation.\n\n%s", this->help().c_str());
                    return;
                }
                delete prod;
            }
            else
            {
                printf("Unknow operation.\n\n%s", this->help().c_str());
                return;
            }
        }

        void cart_handler::handle_view()
        {
            auto uid = this->_current_user->id;
            printf("Shopping cart:\n");
            auto list = this->_cart_service->list_by(u"uid", std::to_string(uid));
            if (list->size() == 0)
            {
                printf("No result.\n");
            }
            else
            {
                printf("ID           NAME           PRICE       AMOUNT\n");
                for (auto i : *list)
                {
                    //       v  v   v
                    printf("#%3zu%20s%12.2lf%10zu\n", i->pid, i->title.c_str(), i->price, i->amount);
                    delete i;
                }
            }
            delete list;
        }

        void cart_handler::handle_add(model::product_abstract *prod, size_t amount)
        {
            auto uid = this->_current_user->id;
            auto pid = prod->id;
            auto cart_item = this->_cart_service->get_by_uid_pid(uid, pid);
            if (nullptr == cart_item)
            {
                cart_item = this->_cart_service->create(uid, pid);
            }
            auto new_amount = cart_item->amount + amount;
            delete cart_item;
            this->handle_set(prod, new_amount);
        }

        void cart_handler::handle_remove(model::product_abstract *prod, size_t amount)
        {
            auto uid = this->_current_user->id;
            auto pid = prod->id;
            auto cart_item = this->_cart_service->get_by_uid_pid(uid, pid);
            if (nullptr == cart_item)
            {
                cart_item = this->_cart_service->create(uid, pid);
            }
            auto new_amount = cart_item->amount - amount;
            delete cart_item;
            if (new_amount < 0)
            {
                printf("Invaild amount.\n");
                return;
            }
            this->handle_set(prod, new_amount);
        }

        void cart_handler::handle_set(model::product_abstract *prod, size_t amount)
        {

            auto uid = this->_current_user->id;
            auto pid = prod->id;
            if (amount == 0)
            {
                this->_cart_service->remove(uid, pid);
                return;
            }
            auto cart_item = this->_cart_service->get_by_uid_pid(uid, pid);
            if (nullptr == cart_item)
            {
                cart_item = this->_cart_service->create(uid, pid);
            }
            cart_item->amount = amount;
            this->_cart_service->save(cart_item);
            delete cart_item;
            return;
        }

        std::string cart_handler::help() const
        {
            auto help_text = "-- cart --\n"
                             "  {cmd}\n"
                             "      View cart items\n"
                             "  {cmd} add ID\n"
                             "      Add product with id equals ID to your shopping cart.\n"
                             "  {cmd} remove ID\n"
                             "      Remove product with id equals out of your shopping cart.\n"
                             "  {cmd} add ID AMOUNT\n"
                             "      Add product with id equals ID with specific amount to your shopping cart.\n"
                             "  {cmd} remove ID AMOUNT\n"
                             "      Remove product with id equals ID with specific amount out of your shopping cart.\n"
                             "  {cmd} set ID AMOUNT\n"
                             "      Set product amount in your shopping cart with id equals ID.\n";

            return help_text;
        }
        std::string cart_handler::desc() const
        {
            return "View and edit shopping cart.";
        }
    }
}