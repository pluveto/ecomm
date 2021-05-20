#include <unordered_map>

#include <ecomm/ioc_container.hpp>

namespace ecomm
{
    class command_router
    {
    private:
        ioc_container *_iocc;

    public:
        command_router(ioc_container *const iocc);
        void init();
        ~command_router() = default;
    };

} // namespace ecomm
