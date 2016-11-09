#include "test_osfile_tcases.h"

#include <osa/osfileIntf.h>
#include <osa/osmemIntf.h>

#include "test_osfile_helper.h"

START_TEST(test_NULL)
  const OsFileIntf_t * const fi = getOsFileIntf();

  OsFile_t * file = (OsFile_t *) 0x12345;
  char_t * path = "test";
  uint64_t data[] = { 0x1122334455667788};

  ck_assert(fi->file_open(NULL, NULL, OSFILEMODE_R) == STATUS_FAILURE);
  ck_assert(fi->file_open(&file, NULL, OSFILEMODE_R) == STATUS_FAILURE);
  ck_assert(fi->file_open(NULL, path, OSFILEMODE_R) == STATUS_FAILURE);

  ck_assert(fi->file_read(NULL, NULL, 0, 0, 0) == 0);
  ck_assert(fi->file_read(file, NULL, 0, 0, 0) == 0);
  ck_assert(fi->file_read(NULL, data, 0, 0, 0) == 0);
  ck_assert(fi->file_read(NULL, data, sizeof(*data), 0, 0) == 0);
  ck_assert(fi->file_read(NULL, data, sizeof(*data), 10, 0) == 0);

  ck_assert(fi->file_write(NULL, NULL, 0, 0) == 0);
  ck_assert(fi->file_write(file, NULL, 0, 0) == 0);
  ck_assert(fi->file_write(NULL, data, 0, 0) == 0);
  ck_assert(fi->file_write(NULL, data, sizeof(*data), 0) == 0);
  ck_assert(fi->file_write(NULL, data, sizeof(*data), 10) == 0);

  ck_assert(fi->file_close(NULL) == STATUS_FAILURE);
END_TEST

static OsFile_t * localFileOpen(const char_t * const path, OsFileMode_e mode)
{
  OsFile_t * rc = NULL;

  ck_assert(path != NULL);
  ck_assert((mode != OSFILEMODE_UNKNOWN) && (mode != OSFILEMODE_SIZE));

  const OsFileIntf_t * const fi = getOsFileIntf();
  ck_assert(fi->file_open(&rc, path, mode) == STATUS_SUCCESS);
  ck_assert(rc != NULL);

  return rc;
}

static void localFileClose(OsFile_t * file)
{
  ck_assert(file != NULL);

  const OsFileIntf_t * const fi = getOsFileIntf();
  ck_assert(fi->file_close(file) == STATUS_SUCCESS);
}

START_TEST(test_open_close)
  localFileClose(localFileOpen("/tmp/osfiletests.test", OSFILEMODE_WPLUS));
END_TEST

START_TEST(test_open_close_modi)
  OsFileMode_e mode = (OsFileMode_e) _i;

  /* Pick an existing file */
  const char_t * const path = "/dev/null";

  if((mode != OSFILEMODE_UNKNOWN) && (mode != OSFILEMODE_SIZE))
  {
    localFileClose(localFileOpen(path, mode));
  }
  else
  {
    const OsFileIntf_t * const fi = getOsFileIntf();
    OsFile_t * file;
    ck_assert(fi->file_open(&file, path, mode) == STATUS_FAILURE);
  }
END_TEST

START_TEST(test_open_read_nonexist)
  const OsFileIntf_t * const fi = getOsFileIntf();
  OsFile_t * file;
  /* Pick an non-existing file */
  const char_t * const path = "/tmp/nonexisting";
  ck_assert(fi->file_open(&file, path, OSFILEMODE_R) == STATUS_FAILURE);
END_TEST

START_TEST(test_open_read_write_close)
  const OsFileIntf_t * const fi = getOsFileIntf();
  const char_t * const text = "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
  size_t nmemb = 32;
  char_t rxBuffer[ 2 * nmemb];

  OsFile_t * file = localFileOpen("/tmp/osfiletests.test", OSFILEMODE_WPLUS);
  ck_assert(fi->file_read(file, rxBuffer, sizeof(*rxBuffer), nmemb, 0) == 0);
  ck_assert(fi->file_write(file, text, sizeof(*text), nmemb) == nmemb);

  ck_assert_int_eq(fi->file_read(file, rxBuffer, sizeof(*rxBuffer), nmemb, 0), nmemb);
  ck_assert(getOsMemIntf()->memcmp(text, rxBuffer, nmemb) == STATUS_SUCCESS);

  ck_assert(fi->file_write(file, text + nmemb, sizeof(*text), nmemb) == nmemb);

  ck_assert_int_eq(fi->file_read(file, rxBuffer, sizeof(*rxBuffer), 2 * nmemb, 0), 2 * nmemb);
  ck_assert(getOsMemIntf()->memcmp(text, rxBuffer, 2 * nmemb) == STATUS_SUCCESS);

  ck_assert_int_eq(fi->file_read(file, rxBuffer, sizeof(*rxBuffer), nmemb, nmemb), nmemb);
  ck_assert(getOsMemIntf()->memcmp(text + nmemb, rxBuffer, nmemb) == STATUS_SUCCESS);

  localFileClose(file);
END_TEST

TCase * tcase_osfile(void)
{
  TCase *tc = tcase_create("TestCase OsFileIntf");
  tcase_set_timeout(tc, 10);
  tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, test_osfile_setup, test_osfile_teardown);

  tcase_add_test(tc, test_NULL);
  tcase_add_test(tc, test_open_close);
  tcase_add_loop_test(tc, test_open_close_modi, OSFILEMODE_UNKNOWN, OSFILEMODE_SIZE);
  tcase_add_test(tc, test_open_read_nonexist);
  tcase_add_test(tc, test_open_read_write_close);

  return tc;
}
