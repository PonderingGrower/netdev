#include <linux/module.h>
#include <linux/netlink.h>  /* for netlink sockets */
#include <linux/skbuff.h>
#include <net/sock.h>

#include "netlink.h"
#include "msgtype.h"

/* defines the protocol used, we want our own protocol */
#define NETLINK_USER 31

struct sock *nl_sk = NULL;
/* TODO this will have to be part of a struct that will contain information
 * about the device this driver will pretend to be received from the server
 * process */
int pid;

/* TODO this will have to be modified to receive responses from server process,
 * find the appropriate wait queue and release it once the reply is assigned
 * to appropriate variables in struct describing one pending file operaion */
void netlink_recv(struct sk_buff *skb) {
    struct nlmsghdr *nlh;
    struct sk_buff *skb_out;
    short msgtype;
    int msg_size;
    char *msg = "Device registered";
    int res;

    printk(KERN_INFO "Entering: %s\n", __FUNCTION__);

    msg_size = strlen(msg);

    nlh = (struct nlmsghdr*)skb->data;
    printk(KERN_INFO "Netlink received msg payload: %s\n", (char*)nlmsg_data(nlh));
    pid = nlh->nlmsg_pid; /*pid of sending process */
    msgtype = nlh->nlmsg_type;

    skb_out = nlmsg_new(msg_size, 0);

    if(!skb_out) {
        printk(KERN_ERR "Failed to allocate new skb\n");
        return;
    } 
    nlh = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, msg_size, 0);  

    NETLINK_CB(skb_out).dst_group = 0; /* not in mcast group */

    strncpy(nlmsg_data(nlh) ,msg ,msg_size);

    res = nlmsg_unicast(nl_sk,skb_out,pid);

    if(res>0)
        printk(KERN_INFO "Error while sending bak to user\n");

}

/* TODO should receive not only msgtype but also a buffer with properly 
 * formatted arguments to the file operation from the netdev_fo_OP_send_req */
int netlink_send(short msgtype) {
    struct nlmsghdr *nlh;
    struct sk_buff *skb_out;
    char *msg;
    int msg_size;
    int res;

    if (msgtype == MSGTYPE_NETDEV_ECHO) {
        msg = "ECHO";
    } else {
        msg = "DEFAULT";
    }
    msg_size = strlen(msg);

    skb_out = nlmsg_new(msg_size, 0);

    if(!skb_out) {
        printk(KERN_ERR "Failed to allocate new skb\n");
        return -1;
    } 
    nlh = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, msg_size, 0);  

    NETLINK_CB(skb_out).dst_group = 0; /* not in mcast group */

    strncpy(nlmsg_data(nlh) ,msg ,msg_size);

    res = nlmsg_unicast(nl_sk,skb_out,pid);

    if(res>0)
        printk(KERN_INFO "Error while sending bak to user\n");

    return 0;
}

int netlink_init(void) {
    // new structure for configuring netlink socket changed in linux kernel 3.8
    // http://stackoverflow.com/questions/15937395/netlink-kernel-create-is-not-working-with-latest-linux-kernel
    struct netlink_kernel_cfg nl_cfg;
    nl_cfg.groups = 0,// used for multicast
    nl_cfg.flags = 0, // TODO
    nl_cfg.input = netlink_recv, // pointer to function that will receive data

    printk("Entering: %s\n", __FUNCTION__);

    nl_sk = netlink_kernel_create(&init_net, NETLINK_USER, &nl_cfg);

    if(!nl_sk) {
        printk(KERN_ALERT "Error creating socket.\n");
        return -10;
    }

    return 0;
}

void netlink_exit(void) {
    printk(KERN_INFO "exiting hello module\n");
    // TODO will have to close connections of all devices with the server process

    /* can only be done once the process releases the socket, otherwise
     * kernel will refuse to unload the module */
    netlink_kernel_release(nl_sk);
}

MODULE_LICENSE("GPL");
