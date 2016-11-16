#include "test_tcp_tcases.h"

int main(int argc, char const *argv[])
{
  (void) argc;
  (void) argv;

  Suite * s = suite_create("Suite TcpIntf");
  suite_add_tcase(s, tcase_tcp_socket());
  suite_run("TCP", s);

  return 0;
}
