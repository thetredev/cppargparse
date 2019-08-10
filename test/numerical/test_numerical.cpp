#include <vector>

#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>
#include <cppargparse/errors.h>

#include "test_numerical.h"


//
// int
//

TEST(TestInt, Required)
{
    cppargparse::test::numerical_required<int>();
}


TEST(TestInt, Optional)
{
    cppargparse::test::numerical_optional<int>();
}


//
// float
//

TEST(TestFloat, Required)
{
    cppargparse::test::numerical_required<float>();
}


TEST(TestFloat, Optional)
{
    cppargparse::test::numerical_optional<float>();
}
