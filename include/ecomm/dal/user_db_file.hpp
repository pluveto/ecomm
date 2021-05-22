#include <ecomm/dal/user_db_interface.hpp>

namespace ecomm
{
    namespace dal
    {
        class user_db_file : public user_db_interface
        {
        private:
            /* data */
        public:
            user_db_file(/* args */);
            ~user_db_file();
        };

    } // namespace dal

} // namespace ecomm
