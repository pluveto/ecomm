#include <string>
#include <cstdint>
namespace ecomm
{
    namespace model
    {
        struct user
        {
            size_t id;
            double balance;
            std::string username;
            std::string password;
            std::string role;
        };
    }
}