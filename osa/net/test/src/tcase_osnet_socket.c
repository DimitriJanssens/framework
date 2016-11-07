#include "test_osnet_tcases.h"

#include "test_osnet_helper.h"

START_TEST(test_osnet_socket_NULL)
  const OsNetIntf_t * const neti = getOsNetIntf();
  OsNetSocket_t * socket = (OsNetSocket_t * ) 0x12345;
  ck_assert(neti->socket_create(OSNETSOCKETTYPE_UNKNOWN, NULL) == STATUS_FAILURE);
  ck_assert(neti->socket_create(OSNETSOCKETTYPE_UNKNOWN, &socket) == STATUS_FAILURE);

  ck_assert(neti->socket_fd(NULL) == -1);

  ck_assert(neti->socket_bind(NULL, NULL, 0) == STATUS_FAILURE);
  ck_assert(neti->socket_bind(socket, NULL, 0) == STATUS_FAILURE);
  ck_assert(neti->socket_bind(NULL, (void*) 0x12345, 10) == STATUS_FAILURE);

  size_t size = 10;
  ck_assert(neti->socket_send(NULL, NULL, NULL, 0) == STATUS_FAILURE);
  ck_assert(neti->socket_send(socket, NULL, NULL, 0) == STATUS_FAILURE);
  ck_assert(neti->socket_send(socket, (void*) 0x12345, NULL, 0) == STATUS_FAILURE);
  ck_assert(neti->socket_send(socket, NULL, &size, 0) == STATUS_FAILURE);
  ck_assert(neti->socket_send(NULL, (void*) 0x12345, NULL, 0) == STATUS_FAILURE);
  ck_assert(neti->socket_send(NULL, (void*) 0x12345, &size, 0) == STATUS_FAILURE);
  ck_assert(neti->socket_send(NULL, NULL, &size, 0) == STATUS_FAILURE);

  ck_assert(neti->socket_recv(NULL, NULL, NULL, 0) == STATUS_FAILURE);
  ck_assert(neti->socket_recv(socket, NULL, NULL, 0) == STATUS_FAILURE);
  ck_assert(neti->socket_recv(socket, (void*) 0x12345, NULL, 0) == STATUS_FAILURE);
  ck_assert(neti->socket_recv(socket, NULL, &size, 0) == STATUS_FAILURE);
  ck_assert(neti->socket_recv(NULL, (void*) 0x12345, NULL, 0) == STATUS_FAILURE);
  ck_assert(neti->socket_recv(NULL, (void*) 0x12345, &size, 0) == STATUS_FAILURE);
  ck_assert(neti->socket_recv(NULL, NULL, &size, 0) == STATUS_FAILURE);

  ck_assert(neti->socket_destroy(NULL) == STATUS_FAILURE);

END_TEST

TCase* tcase_osnet_socket(void)
{
  TCase *tc = tcase_create("TestCase OsNetIntf Socket");
  tcase_set_timeout(tc, 10);
  tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, test_osnet_setup, test_osnet_teardown);

  tcase_add_test(tc, test_osnet_socket_NULL);

  return tc;
}
