#ifndef _FO_H
#define _FO_H

#include <linux/skbuff.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/netlink.h>  /* for netlink sockets */
#include <linux/completion.h>

#include "netdevmgm.h"

struct netdev_data;
/* file structure for a queue of operations of dummy device, those will have
 * to be allocated fast and from a large pool since there will be a lot */
struct fo_req {
    long               seq;      /* for synchronizing netlink messages       */
    short              msgtype;  /* type of file operation */
    void              *args;     /* place for s_fo_OPERATION structures      */
    size_t             size;     /* size of the s_fo_OPERATION structure     */
    int                rvalue;   /* informs about success of failure of fo   */
    struct completion  comp;     /* completion to release once reply arrives */
};

/* used for sending file operations converted by send_req functions to
 * a buffer of certian size to the loop sending operations whtough netlink
 * to the server process */
int fo_send(short msgtype, struct netdev_data *nddata, void *args, size_t size);
int fo_recv(struct sk_buff *skb);
int fo_complete(struct netdev_data *nddata, struct nlmsghdr *nlh, struct sk_buff *skb);
int fo_execute(void *data);

/* file operation functions for file_operations structure */
loff_t netdev_fo_llseek (struct file *flip, loff_t offset, int whence);
ssize_t netdev_fo_read (struct file *flip, char __user *data, size_t c, loff_t *offset);
ssize_t netdev_fo_write (struct file *flip, const char __user *data, size_t c, loff_t *offset);
ssize_t netdev_fo_aio_read (struct kiocb *a, const struct iovec *b, unsigned long c, loff_t offset);
ssize_t netdev_fo_aio_write (struct kiocb *a, const struct iovec *b, unsigned long c, loff_t d);
unsigned int netdev_fo_poll (struct file *filp, struct poll_table_struct *wait);
long netdev_fo_unlocked_ioctl (struct file *filp, unsigned int b, unsigned long c);
long netdev_fo_compat_ioctl (struct file *filp, unsigned int b, unsigned long c);
int netdev_fo_mmap (struct file *filp, struct vm_area_struct *b);
int netdev_fo_open (struct inode *inode, struct file *filp);
int netdev_fo_flush (struct file *filp, fl_owner_t id);
int netdev_fo_release (struct inode *a, struct file *filp);
int netdev_fo_fsync (struct file *filp, loff_t b, loff_t offset, int d);
int netdev_fo_aio_fsync (struct kiocb *a, int b);
int netdev_fo_fasync (int a, struct file *filp, int c);
int netdev_fo_lock (struct file *filp, int b, struct file_lock *c);
ssize_t netdev_fo_sendpage (struct file *filp, struct page *b, int c, size_t size, loff_t *offset, int f);
unsigned long netdev_fo_get_unmapped_area (struct file *filp, unsigned long b, unsigned long c,unsigned long d, unsigned long e);
int netdev_fo_check_flags (int a);
int netdev_fo_flock (struct file *filp, int b, struct file_lock *c);
ssize_t netdev_fo_splice_write (struct pipe_inode_info *a, struct file *filp, loff_t *offset, size_t size, unsigned int e);
ssize_t netdev_fo_splice_read (struct file *filp, loff_t *offset, struct pipe_inode_info *c, size_t size, unsigned int e);
int netdev_fo_setlease (struct file *filp, long b, struct file_lock **c);
long netdev_fo_fallocate (struct file *filp, int b, loff_t offset, loff_t len);
int netdev_fo_show_fdinfo (struct seq_file *a, struct file *filp);

/* functions for sending and receiving file operations */
loff_t netdev_fo_llseek_send_req (struct file *flip, loff_t offset, int whence);
ssize_t netdev_fo_read_send_req (struct file *flip, char __user *data, size_t size, loff_t *offset);
ssize_t netdev_fo_write_send_req (struct file *flip, const char __user *data, size_t size, loff_t *offset);
size_t netdev_fo_aio_read_send_req (struct kiocb *a, const struct iovec *b, unsigned long c, loff_t offset);
ssize_t netdev_fo_aio_write_send_req (struct kiocb *a, const struct iovec *b, unsigned long c, loff_t d);
unsigned int netdev_fo_poll_send_req (struct file *filp, struct poll_table_struct *wait);
long netdev_fo_unlocked_ioctl_send_req (struct file *filp, unsigned int b, unsigned long c);
long netdev_fo_compat_ioctl_send_req (struct file *filp, unsigned int b, unsigned long c);
int netdev_fo_mmap_send_req (struct file *filp, struct vm_area_struct *b);
int netdev_fo_open_send_req (struct inode *inode, struct file *filp);
int netdev_fo_flush_send_req (struct file *filp, fl_owner_t id);
int netdev_fo_release_send_req (struct inode *a, struct file *filp);
int netdev_fo_fsync_send_req (struct file *filp, loff_t b, loff_t offset, int d);
int netdev_fo_aio_fsync_send_req (struct kiocb *a, int b);
int netdev_fo_fasync_send_req (int a, struct file *filp, int c);
int netdev_fo_lock_send_req (struct file *filp, int b, struct file_lock *c);
ssize_t netdev_fo_sendpage_send_req (struct file *filp, struct page *b, int c, size_t size, loff_t *offset, int f);
unsigned long netdev_fo_get_unmapped_area_send_req (struct file *filp, unsigned long b, unsigned long c,unsigned long d, unsigned long e);
int netdev_fo_check_flags_send_req (int a);
int netdev_fo_flock_send_req (struct file *filp, int b, struct file_lock *c);
ssize_t netdev_fo_splice_write_send_req (struct pipe_inode_info *a, struct file *filp, loff_t *offset, size_t size, unsigned int e);
ssize_t netdev_fo_splice_read_send_req (struct file *filp, loff_t *offset, struct pipe_inode_info *c, size_t size, unsigned int e);
int netdev_fo_setlease_send_req (struct file *filp, long b, struct file_lock **c);
long netdev_fo_fallocate_send_req (struct file *filp, int b, loff_t offset, loff_t len);
int netdev_fo_show_fdinfo_send_req (struct seq_file *a, struct file *filp);

extern struct file_operations netdev_fops;

#endif /* _FO_H */
