#include <string>
#include <cstdint>
#include <ecomm/model/product_abstract.hpp>
namespace ecomm
{
    namespace model
    {
        class book_product : public product_abstract
        {
        public:
            std::string author;
            std::string press;
            std::string isbn;
            std::string to_ext_props();
            void from_ext_props(std::string ext_props);
            book_product(){}
            book_product(
                size_t uid,
                double price,
                double discount,
                double total_amount,
                double available_amount,
                std::string type,
                std::string title,
                std::string description,
                std::string author,
                std::string press,
                std::string isbn)
                : product_abstract(uid,
                                   price,
                                   discount,
                                   total_amount,
                                   available_amount,
                                   type,
                                   title,
                                   description),
                  author(author),
                  press(press),
                  isbn(isbn) {}
        };

    }
}