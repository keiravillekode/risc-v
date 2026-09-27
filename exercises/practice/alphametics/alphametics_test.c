#include "vendor/unity.h"

extern void solve(char *puzzle);

void setUp(void) {
}

void tearDown(void) {
}

void test_puzzle_with_three_letters(void) {
    char puzzle[] = "I + BB = ILL";
    solve(puzzle);
    TEST_ASSERT_EQUAL_STRING("1 + 99 = 100", puzzle);
}

void test_solution_must_have_unique_value_for_each_letter(void) {
    TEST_IGNORE();
    char puzzle[] = "A = B";
    solve(puzzle);
    TEST_ASSERT_EQUAL_STRING("", puzzle);
}

void test_leading_zero_solution_is_invalid(void) {
    TEST_IGNORE();
    char puzzle[] = "ACA + DD = BD";
    solve(puzzle);
    TEST_ASSERT_EQUAL_STRING("", puzzle);
}

void test_puzzle_with_two_digits_final_carry(void) {
    TEST_IGNORE();
    char puzzle[] = "A + A + A + A + A + A + A + A + A + A + A + B = BCC";
    solve(puzzle);
    TEST_ASSERT_EQUAL_STRING("9 + 9 + 9 + 9 + 9 + 9 + 9 + 9 + 9 + 9 + 9 + 1 = 100", puzzle);
}

void test_puzzle_with_four_letters(void) {
    TEST_IGNORE();
    char puzzle[] = "AS + A = MOM";
    solve(puzzle);
    TEST_ASSERT_EQUAL_STRING("92 + 9 = 101", puzzle);
}

void test_puzzle_with_six_letters(void) {
    TEST_IGNORE();
    char puzzle[] = "NO + NO + TOO = LATE";
    solve(puzzle);
    TEST_ASSERT_EQUAL_STRING("74 + 74 + 944 = 1092", puzzle);
}

void test_puzzle_with_seven_letters(void) {
    TEST_IGNORE();
    char puzzle[] = "HE + SEES + THE = LIGHT";
    solve(puzzle);
    TEST_ASSERT_EQUAL_STRING("54 + 9449 + 754 = 10257", puzzle);
}

void test_puzzle_with_eight_letters(void) {
    TEST_IGNORE();
    char puzzle[] = "SEND + MORE = MONEY";
    solve(puzzle);
    TEST_ASSERT_EQUAL_STRING("9567 + 1085 = 10652", puzzle);
}

void test_puzzle_with_ten_letters(void) {
    TEST_IGNORE();
    char puzzle[] = "AND + A + STRONG + OFFENSE + AS + A + GOOD = DEFENSE";
    solve(puzzle);
    TEST_ASSERT_EQUAL_STRING("503 + 5 + 691208 + 2774064 + 56 + 5 + 8223 = 3474064", puzzle);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_puzzle_with_three_letters);
    RUN_TEST(test_solution_must_have_unique_value_for_each_letter);
    RUN_TEST(test_leading_zero_solution_is_invalid);
    RUN_TEST(test_puzzle_with_two_digits_final_carry);
    RUN_TEST(test_puzzle_with_four_letters);
    RUN_TEST(test_puzzle_with_six_letters);
    RUN_TEST(test_puzzle_with_seven_letters);
    RUN_TEST(test_puzzle_with_eight_letters);
    RUN_TEST(test_puzzle_with_ten_letters);
    return UNITY_END();
}
