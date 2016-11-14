#include "test_osstring_tcases.h"

#include <osa/osstringIntf.h>
#include <osa/osmemIntf.h>

#include "test_osstring_helper.h"

START_TEST(test_NULL)
  const OsStringIntf_t * const si = getOsStringIntf();
  char_t buffer[1];

  ck_assert(si->string_write(NULL, 0, NULL, NULL) == STATUS_FAILURE);
  ck_assert(si->string_write(buffer, sizeof(buffer), NULL, NULL) == STATUS_FAILURE);
  ck_assert(si->string_write(NULL, sizeof(buffer), NULL, "test") == STATUS_FAILURE);

  ck_assert(si->string_length(NULL) == 0);
END_TEST

static const char_t * test_string_short = "ok";
static const char_t * test_string_long = "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

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
  tcase_add_test(tc, test_string_write_ok);
  tcase_add_test(tc, test_string_write_buffertoosmall);
  tcase_add_test(tc, test_string_length);

  return tc;
}
