#include "test_osnet_tcases.h"

#include "test_osnet_helper.h"

START_TEST(test_osnet_NULL)
  const OsNetIntf_t * const neti = getOsNetIntf();
  OsNetSocket_t * socket;
  ck_assert(neti->socket_create(OSNETSOCKETTYPE_UNKNOWN, NULL) == STATUS_FAILURE);
  ck_assert(neti->socket_create(OSNETSOCKETTYPE_CAN, NULL) == STATUS_FAILURE);
  ck_assert(neti->socket_create(OSNETSOCKETTYPE_UNKNOWN, &socket) == STATUS_FAILURE);

END_TEST

static OsNetSocket_t * localCanSocketCreate(void)
{
  const OsNetIntf_t * const neti = getOsNetIntf();

  OsNetSocket_t * socket = NULL;
  ck_assert(neti->socket_create(OSNETSOCKETTYPE_CAN, &socket) == STATUS_SUCCESS);
  ck_assert(socket != NULL);
  return socket;
}

static void localCanSocketDestroy(OsNetSocket_t * socket)
{
  const OsNetIntf_t * const neti = getOsNetIntf();

  ck_assert(socket != NULL);
  ck_assert(neti->socket_destroy(socket) == STATUS_SUCCESS);
}

START_TEST(test_osnet_socket_can_create_destroy)
  localCanSocketDestroy(localCanSocketCreate());
END_TEST

TCase *tcase_osnet_socket_can(void)
{
  TCase *tc = tcase_create("TestCase OsNetIntf Socket CAN");
  tcase_set_timeout(tc, 10);
  tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, test_osnet_setup, test_osnet_teardown);

  tcase_add_test(tc, test_osnet_NULL);
  tcase_add_test(tc, test_osnet_socket_can_create_destroy);

  return tc;
}