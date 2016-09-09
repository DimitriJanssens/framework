#ifndef TESTFRAMEWORK_H
#define TESTFRAMEWORK_H

#include <common/commontypes.h>
#include <check/check.h>

#define ENV_RESULTS_DIR (const char* const) "RESULTS_DIR"

void suite_run(const char_t *const name, Suite *suite);
void tcase_add_valgrind_fixtures(TCase *tc);

#endif