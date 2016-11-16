#include "test_tcp_tcases.h"

#include <logging/logging.h>
#include <protocols/tcpIntf.h>
#include <osa/osmemIntf.h>

#include "tcp_socket.h"

#include "test_tcp_helper.h"

START_TEST(test_NULL)
  const TcpIntf_t * const ti = getTcpIntf();
  OsNetSocket_t * socket = (OsNetSocket_t *) 0x12345;
  TcpSocketIpv4Address_t addr;
  uint8_t data[10];
  size_t bytes;

  ck_assert(ti->socket_create_connect(NULL, NULL) == STATUS_FAILURE);
  ck_assert(ti->socket_create_connect(&socket, NULL) == STATUS_FAILURE);
  ck_assert(ti->socket_create_connect(NULL, &addr) == STATUS_FAILURE);

  ck_assert(ti->socket_write(NULL, NULL, 0, NULL) == STATUS_FAILURE);
  ck_assert(ti->socket_write(socket, NULL, 0, NULL) == STATUS_FAILURE);
  ck_assert(ti->socket_write(socket, data, 0, NULL) == STATUS_FAILURE);
  ck_assert(ti->socket_write(NULL, data, 0, NULL) == STATUS_FAILURE);
  ck_assert(ti->socket_write(NULL, data, 0, &bytes) == STATUS_FAILURE);
  ck_assert(ti->socket_write(NULL, NULL, 0, &bytes) == STATUS_FAILURE);

  ck_assert(ti->socket_read(NULL, NULL, 0, NULL) == STATUS_FAILURE);
  ck_assert(ti->socket_read(socket, NULL, 0, NULL) == STATUS_FAILURE);
  ck_assert(ti->socket_read(socket, data, 0, NULL) == STATUS_FAILURE);
  ck_assert(ti->socket_read(NULL, data, 0, NULL) == STATUS_FAILURE);
  ck_assert(ti->socket_read(NULL, data, 0, &bytes) == STATUS_FAILURE);
  ck_assert(ti->socket_read(NULL, NULL, 0, &bytes) == STATUS_FAILURE);

  ck_assert(ti->socket_destroy(NULL) == STATUS_FAILURE);

END_TEST

static OsNetSocket_t * localTcpSocketListenCreate(const TcpSocketIpv4Address_t * const address)
{
  ck_assert(address != NULL);

  OsNetSocket_t * socket = NULL;
  ck_assert(tcp_socket_create_listen(&socket, address, 1) == STATUS_SUCCESS);
  ck_assert(socket != NULL);
  return socket;
}

static OsNetSocket_t * localTcpSocketConnectCreate(const TcpSocketIpv4Address_t * const address)
{
  const TcpIntf_t * const ti = getTcpIntf();

  ck_assert(address != NULL);

  OsNetSocket_t * socket = NULL;
  ck_assert(ti->socket_create_connect(&socket, address) == STATUS_SUCCESS);
  ck_assert(socket != NULL);
  return socket;
}

static void localTcpSocketDestroy(OsNetSocket_t * socket)
{
  const TcpIntf_t * const ti = getTcpIntf();

  ck_assert(socket != NULL);
  ck_assert(ti->socket_destroy(socket) == STATUS_SUCCESS);
}

START_TEST(test_tcp_socket)
  TcpSocketIpv4Address_t addr;
  addr.address = TCPSOCKETIPV4ADDRESS(127,0,0,1);
  addr.port = 12345;

  OsNetSocket_t * listensock = localTcpSocketListenCreate(&addr);
  OsNetSocket_t * remotesock = localTcpSocketConnectCreate(&addr);

  const TcpIntf_t * const tcp = getTcpIntf();

  OsNetSocket_t * localsock;
  ck_assert(getOsNetIntf()->socket_accept(listensock, &localsock, NULL, NULL) == STATUS_SUCCESS);
  OsNetSocket_t * tmp;
  ck_assert(getOsNetIntf()->socket_accept(listensock, &tmp, NULL, NULL) == STATUS_FAILURE);

  //Write some data:
  uint8_t tx_buffer[] = { "DEADBEEF" };
  const size_t tx_buffer_size = ARRAY_SIZE(tx_buffer);
  uint8_t rx_buffer[] = { "00000000" };
  const size_t rx_buffer_size = ARRAY_SIZE(rx_buffer);

  INFO("BEFORE: send buffer <%s> vs recv buffer <%s>\n", tx_buffer, rx_buffer);

  size_t txbytes = 0;
  ck_assert(tcp->socket_write(remotesock, tx_buffer, tx_buffer_size, &txbytes) == STATUS_SUCCESS);
  ck_assert(tx_buffer_size == txbytes);

  size_t rxbytes = 0;
  ck_assert(tcp->socket_read(localsock, rx_buffer, rx_buffer_size, &rxbytes) == STATUS_SUCCESS);
  ck_assert(rx_buffer_size == rxbytes);

  INFO("AFTER: send buffer <%s> vs recv buffer <%s>\n", tx_buffer, rx_buffer);

  ck_assert(getOsMemIntf()->memcmp(tx_buffer, rx_buffer, ARRAY_SIZE(tx_buffer)) == STATUS_SUCCESS);

  localTcpSocketDestroy(localsock);
  localTcpSocketDestroy(remotesock);
  localTcpSocketDestroy(listensock);
END_TEST

TCase *tcase_tcp_socket(void)
{
  TCase *tc = tcase_create("TestCase Protocols TCP Socket");
  tcase_set_timeout(tc, 10);
  tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, test_tcp_setup, test_tcp_teardown);

  tcase_add_test(tc, test_NULL);
  tcase_add_test(tc, test_tcp_socket);

  return tc;
}
