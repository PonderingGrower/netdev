#ifndef _FO_STRUCT_H
#define _FO_STRUCT_H

#include <linux/types.h>
#include <linux/fs.h>

/* structures used to pass file operation arguments to sending function */
struct s_fo_llseek {
    loff_t offset;
    int whence;
    loff_t rvalue;
};
struct s_fo_read {
    char __user *data;
    size_t size;
    loff_t offset;
    ssize_t rvalue;
};
struct s_fo_write {
    char __user *data;
    size_t size;
    loff_t offset;
    ssize_t rvalue;
};
struct s_fo_aio_read {
    struct kiocb *a;
    const struct iovec *b;
    unsigned long c;
    loff_t offset;
    ssize_t rvalue;
};
struct s_fo_aio_write {
    struct kiocb *a;
    struct iovec *b;
    unsigned long c;
    loff_t offset;
    ssize_t rvalue;
};
struct s_dev_fo_poll {
    struct poll_table_struct *wait;
    unsigned long rvalue;
};
struct s_fo_unlocked_ioctl {
    unsigned int cmd;
    unsigned long arg;
    long rvalue;
};
struct s_fo_compat_ioctl {
    unsigned int cmd;
    unsigned long arg;
    long rvalue;
};
struct s_fo_mmap {
    struct vm_area_struct *b;
    int rvalue;
};
struct s_fo_open {
    struct inode *inode;
    int rvalue;
};
struct s_fo_flush {
    int rvalue;
};
struct s_fo_release {
    int rvalue;
};
struct s_fo_fsync {
    loff_t b;
    loff_t c;
    int d;
    int rvalue;
};
struct s_fo_aio_fsync {
    struct kiocb *a;
    int b;
    int rvalue;
};
struct s_fo_fasync {
    int a;
    int c;
    int rvalue;
};
struct s_fo_lock {
    int b;
    int rvalue;
};
struct s_fo_sendpage {
    struct page *b;
    int c;
    size_t size;
    loff_t *offset;
    int f;
    ssize_t rvalue;
};
struct s_fo_get_unmapped_area{
    unsigned long b;
    unsigned long c;
    unsigned long d;
    unsigned long e;
    unsigned long rvalue;
};
struct s_fo_check_flags {
    int a;
    int rvalue;
};
struct s_fo_flock {
    int b;
    int rvalue;
};
struct s_fo_splice_write {
    struct pipe_inode_info *a;
    loff_t *offset;
    size_t size;
    unsigned int e;
    ssize_t rvalue;
};
struct s_fo_splice_read {
    loff_t *b;
    struct pipe_inode_info *c;
    size_t size;
    unsigned int e;
    ssize_t rvalue;
};
struct s_fo_setlease {
    long b;
    int rvalue;
};
struct s_fo_fallocate {
    int b;
    loff_t offset;
    loff_t len;
    long rvalue;
};
struct s_fo_show_fdinfo {
    struct seq_file *a;
    int rvalue;
};

#endif /* _FO_STRUCT_H */
