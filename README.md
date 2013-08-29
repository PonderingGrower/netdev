netdev
======

Description
-----------

This project has a goal of allowing the sharing of physical devices like character and block devices between linux machines over TCP/IP.

Disclamer
---------

The code is not yet stable. Test at your own peril. This WILL cause kernel panics.

Usage
-----

Both kernel module and the daemon program can be compiled with make.

Daemon can be started with or without arguments.

    Usage: ./netdevd [-f CONFIGFILE] [-p LISTENPORT] [-h]

Format of configuration file:

    RemoteDevicePath;DummyDeviceName;DaemonIP;DaemonPort

Example:

    /dev/urandom;netdev_urandom;192.168.1.13;9999

Some static limitations apply. For example limit of devices is 32 and is defined in include/protocol.h with NETDEV_MAX_DEVICES and NETDEV_HTABLE_DEV_SIZE.

Notes
-----

If you want to play with this software please do, and please report any crashes and bugs you might encounter to my github at https://github.com/PonderingGrower/netdev .
