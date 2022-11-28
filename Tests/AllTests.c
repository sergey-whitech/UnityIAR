#include "unity_fixture.h"

//------------------------------------------------------------------------------
void RunAllTests(void)
{
    RUN_TEST_GROUP(sqrt);
}

//------------------------------------------------------------------------------
TEST_GROUP_RUNNER(sqrt)
{
    RUN_TEST_CASE(sqrt, Positive);
    RUN_TEST_CASE(sqrt, Zero);
    RUN_TEST_CASE(sqrt, Negative);
}
