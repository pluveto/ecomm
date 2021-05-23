#include <string>
#include <cstdint>
#include <ecomm/model/product_abstract.hpp>
namespace ecomm
{
    namespace model
    {
        class food_product : public product_abstract
        {
        public:
            time_t expired_at;
            time_t manufactured_at;
            std::string to_ext_props();
            void from_ext_props(std::string ext_props);
            food_product(){}
            food_product(
                size_t uid,
                double price,
                double discount,
                double total_amount,
                double available_amount,
                std::string type,
                std::string title,
                std::string description,
                time_t expired_at,
                time_t manufactured_at)
                : product_abstract(uid,
                                   price,
                                   discount,
                                   total_amount,
                                   available_amount,
                                   type,
                                   title,
                                   description),
                  expired_at(expired_at),
                  manufactured_at(manufactured_at) {}
        };

    }
}