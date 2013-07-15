#ifndef _NETLINK_H
#define _NETLINK_H

#include <linux/skbuff.h>

void netlink_recv(struct sk_buff *skb);
int netlink_send(short msgtype);
int netlink_init(void);
void netlink_exit(void);

#endif /* _NETLINK_H */
