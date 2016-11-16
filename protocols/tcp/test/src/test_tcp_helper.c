#include "test_tcp_helper.h"

#include <osa/osmemIntf.h>
#include <osa/osnetIntf.h>
#include <protocols/tcpIntf.h>

#include "tcp_socket.h"

void test_tcp_setup(void)
{
  setDefaultOsMemIntfForUnittests();
  setDefaultOsNetIntfForUnittests();

  TcpIntf_t * intf = getTcpIntf();
  intf->socket_create_connect = tcp_socket_create_connect;
  intf->socket_read = tcp_socket_read;
  intf->socket_write = tcp_socket_write;
  intf->socket_destroy = tcp_socket_destroy;
}

void test_tcp_teardown(void)
{
  TcpIntf_t * intf = getTcpIntf();
  getOsMemIntf()->memset(intf, 0, sizeof(*intf));

  resetDefaultOsNetIntfForUnittests();
  resetDefaultOsMemIntfForUnittests();
}
