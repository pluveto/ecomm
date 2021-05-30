#include <string>
#include <cstdint>
#include <ecomm/model/product_abstract.hpp>
namespace ecomm
{
    namespace model
    {
        class dress_product : public product_abstract
        {
        public:
            std::string size;
            std::string brand;
            std::string to_ext_props();
            void from_ext_props(std::string ext_props);
            virtual std::string detail() const;

            dress_product() {}
            dress_product(
                size_t uid,
                double price,
                double discount,
                double total_amount,
                double available_amount,
                std::string type,
                std::string title,
                std::string description,
                std::string size,
                std::string brand)
                : product_abstract(uid,
                                   price,
                                   discount,
                                   total_amount,
                                   available_amount,
                                   type,
                                   title,
                                   description),
                  size(size),
                  brand(brand) {}
        };

    }
}