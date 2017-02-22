#include "test_osstring_tcases.h"

#include <osa/osstringIntf.h>
#include <osa/osmemIntf.h>

#include "test_osstring_helper.h"

START_TEST(test_NULL)
  const OsStringIntf_t * const si = getOsStringIntf();
  char_t buffer[1];

  ck_assert(si->string_cmp(NULL, NULL, 0) == STATUS_FAILURE);
  ck_assert(si->string_cmp(buffer, NULL, 0) == STATUS_FAILURE);
  ck_assert(si->string_cmp(NULL, buffer, 0) == STATUS_FAILURE);

  ck_assert(si->string_write(NULL, 0, NULL, NULL) == STATUS_FAILURE);
  ck_assert(si->string_write(buffer, sizeof(buffer), NULL, NULL) == STATUS_FAILURE);
  ck_assert(si->string_write(NULL, sizeof(buffer), NULL, "test") == STATUS_FAILURE);

  ck_assert(si->string_scan(NULL, 0, NULL) == STATUS_FAILURE);
  ck_assert(si->string_scan(buffer, 0, NULL) == STATUS_FAILURE);
  ck_assert(si->string_scan(NULL, 0, "test") == STATUS_FAILURE);

  ck_assert(si->string_length(NULL) == 0);
END_TEST

static const char_t * test_string_short = "ok";
static const char_t * test_string_long = "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

START_TEST(test_string_cmp_ok)
{
  const OsStringIntf_t * const si = getOsStringIntf();

  char_t buffer[10] = "ok";

  ck_assert(STATUS_SUCCESS == si->string_cmp(test_string_short, buffer, 0));
  ck_assert(STATUS_SUCCESS == si->string_cmp(buffer, test_string_short, 0));

  ck_assert(STATUS_SUCCESS == si->string_cmp(test_string_short, buffer, 10));
  ck_assert(STATUS_SUCCESS == si->string_cmp(buffer, test_string_short, 10));
}
END_TEST

START_TEST(test_string_cmp_nok)
{
  const OsStringIntf_t * const si = getOsStringIntf();

  ck_assert(STATUS_FAILURE == si->string_cmp(test_string_short, test_string_long, 0));
  ck_assert(STATUS_FAILURE == si->string_cmp(test_string_long, test_string_short, 0));

  ck_assert(STATUS_FAILURE == si->string_cmp(test_string_short, test_string_long, 10));
  ck_assert(STATUS_FAILURE == si->string_cmp(test_string_long, test_string_short, 10));
}
END_TEST

START_TEST(test_string_write_ok)
  const OsStringIntf_t * const si = getOsStringIntf();

  char_t buffer[10];
  size_t written = 0;

  ck_assert(si->string_write(buffer, sizeof(buffer), NULL, test_string_short) == STATUS_SUCCESS);
  ck_assert(si->string_write(buffer, sizeof(buffer), &written, test_string_short) == STATUS_SUCCESS);
  ck_assert(written != 0);
  ck_assert(written == si->string_length(test_string_short));
END_TEST

START_TEST(test_string_write_buffertoosmall)
  const OsStringIntf_t * const si = getOsStringIntf();

  char_t buffer[10];
  size_t written = 0;

  ck_assert(si->string_write(buffer, sizeof(buffer), NULL, test_string_long) == STATUS_FAILURE);
  ck_assert(si->string_write(buffer, sizeof(buffer), &written, test_string_long) == STATUS_FAILURE);
  ck_assert(written == 0);
  ck_assert(written != si->string_length(test_string_short));
END_TEST

START_TEST(test_string_scan_ok)
  const OsStringIntf_t * const si = getOsStringIntf();

  uint8_t number1 = 0;
  uint8_t number2 = 0;

  ck_assert(si->string_scan("Number1: 45 and Number2: 0xAA", 2, "Number1: %"SCNu8" and Number2: %"SCNi8"", &number1, &number2) == STATUS_SUCCESS);
  ck_assert(number1 == 45);
  ck_assert(number2 == 0xAA);

  uint8_t number3 = 0;
  ck_assert(si->string_scan("Het getal is 33", 1, "Het    getal    is       %"SCNu8"", &number3) == STATUS_SUCCESS);
  ck_assert(number3 == 33);
END_TEST

START_TEST(test_string_scan_conversionrange_max)
  const OsStringIntf_t * const si = getOsStringIntf();

  uint8_t number1 = 0;
  uint8_t number2 = 0;

  const char_t * format = "%"SCNu8";%"SCNi8"";
  const char_t * string = "325;0xAAF";

  ck_assert(si->string_scan(string, 2, format, &number1, &number2) == STATUS_SUCCESS);

  ck_assert_uint_ne(number1, 45);
  ck_assert_uint_eq(number1, 325 & 0xFF);
  ck_assert_uint_ne(number2, 0xAA);
  ck_assert_uint_eq(number2, 0xAAF & 0xFF);
END_TEST

START_TEST(test_string_scan_conversionrange_min)
  const OsStringIntf_t * const si = getOsStringIntf();

  uint8_t number1 = 0;
  uint8_t number2 = 0;

  const char_t * format = "%"SCNu8";%"SCNi8"";
  const char_t * string = "-5;0xAAF";

  ck_assert(si->string_scan(string, 2, format, &number1, &number2) == STATUS_SUCCESS);

  ck_assert_uint_ne(number1, -5);
  ck_assert_uint_eq(number1, (uint8_t) -5);
  ck_assert_uint_ne(number2, 0xAA);
  ck_assert_uint_eq(number2, 0xAAF & 0xFF);
END_TEST

START_TEST(test_string_scan_conversionerror_allitems)
  const OsStringIntf_t * const si = getOsStringIntf();

  uint8_t number1 = 0;

  const char_t * format = "%"SCNi8"";
  const char_t * string = "HAHA";

  ck_assert(si->string_scan(string, 1, format, &number1) == STATUS_FAILURE);
END_TEST

START_TEST(test_string_scan_conversionerror_someitems)
  const OsStringIntf_t * const si = getOsStringIntf();

  uint8_t number1 = 0;
  uint8_t number2 = 0;

  const char_t * format = "%"SCNu8";%"SCNu8"";
  const char_t * string = "a;45";

  ck_assert(si->string_scan(string, 2, format, &number1, &number2) == STATUS_FAILURE);
END_TEST

START_TEST(test_string_length)
{
  const OsStringIntf_t * const si = getOsStringIntf();
  ck_assert(si->string_length(test_string_short) == 2);
  ck_assert(si->string_length(test_string_long) == 446);
}
END_TEST

TCase * tcase_osstring(void)
{
  TCase *tc = tcase_create("TestCase OsStringIntf");
  tcase_set_timeout(tc, 10);
  tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, test_osstring_setup, test_osstring_teardown);

  tcase_add_test(tc, test_NULL);
  tcase_add_test(tc, test_string_cmp_ok);
  tcase_add_test(tc, test_string_cmp_nok);
  tcase_add_test(tc, test_string_write_ok);
  tcase_add_test(tc, test_string_write_buffertoosmall);
  tcase_add_test(tc, test_string_scan_ok);
  tcase_add_test(tc, test_string_scan_conversionrange_max);
  tcase_add_test(tc, test_string_scan_conversionrange_min);
  tcase_add_test(tc, test_string_scan_conversionerror_allitems);
  tcase_add_test(tc, test_string_scan_conversionerror_someitems);
  tcase_add_test(tc, test_string_length);

  return tc;
}
