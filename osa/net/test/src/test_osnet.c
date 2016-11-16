#include "test_osnet_tcases.h"

int main(int argc, char const *argv[])
{
  (void) argc;
  (void) argv;

  Suite * s = suite_create("Suite OsNetIntf");
  suite_add_tcase(s, tcase_osnet_socket_can());
  suite_add_tcase(s, tcase_osnet_socket_interface());
  suite_add_tcase(s, tcase_osnet_socket_udp());
  suite_add_tcase(s, tcase_osnet_socket());
  suite_add_tcase(s, tcase_osnet_socket_tcp());
  suite_run("OSNET", s);

  return 0;
}
