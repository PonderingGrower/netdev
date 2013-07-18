#ifndef _PROTOCOL_H
#define _PROTOCOL_H

/* defines the default netlink server port */
#define NETDEV_SERVER_PORT 9999

#define NETDEV_MAXLINE  1024

/* 2nd argument to listen() */
#define NETDEV_LISTENQ  1024

/* defines the protocol used, we want our own protocol */
#define NETLINK_PROTOCOL 31

/* define type of message for netlink driver control,
 * will be used in nlmsghdr->nlmsg_type */
#define MSGTYPE_CONTROL_ECHO         1
#define MSGTYPE_CONTROL_REGISTER     2
#define MSGTYPE_CONTROL_UNREGISTER   3
#define MSGTYPE_CONTROL_DRIVER_STOP  4

/* limit of control messsages */
#define MSGTYPE_CONTROL_START       0
#define MSGTYPE_CONTROL_END         100

/* Definitions used to distinguis between file operation structures
 * that contain all the functiona arguments, best used with short or __u16
 * Will be either used in nlmsghdr->nlmsg_type or some inner variable */
#define MSGTYPE_FO_LLSEEK            101
#define MSGTYPE_FO_READ              102
#define MSGTYPE_FO_WRITE             103
#define MSGTYPE_FO_AIO_READ          104
#define MSGTYPE_FO_AIO_WRITE         105
#define MSGTYPE_FO_READDIR           106
#define MSGTYPE_FO_POLL              107
#define MSGTYPE_FO_UNLOCKED_IOCTL    108
#define MSGTYPE_FO_COMPAT_IOCTL      109
#define MSGTYPE_FO_MMAP              110
#define MSGTYPE_FO_OPEN              111
#define MSGTYPE_FO_FLUSH             112
#define MSGTYPE_FO_RELEASE           113
#define MSGTYPE_FO_FSYNC             114
#define MSGTYPE_FO_AIO_FSYNC         115
#define MSGTYPE_FO_FASYNC            116
#define MSGTYPE_FO_LOCK              117
#define MSGTYPE_FO_SENDPAGE          118
#define MSGTYPE_FO_GET_UNMAPPED_AREA 119
#define MSGTYPE_FO_CHECK_FLAGS       120
#define MSGTYPE_FO_FLOCK             121
#define MSGTYPE_FO_SPLICE_WRITE      122
#define MSGTYPE_FO_SPLICE_READ       123
#define MSGTYPE_FO_SETLEASE          124
#define MSGTYPE_FO_FALLOCATE         125
#define MSGTYPE_FO_SHOW_FDINF        126

#define MSGTYPE_FO_START             100
#define MSGTYPE_FO_END               127

#endif /* _PROTOCOL_H */