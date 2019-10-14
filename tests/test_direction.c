#include <criterion/criterion.h>
#include "direction.h"

Test(direction, check_reverse_up)
{
    cr_assert_eq(reverse_direction(UP), DOWN);
}

Test(direction, check_reverse_down)
{
    cr_assert_eq(reverse_direction(DOWN), UP);
}

Test(direction, check_reverse_left)
{
    cr_assert_eq(reverse_direction(LEFT), RIGHT);
}

Test(directions, check_reverse_right)
{
    cr_assert_eq(reverse_direction(RIGHT), LEFT);
}