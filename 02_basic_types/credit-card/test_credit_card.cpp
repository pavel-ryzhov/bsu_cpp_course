#include "credit_card.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Simple") {
    // clang-format off
    CHECK(IsValidCreditCardNumber(4003'6000'0000'0014));
    CHECK(IsValidCreditCardNumber(4545'9070'5060'8322));
    CHECK(IsValidCreditCardNumber(4916'8757'5628'8270));
    CHECK(IsValidCreditCardNumber(2376'6160'8768));
    CHECK(IsValidCreditCardNumber(4916'0000'0000'1052));
    CHECK(IsValidCreditCardNumber(4916'0000'0000'6440));
    CHECK(IsValidCreditCardNumber(5536'5429'7439'7815));

    CHECK_FALSE(IsValidCreditCardNumber(4003'6000'0000'0015));
    CHECK_FALSE(IsValidCreditCardNumber(4916'8757'5628'0000));
    CHECK_FALSE(IsValidCreditCardNumber(5536'5428'7439'7815));
    CHECK_FALSE(IsValidCreditCardNumber(2376'6168'8768));
    // clang-format on

    CHECK_FALSE(IsValidCreditCardNumber(1));
    CHECK(IsValidCreditCardNumber(0));
}
