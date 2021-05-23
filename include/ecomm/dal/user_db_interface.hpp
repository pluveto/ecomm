#include <stdint.h>
#include <ecomm/model/user_model.hpp>

namespace ecomm
{
    namespace dal
    {
        class user_db_interface
        {
        private:
            /* data */
        public:
            virtual int64_t insert_user(ecomm::model::user_abstract_model *user) = 0;
            virtual int64_t delete_user(ecomm::model::user_abstract_model *user) = 0;
            virtual ecomm::model::user_abstract_model *get_user_by_username(std::string username) = 0;
        };

    } // namespace dal

} // namespace ecomm
