#include "osnet.h"

#include <arpa/inet.h>

uint32_t osnet_htonl(uint32_t hostlong)
{
  return htonl(hostlong);
}

uint16_t osnet_htons(uint16_t hostshort)
{
  return htons(hostshort);
}

uint32_t osnet_ntohl(uint32_t netlong)
{
  return ntohl(netlong);
}

uint16_t osnet_ntohs(uint16_t netshort)
{
  return ntohs(netshort);
}