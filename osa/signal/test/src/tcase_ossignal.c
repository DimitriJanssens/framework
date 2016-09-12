#include "test_ossignal_tcases.h"

#include <signal.h>

#include "test_ossignal_helper.h"

START_TEST(test_ossignal_NULL)
  const OsSignalIntf_t * const si = getOsSignalIntf();

  ck_assert(si->handler_register(NULL) == STATUS_FAILURE);
  ck_assert(si->signal_register(OSSIGNAL_UNKNOWN) == STATUS_FAILURE);
END_TEST

static struct
{
  OsSignal_e sig_register;
  int32_t sig_raise;
} m_sigdata[] =
{
  { OSSIGNAL_SIGHUP, SIGHUP },
  { OSSIGNAL_SIGINT, SIGINT },
  { OSSIGNAL_SIGPIPE, SIGPIPE },
  { OSSIGNAL_SIGALRM, SIGALRM },
  { OSSIGNAL_SIGTERM, SIGTERM },
  { OSSIGNAL_SIGUSR1, SIGUSR1 },
  { OSSIGNAL_SIGUSR2, SIGUSR2 },
};

static Boolean_e handler_fired = BOOLEAN_FALSE;
static void localSigHandler(OsSignal_e signal)
{
  (void) signal;
  handler_fired = BOOLEAN_TRUE;
}

START_TEST(test_ossignal)
  handler_fired = BOOLEAN_FALSE;

  const OsSignalIntf_t * const si = getOsSignalIntf();
  ck_assert(si->handler_register(localSigHandler) == STATUS_SUCCESS);
  ck_assert(si->signal_register(m_sigdata[_i].sig_register) == STATUS_SUCCESS);

  ck_assert(raise(m_sigdata[_i].sig_raise) == 0);

  ck_assert(handler_fired == BOOLEAN_TRUE);
END_TEST

TCase * tcase_ossignal(void)
{ 
  TCase *tc = tcase_create("TestCase OsSignalIntf");
  tcase_set_timeout(tc, 10);
  tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, test_ossignal_setup, test_ossignal_teardown);

  tcase_add_test(tc, test_ossignal_NULL);
  tcase_add_loop_test(tc, test_ossignal, 0, ARRAY_SIZE(m_sigdata));

  return tc;
}