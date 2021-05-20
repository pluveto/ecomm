/**
 * @file main.cpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-20
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */
#include <ecomm/app.hpp>
int main(int argc, char *argv[])
{
   auto app = new ecomm::app();
   app->config("app.json");
   app->init();
   app->run();
}

