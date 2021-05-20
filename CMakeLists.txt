cmake_minimum_required(VERSION 3.0.0)
project(ecomm VERSION 0.1.0)

include(CTest)
enable_testing()
include_directories("include")


file(GLOB_RECURSE my_sources ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(ecomm src/main.cpp src/app.cpp src/ioc_container.cpp ${my_sources})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)


target_link_libraries(ecomm PRIVATE spdlog::spdlog spdlog::spdlog_header_only)
target_link_libraries(ecomm PRIVATE unofficial::sqlite3::sqlite3)
target_link_libraries(ecomm PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
target_link_libraries(ecomm PRIVATE OpenSSL::Crypto)

