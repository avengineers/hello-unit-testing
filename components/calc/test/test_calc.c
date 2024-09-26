#include "calc.h"
#include <stdio.h>

void test_calc_add()
{
    int32_t result = calc_add(10, 20);
    if (result == 30)
    {
        printf("test calc_add(10, 20): PASS\n");
    }
    else
    {
        printf("test calc_add(10, 20): FAIL\n");
    }

    result = calc_add(10, -20);
    if (result == -10)
    {
        printf("test calc_add(10, -20): PASS\n");
    }
    else
    {
        printf("test calc_add(10, -20): FAIL\n");
    }

    result = calc_add(-10, -20);
    if (result == -30)
    {
        printf("test calc_add(-10, -20): PASS\n");
    }
    else
    {
        printf("test calc_add(-10, -20): FAIL\n");
    }

    result = calc_add(INT16_MAX, 1);
    if (result == INT16_MAX + 1)
    {
        printf("test calc_add(INT16_MAX, 1): PASS\n");
    }
    else
    {
        printf("test calc_add(INT16_MAX, 1): FAIL\n");
    }

    result = calc_add(INT16_MIN, -1);
    if (result == INT16_MIN - 1)
    {
        printf("test calc_add(INT16_MIN, -1): PASS\n");
    }
    else
    {
        printf("test calc_add(INT16_MIN, -1): FAIL\n");
    }
}

int main()
{
    test_calc_add();
    return 0;
}
