#include <unordered_map>

#include <ecomm/ioc_container.hpp>

namespace ecomm
{
    class service_router
    {
    private:
        ioc_container *_iocc;

    public:
        service_router(ioc_container *const iocc);
        void init();
        ~service_router() = default;
    };

} // namespace ecomm
