#include "calc.h"
#include <stdio.h>
#include <assert.h>

void test_calc_add()
{
    printf("testing calc_add ... ");
    assert(calc_add(10, 20) == 30);
    assert(calc_add(10, -20) == -10);
    assert(calc_add(-10, -20) == -30);
    assert(calc_add(INT16_MAX, 1) == INT16_MAX + 1);
    assert(calc_add(INT16_MIN, -1) == INT16_MIN - 1);
    printf("done.\n");
}

int main()
{
    test_calc_add();
    return 0;
}
