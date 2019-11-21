#include "fibo.h"

#include <iostream>
#include <sstream>

#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(constructors)
{
    Fibo f;
    BOOST_CHECK_EQUAL(Fibo(0), f);
    BOOST_CHECK_EQUAL(Fibo(0), Fibo(f));
    BOOST_CHECK_EQUAL(Fibo(0), Zero());
    BOOST_CHECK_EQUAL(Fibo(0), Fibo());
    BOOST_CHECK_EQUAL(Fibo(0), Fibo("0"));
    BOOST_CHECK_EQUAL(Fibo(1), Fibo(1));
    BOOST_CHECK_EQUAL(Fibo(1), One());
    BOOST_CHECK_EQUAL(Fibo("1"), Fibo(1));
    BOOST_CHECK_EQUAL(Fibo("1000101"), Fibo(25));
    BOOST_CHECK_EQUAL(Fibo("10010010"), Fibo(44));
    BOOST_CHECK_EQUAL(Fibo("100101001001010"), Fibo(1337));
    BOOST_CHECK_EQUAL(Fibo("1"), Fibo("1"));
    BOOST_CHECK_EQUAL(Fibo("1"), Fibo("001"));
}

BOOST_AUTO_TEST_CASE(compilation)
{
    Fibo f1, f2;
    bool b;

    //Following test cases should cause compilation error.
    //Please comment out every test after it start causing an error.
//    Fibo f3(true);
//    BOOST_ERROR("Fibo(true) should not compile");
//    Fibo f4('a');
//    BOOST_ERROR("Fibo('a') should not compile");
//    f1 += "10";
//    BOOST_ERROR("f1 += \"10\" should not compile");
//    f1 = f2 + "10";
//    BOOST_ERROR("f1 = f2 + \"10\" should not compile");
//    b = "10" < f2
//    BOOST_ERROR("b = \"10\" < f2 should not compile");
//    Zero() += Fibo("10");
//    BOOST_ERROR("Zero() += Fibo("10") should not compile");
//    One() += Fibo("10");
//    BOOST_ERROR("One() += Fibo("10") should not compile");

    // Following checks should compile.
    // Make sure those are uncommented when implementation is ready.
    BOOST_CHECK((Fibo() += 2) == 2);
    BOOST_CHECK((Fibo(2) = Fibo() + 2) == 2);
//    BOOST_CHECK(b = 2 < f2);
}

BOOST_AUTO_TEST_CASE(print)
{
    std::ostringstream test_string;

    test_string << Fibo(0);
    BOOST_CHECK_EQUAL(test_string.str(), "0");
    test_string.str("");

    test_string << Fibo(1);
    BOOST_CHECK_EQUAL(test_string.str(), "1");
    test_string.str("");

    test_string << Fibo("11");
    BOOST_CHECK_EQUAL(test_string.str(), "100");
}

BOOST_AUTO_TEST_CASE(exceptions)
{
    BOOST_CHECK_THROW(Fibo("0123"), std::invalid_argument);
    BOOST_CHECK_THROW(Fibo("abc"), std::invalid_argument);
    BOOST_CHECK_NO_THROW(Fibo("0"));
    BOOST_CHECK_NO_THROW(Fibo("1"));
    BOOST_CHECK_NO_THROW(Fibo("0101"));
}

BOOST_AUTO_TEST_CASE(addition)
{
    BOOST_REQUIRE_EQUAL(Fibo("101") + Fibo("101"), Fibo("1011"));
    BOOST_REQUIRE_EQUAL(Fibo("1001") + Fibo("1001"), Fibo("10101"));
    BOOST_REQUIRE_EQUAL(Fibo("1001") + Fibo("1010"), Fibo("10110"));
    BOOST_CHECK_EQUAL(Fibo("1") += Fibo("1"), Fibo("10"));
    BOOST_CHECK_EQUAL(Fibo("1") + Fibo("1"), Fibo("10"));
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            Fibo actual = Fibo(i) + Fibo(j);
            Fibo expected = Fibo(i + j);
            if (actual != expected) {
                std::stringstream msg;
                msg << "i = " << i << ", j = " << j << ", actual(" << actual << ") != expected(" << expected << ")";
                BOOST_FAIL(msg.str());
            }
        }
    }
}

BOOST_AUTO_TEST_CASE(provided)
{
    Fibo f;
    BOOST_CHECK_EQUAL(f, Zero());
    BOOST_CHECK_EQUAL(Fibo(f), Zero());
    BOOST_CHECK(Zero() < One());
    BOOST_CHECK_EQUAL(Fibo("11"), Fibo("100"));
    BOOST_CHECK_EQUAL((Fibo("1001") + Fibo("10")), Fibo("1011"));
    BOOST_CHECK_EQUAL((Fibo("1001") & Fibo("1100")), Zero()); // 1100 == 10000
    BOOST_CHECK_EQUAL((Fibo("1100") | Fibo("11")), Fibo("10100")); // 1100 == 10000, 11 == 100
    BOOST_CHECK_EQUAL((Fibo("1001") ^ Fibo("1010")), Fibo("11"));
    BOOST_CHECK_EQUAL((Fibo("101") << 3), Fibo("101000"));

    f = One();
    f <<= 3;
    BOOST_CHECK_EQUAL(f, Fibo("1000"));

    f = One();
    BOOST_CHECK_EQUAL(f + Fibo("1"), Fibo("10"));
    BOOST_CHECK_EQUAL(f, One());

    Fibo f1("101");
    Fibo f2 = Fibo("101");
    BOOST_CHECK_EQUAL(f1, f2);

    BOOST_CHECK_EQUAL(Fibo("11").length(), 3); // 11 == 100

    //std::cout << Fibo("11") << std::endl; // prints 100
}
