/*
 * Copyright 2018-2019 Xaptum, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#ifndef ENFTUN_ICMP_H
#define ENFTUN_ICMP_H

#include <netinet/icmp6.h>
#include <netinet/ip6.h>
#include <stdbool.h>

#include "packet.h"

#ifndef ND_RA_FLAG_PRF_HIGH
#define ND_RA_FLAG_PRF_HIGH 0x08
#define ND_RA_FLAG_PRF_MEDIUM 0x00
#define ND_RA_FLAG_PRF_LOW 0x18
#endif

#ifndef ND_OPT_ROUTE_INFO
#define ND_OPT_ROUTE_INFO 24

struct nd_opt_route_info
{ /* route info */
    u_int8_t nd_opt_rti_type;
    u_int8_t nd_opt_rti_len;
    u_int8_t nd_opt_rti_prefixlen;
    u_int8_t nd_opt_rti_flags;
    u_int32_t nd_opt_rti_lifetime;
    /* prefix follows */
};
#endif

struct nd_opt_mtu*
enftun_icmp6_nd_mtu(struct enftun_packet* pkt);

struct nd_opt_route_info*
enftun_icmp6_nd_route_info(struct enftun_packet* pkt,
                           const struct in6_addr* pfx,
                           uint8_t pfxlen,
                           uint32_t lifetime);

struct nd_router_advert*
enftun_icmp6_nd_ra(struct enftun_packet* pkt,
                   const struct in6_addr* src,
                   const struct in6_addr* dst,
                   const struct in6_addr* network,
                   uint16_t prefix,
                   const char** other_routes);

struct nd_router_solicit*
enftun_icmp6_nd_rs_pull(struct enftun_packet* pkt, struct ip6_hdr* iph);

struct icmp6_hdr*
enftun_icmp6_echo_reply_pull(struct enftun_packet* pkt, struct ip6_hdr* iph);

struct icmp6_hdr*
enftun_icmp6_echo_request(struct enftun_packet* pkt,
                          const struct in6_addr* src,
                          const struct in6_addr* dest);

#endif // ENFTUN_ICMP_H
