#include <stdio.h>
#include <stdint.h>
#include <string>
#include <cstring>
#include <memory>

#include <gtest/gtest.h>

#include <ecomm/service/crypto_service.hpp>

TEST(CryptoServiceTest, MD5)
{
    auto s = new ecomm::service::crypto_service(nullptr);

    EXPECT_EQ(s->md5("12345678"),
              "25d55ad283aa400af464c76d713c07ad");
    EXPECT_EQ(s->md5(" "),
              "d41d8cd98f00b204e9800998ecf8427e");
}

TEST(CryptoServiceTest, MD5WithSault)
{
    auto s = new ecomm::service::crypto_service(nullptr);
    
    EXPECT_EQ(s->md5("1234","5678"),
              "25d55ad283aa400af464c76d713c07ad");
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
