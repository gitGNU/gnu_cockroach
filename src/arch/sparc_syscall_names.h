/*
   Syscall names in sparc64, in a suitable format.

   Copyright (C) 2011-2015 Jose E. Marchesi <jemarch@gnu.org>
   Copyright (C) 2011-2015 Giuseppe Scrivano <gscrivano@gnu.org>

   cockroach is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   cockroach is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with the program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* Note that this file is maintained manually, based on the kernel
   asm/unistd.h.  */

#ifndef ROACH_SPARC_SYSCALL_NAMES
#define ROACH_SPARC_SYSCALL_NAMES

#ifndef __SYSCALL
#define __SYSCALL(a, b)
#endif

#ifndef __32bit_syscall_numbers__
#ifndef __arch64__
#define __32bit_syscall_numbers__
#endif
#endif

#define __NR_restart_syscall      0 /* Linux Specific				   */
__SYSCALL(__NR_restart_syscall, sys_restart_syscall)
#define __NR_exit                 1 /* Common                                      */
__SYSCALL(__NR_exit, sys_exit)
#define __NR_fork                 2 /* Common                                      */
__SYSCALL(__NR_fork, sys_fork)
#define __NR_read                 3 /* Common                                      */
__SYSCALL(__NR_read, sys_read)
#define __NR_write                4 /* Common                                      */
__SYSCALL(__NR_write, sys_write)
#define __NR_open                 5 /* Common                                      */
__SYSCALL(__NR_open, sys_open)
#define __NR_close                6 /* Common                                      */
__SYSCALL(__NR_close, sys_close)
#define __NR_wait4                7 /* Common                                      */
__SYSCALL(__NR_wait4, sys_wait4)
#define __NR_creat                8 /* Common                                      */
__SYSCALL(__NR_creat, sys_creat)
#define __NR_link                 9 /* Common                                      */
__SYSCALL(__NR_link, sys_link)
#define __NR_unlink              10 /* Common                                      */
__SYSCALL(__NR_unlink, sys_unlink)
#define __NR_execv               11 /* SunOS Specific                              */
__SYSCALL(__NR_execv, sys_execv)
#define __NR_chdir               12 /* Common                                      */
__SYSCALL(__NR_chdir, sys_chdir)
#define __NR_chown		 13 /* Common					   */
__SYSCALL(__NR_chown		, sys_chown		)
#define __NR_mknod               14 /* Common                                      */
__SYSCALL(__NR_mknod, sys_mknod)
#define __NR_chmod               15 /* Common                                      */
__SYSCALL(__NR_chmod, sys_chmod)
#define __NR_lchown              16 /* Common                                      */
__SYSCALL(__NR_lchown, sys_lchown)
#define __NR_brk                 17 /* Common                                      */
__SYSCALL(__NR_brk, sys_brk)
#define __NR_perfctr             18 /* Performance counter operations              */
__SYSCALL(__NR_perfctr, sys_perfctr)
#define __NR_lseek               19 /* Common                                      */
__SYSCALL(__NR_lseek, sys_lseek)
#define __NR_getpid              20 /* Common                                      */
__SYSCALL(__NR_getpid, sys_getpid)
#define __NR_capget		 21 /* Linux Specific				   */
__SYSCALL(__NR_capget		, sys_capget		)
#define __NR_capset		 22 /* Linux Specific				   */
__SYSCALL(__NR_capset		, sys_capset		)
#define __NR_setuid              23 /* Implemented via setreuid in SunOS           */
__SYSCALL(__NR_setuid, sys_setuid)
#define __NR_getuid              24 /* Common                                      */
__SYSCALL(__NR_getuid, sys_getuid)
#define __NR_vmsplice	         25 /* ENOSYS under SunOS			   */
__SYSCALL(__NR_vmsplice	, sys_vmsplice	)
#define __NR_ptrace              26 /* Common                                      */
__SYSCALL(__NR_ptrace, sys_ptrace)
#define __NR_alarm               27 /* Implemented via setitimer in SunOS          */
__SYSCALL(__NR_alarm, sys_alarm)
#define __NR_sigaltstack	 28 /* Common					   */
__SYSCALL(__NR_sigaltstack	, sys_sigaltstack	)
#define __NR_pause               29 /* Is sigblock(0)->sigpause() in SunOS         */
__SYSCALL(__NR_pause, sys_pause)
#define __NR_utime               30 /* Implemented via utimes() under SunOS        */
__SYSCALL(__NR_utime, sys_utime)
#ifdef __32bit_syscall_numbers__
#define __NR_lchown32            31 /* Linux sparc32 specific                      */
__SYSCALL(__NR_lchown32, sys_lchown32)
#define __NR_fchown32            32 /* Linux sparc32 specific                      */
__SYSCALL(__NR_fchown32, sys_fchown32)
#endif
#define __NR_access              33 /* Common                                      */
__SYSCALL(__NR_access, sys_access)
#define __NR_nice                34 /* Implemented via get/setpriority() in SunOS  */
__SYSCALL(__NR_nice, sys_nice)
#ifdef __32bit_syscall_numbers__
#define __NR_chown32             35 /* Linux sparc32 specific                      */
__SYSCALL(__NR_chown32, sys_chown32)
#endif
#define __NR_sync                36 /* Common                                      */
__SYSCALL(__NR_sync, sys_sync)
#define __NR_kill                37 /* Common                                      */
__SYSCALL(__NR_kill, sys_kill)
#define __NR_stat                38 /* Common                                      */
__SYSCALL(__NR_stat, sys_stat)
#define __NR_sendfile		 39 /* Linux Specific				   */
__SYSCALL(__NR_sendfile		, sys_sendfile		)
#define __NR_lstat               40 /* Common                                      */
__SYSCALL(__NR_lstat, sys_lstat)
#define __NR_dup                 41 /* Common                                      */
__SYSCALL(__NR_dup, sys_dup)
#define __NR_pipe                42 /* Common                                      */
__SYSCALL(__NR_pipe, sys_pipe)
#define __NR_times               43 /* Implemented via getrusage() in SunOS        */
__SYSCALL(__NR_times, sys_times)
#ifdef __32bit_syscall_numbers__
#define __NR_getuid32            44 /* Linux sparc32 specific                      */
__SYSCALL(__NR_getuid32, sys_getuid32)
#endif
#define __NR_umount2             45 /* Linux Specific                              */
__SYSCALL(__NR_umount2, sys_umount2)
#define __NR_setgid              46 /* Implemented via setregid() in SunOS         */
__SYSCALL(__NR_setgid, sys_setgid)
#define __NR_getgid              47 /* Common                                      */
__SYSCALL(__NR_getgid, sys_getgid)
#define __NR_signal              48 /* Implemented via sigvec() in SunOS           */
__SYSCALL(__NR_signal, sys_signal)
#define __NR_geteuid             49 /* SunOS calls getuid()                        */
__SYSCALL(__NR_geteuid, sys_geteuid)
#define __NR_getegid             50 /* SunOS calls getgid()                        */
__SYSCALL(__NR_getegid, sys_getegid)
#define __NR_acct                51 /* Common                                      */
__SYSCALL(__NR_acct, sys_acct)
#ifdef __32bit_syscall_numbers__
#define __NR_getgid32            53 /* Linux sparc32 specific                      */
__SYSCALL(__NR_getgid32, sys_getgid32)
#else
#define __NR_memory_ordering	 52 /* Linux Specific				   */
__SYSCALL(__NR_memory_ordering	, sys_memory_ordering	)
#endif
#define __NR_ioctl               54 /* Common                                      */
__SYSCALL(__NR_ioctl, sys_ioctl)
#define __NR_reboot              55 /* Common                                      */
__SYSCALL(__NR_reboot, sys_reboot)
#ifdef __32bit_syscall_numbers__
#define __NR_mmap2		 56 /* Linux sparc32 Specific			   */
__SYSCALL(__NR_mmap2		, sys_mmap2		)
#endif
#define __NR_symlink             57 /* Common                                      */
__SYSCALL(__NR_symlink, sys_symlink)
#define __NR_readlink            58 /* Common                                      */
__SYSCALL(__NR_readlink, sys_readlink)
#define __NR_execve              59 /* Common                                      */
__SYSCALL(__NR_execve, sys_execve)
#define __NR_umask               60 /* Common                                      */
__SYSCALL(__NR_umask, sys_umask)
#define __NR_chroot              61 /* Common                                      */
__SYSCALL(__NR_chroot, sys_chroot)
#define __NR_fstat               62 /* Common                                      */
__SYSCALL(__NR_fstat, sys_fstat)
#define __NR_fstat64		 63 /* Linux Specific			           */
__SYSCALL(__NR_fstat64		, sys_fstat64		)
#define __NR_getpagesize         64 /* Common                                      */
__SYSCALL(__NR_getpagesize, sys_getpagesize)
#define __NR_msync               65 /* Common in newer 1.3.x revs...               */
__SYSCALL(__NR_msync, sys_msync)
#define __NR_vfork               66 /* Common                                      */
__SYSCALL(__NR_vfork, sys_vfork)
#define __NR_pread64             67 /* Linux Specific                              */
__SYSCALL(__NR_pread64, sys_pread64)
#define __NR_pwrite64            68 /* Linux Specific                              */
__SYSCALL(__NR_pwrite64, sys_pwrite64)
#ifdef __32bit_syscall_numbers__
#define __NR_geteuid32           69 /* Linux sparc32, sbrk under SunOS             */
__SYSCALL(__NR_geteuid32, sys_geteuid32)
#define __NR_getegid32           70 /* Linux sparc32, sstk under SunOS             */
__SYSCALL(__NR_getegid32, sys_getegid32)
#endif
#define __NR_mmap                71 /* Common                                      */
__SYSCALL(__NR_mmap, sys_mmap)
#ifdef __32bit_syscall_numbers__
#define __NR_setreuid32          72 /* Linux sparc32, vadvise under SunOS          */
__SYSCALL(__NR_setreuid32, sys_setreuid32)
#endif
#define __NR_munmap              73 /* Common                                      */
__SYSCALL(__NR_munmap, sys_munmap)
#define __NR_mprotect            74 /* Common                                      */
__SYSCALL(__NR_mprotect, sys_mprotect)
#define __NR_madvise             75 /* Common                                      */
__SYSCALL(__NR_madvise, sys_madvise)
#define __NR_vhangup             76 /* Common                                      */
__SYSCALL(__NR_vhangup, sys_vhangup)
#ifdef __32bit_syscall_numbers__
#define __NR_truncate64		 77 /* Linux sparc32 Specific			   */
__SYSCALL(__NR_truncate64		, sys_truncate64		)
#endif
#define __NR_mincore             78 /* Common                                      */
__SYSCALL(__NR_mincore, sys_mincore)
#define __NR_getgroups           79 /* Common                                      */
__SYSCALL(__NR_getgroups, sys_getgroups)
#define __NR_setgroups           80 /* Common                                      */
__SYSCALL(__NR_setgroups, sys_setgroups)
#define __NR_getpgrp             81 /* Common                                      */
__SYSCALL(__NR_getpgrp, sys_getpgrp)
#ifdef __32bit_syscall_numbers__
#define __NR_setgroups32         82 /* Linux sparc32, setpgrp under SunOS          */
__SYSCALL(__NR_setgroups32, sys_setgroups32)
#endif
#define __NR_setitimer           83 /* Common                                      */
__SYSCALL(__NR_setitimer, sys_setitimer)
#ifdef __32bit_syscall_numbers__
#define __NR_ftruncate64	 84 /* Linux sparc32 Specific			   */
__SYSCALL(__NR_ftruncate64	, sys_ftruncate64	)
#endif
#define __NR_swapon              85 /* Common                                      */
__SYSCALL(__NR_swapon, sys_swapon)
#define __NR_getitimer           86 /* Common                                      */
__SYSCALL(__NR_getitimer, sys_getitimer)
#ifdef __32bit_syscall_numbers__
#define __NR_setuid32            87 /* Linux sparc32, gethostname under SunOS      */
__SYSCALL(__NR_setuid32, sys_setuid32)
#endif
#define __NR_sethostname         88 /* Common                                      */
__SYSCALL(__NR_sethostname, sys_sethostname)
#ifdef __32bit_syscall_numbers__
#define __NR_setgid32            89 /* Linux sparc32, getdtablesize under SunOS    */
__SYSCALL(__NR_setgid32, sys_setgid32)
#endif
#define __NR_dup2                90 /* Common                                      */
__SYSCALL(__NR_dup2, sys_dup2)
#ifdef __32bit_syscall_numbers__
#define __NR_setfsuid32          91 /* Linux sparc32, getdopt under SunOS          */
__SYSCALL(__NR_setfsuid32, sys_setfsuid32)
#endif
#define __NR_fcntl               92 /* Common                                      */
__SYSCALL(__NR_fcntl, sys_fcntl)
#define __NR_select              93 /* Common                                      */
__SYSCALL(__NR_select, sys_select)
#ifdef __32bit_syscall_numbers__
#define __NR_setfsgid32          94 /* Linux sparc32, setdopt under SunOS          */
__SYSCALL(__NR_setfsgid32, sys_setfsgid32)
#endif
#define __NR_fsync               95 /* Common                                      */
__SYSCALL(__NR_fsync, sys_fsync)
#define __NR_setpriority         96 /* Common                                      */
__SYSCALL(__NR_setpriority, sys_setpriority)
#define __NR_socket              97 /* Common                                      */
__SYSCALL(__NR_socket, sys_socket)
#define __NR_connect             98 /* Common                                      */
__SYSCALL(__NR_connect, sys_connect)
#define __NR_accept              99 /* Common                                      */
__SYSCALL(__NR_accept, sys_accept)
#define __NR_getpriority        100 /* Common                                      */
__SYSCALL(__NR_getpriority, sys_getpriority)
#define __NR_rt_sigreturn       101 /* Linux Specific                              */
__SYSCALL(__NR_rt_sigreturn, sys_rt_sigreturn)
#define __NR_rt_sigaction       102 /* Linux Specific                              */
__SYSCALL(__NR_rt_sigaction, sys_rt_sigaction)
#define __NR_rt_sigprocmask     103 /* Linux Specific                              */
__SYSCALL(__NR_rt_sigprocmask, sys_rt_sigprocmask)
#define __NR_rt_sigpending      104 /* Linux Specific                              */
__SYSCALL(__NR_rt_sigpending, sys_rt_sigpending)
#define __NR_rt_sigtimedwait    105 /* Linux Specific                              */
__SYSCALL(__NR_rt_sigtimedwait, sys_rt_sigtimedwait)
#define __NR_rt_sigqueueinfo    106 /* Linux Specific                              */
__SYSCALL(__NR_rt_sigqueueinfo, sys_rt_sigqueueinfo)
#define __NR_rt_sigsuspend      107 /* Linux Specific                              */
__SYSCALL(__NR_rt_sigsuspend, sys_rt_sigsuspend)
#ifdef __32bit_syscall_numbers__
#define __NR_setresuid32        108 /* Linux Specific, sigvec under SunOS	   */
__SYSCALL(__NR_setresuid32, sys_setresuid32)
#define __NR_getresuid32        109 /* Linux Specific, sigblock under SunOS	   */
__SYSCALL(__NR_getresuid32, sys_getresuid32)
#define __NR_setresgid32        110 /* Linux Specific, sigsetmask under SunOS	   */
__SYSCALL(__NR_setresgid32, sys_setresgid32)
#define __NR_getresgid32        111 /* Linux Specific, sigpause under SunOS	   */
__SYSCALL(__NR_getresgid32, sys_getresgid32)
#define __NR_setregid32         112 /* Linux sparc32, sigstack under SunOS         */
__SYSCALL(__NR_setregid32, sys_setregid32)
#else
#define __NR_setresuid          108 /* Linux Specific, sigvec under SunOS	   */
__SYSCALL(__NR_setresuid, sys_setresuid)
#define __NR_getresuid          109 /* Linux Specific, sigblock under SunOS	   */
__SYSCALL(__NR_getresuid, sys_getresuid)
#define __NR_setresgid          110 /* Linux Specific, sigsetmask under SunOS	   */
__SYSCALL(__NR_setresgid, sys_setresgid)
#define __NR_getresgid          111 /* Linux Specific, sigpause under SunOS	   */
__SYSCALL(__NR_getresgid, sys_getresgid)
#endif
#define __NR_recvmsg            113 /* Common                                      */
__SYSCALL(__NR_recvmsg, sys_recvmsg)
#define __NR_sendmsg            114 /* Common                                      */
__SYSCALL(__NR_sendmsg, sys_sendmsg)
#ifdef __32bit_syscall_numbers__
#define __NR_getgroups32        115 /* Linux sparc32, vtrace under SunOS           */
__SYSCALL(__NR_getgroups32, sys_getgroups32)
#endif
#define __NR_gettimeofday       116 /* Common                                      */
__SYSCALL(__NR_gettimeofday, sys_gettimeofday)
#define __NR_getrusage          117 /* Common                                      */
__SYSCALL(__NR_getrusage, sys_getrusage)
#define __NR_getsockopt         118 /* Common                                      */
__SYSCALL(__NR_getsockopt, sys_getsockopt)
#define __NR_getcwd		119 /* Linux Specific				   */
__SYSCALL(__NR_getcwd, sys_getcwd)
#define __NR_readv              120 /* Common                                      */
__SYSCALL(__NR_readv, sys_readv)
#define __NR_writev             121 /* Common                                      */
__SYSCALL(__NR_writev, sys_writev)
#define __NR_settimeofday       122 /* Common                                      */
__SYSCALL(__NR_settimeofday, sys_settimeofday)
#define __NR_fchown             123 /* Common                                      */
__SYSCALL(__NR_fchown, sys_fchown)
#define __NR_fchmod             124 /* Common                                      */
__SYSCALL(__NR_fchmod, sys_fchmod)
#define __NR_recvfrom           125 /* Common                                      */
__SYSCALL(__NR_recvfrom, sys_recvfrom)
#define __NR_setreuid           126 /* Common                                      */
__SYSCALL(__NR_setreuid, sys_setreuid)
#define __NR_setregid           127 /* Common                                      */
__SYSCALL(__NR_setregid, sys_setregid)
#define __NR_rename             128 /* Common                                      */
__SYSCALL(__NR_rename, sys_rename)
#define __NR_truncate           129 /* Common                                      */
__SYSCALL(__NR_truncate, sys_truncate)
#define __NR_ftruncate          130 /* Common                                      */
__SYSCALL(__NR_ftruncate, sys_ftruncate)
#define __NR_flock              131 /* Common                                      */
__SYSCALL(__NR_flock, sys_flock)
#define __NR_lstat64		132 /* Linux Specific			           */
__SYSCALL(__NR_lstat64, sys_lstat64)
#define __NR_sendto             133 /* Common                                      */
__SYSCALL(__NR_sendto, sys_sendto)
#define __NR_shutdown           134 /* Common                                      */
__SYSCALL(__NR_shutdown, sys_shutdown)
#define __NR_socketpair         135 /* Common                                      */
__SYSCALL(__NR_socketpair, sys_socketpair)
#define __NR_mkdir              136 /* Common                                      */
__SYSCALL(__NR_mkdir, sys_mkdir)
#define __NR_rmdir              137 /* Common                                      */
__SYSCALL(__NR_rmdir, sys_rmdir)
#define __NR_utimes             138 /* SunOS Specific                              */
__SYSCALL(__NR_utimes, sys_utimes)
#define __NR_stat64		139 /* Linux Specific			           */
__SYSCALL(__NR_stat64, sys_stat64)
#define __NR_sendfile64         140 /* adjtime under SunOS                         */
__SYSCALL(__NR_sendfile64, sys_sendfile64)
#define __NR_getpeername        141 /* Common                                      */
__SYSCALL(__NR_getpeername, sys_getpeername)
#define __NR_futex              142 /* gethostid under SunOS                       */
__SYSCALL(__NR_futex, sys_futex)
#define __NR_gettid             143 /* ENOSYS under SunOS                          */
__SYSCALL(__NR_gettid, sys_gettid)
#define __NR_getrlimit		144 /* Common                                      */
__SYSCALL(__NR_getrlimit, sys_getrlimit)
#define __NR_setrlimit          145 /* Common                                      */
__SYSCALL(__NR_setrlimit, sys_setrlimit)
#define __NR_pivot_root		146 /* Linux Specific, killpg under SunOS          */
__SYSCALL(__NR_pivot_root, sys_pivot_root)
#define __NR_prctl		147 /* ENOSYS under SunOS                          */
__SYSCALL(__NR_prctl, sys_prctl)
#define __NR_pciconfig_read	148 /* ENOSYS under SunOS                          */
__SYSCALL(__NR_pciconfig_read, sys_pciconfig_read)
#define __NR_pciconfig_write	149 /* ENOSYS under SunOS                          */
__SYSCALL(__NR_pciconfig_write, sys_pciconfig_write)
#define __NR_getsockname        150 /* Common                                      */
__SYSCALL(__NR_getsockname, sys_getsockname)
#define __NR_inotify_init       151 /* Linux specific                              */
__SYSCALL(__NR_inotify_init, sys_inotify_init)
#define __NR_inotify_add_watch  152 /* Linux specific                              */
__SYSCALL(__NR_inotify_add_watch, sys_inotify_add_watch)
#define __NR_poll               153 /* Common                                      */
__SYSCALL(__NR_poll, sys_poll)
#define __NR_getdents64		154 /* Linux specific				   */
__SYSCALL(__NR_getdents64, sys_getdents64)
#ifdef __32bit_syscall_numbers__
#define __NR_fcntl64		155 /* Linux sparc32 Specific                      */
__SYSCALL(__NR_fcntl64, sys_fcntl64)
#endif
#define __NR_inotify_rm_watch   156 /* Linux specific				   */
__SYSCALL(__NR_inotify_rm_watch, sys_inotify_rm_watch)
#define __NR_statfs             157 /* Common                                      */
__SYSCALL(__NR_statfs, sys_statfs)
#define __NR_fstatfs            158 /* Common                                      */
__SYSCALL(__NR_fstatfs, sys_fstatfs)
#define __NR_umount             159 /* Common                                      */
__SYSCALL(__NR_umount, sys_umount)
#define __NR_sched_set_affinity 160 /* Linux specific, async_daemon under SunOS    */
__SYSCALL(__NR_sched_set_affinity, sys_sched_set_affinity)
#define __NR_sched_get_affinity 161 /* Linux specific, getfh under SunOS           */
__SYSCALL(__NR_sched_get_affinity, sys_sched_get_affinity)
#define __NR_getdomainname      162 /* SunOS Specific                              */
__SYSCALL(__NR_getdomainname, sys_getdomainname)
#define __NR_setdomainname      163 /* Common                                      */
__SYSCALL(__NR_setdomainname, sys_setdomainname)
#ifndef __32bit_syscall_numbers__
#define __NR_utrap_install	164 /* SYSV ABI/v9 required			   */
__SYSCALL(__NR_utrap_install, sys_utrap_install)
#endif
#define __NR_quotactl           165 /* Common                                      */
__SYSCALL(__NR_quotactl, sys_quotactl)
#define __NR_set_tid_address    166 /* Linux specific, exportfs under SunOS        */
__SYSCALL(__NR_set_tid_address, sys_set_tid_address)
#define __NR_mount              167 /* Common                                      */
__SYSCALL(__NR_mount, sys_mount)
#define __NR_ustat              168 /* Common                                      */
__SYSCALL(__NR_ustat, sys_ustat)
#define __NR_setxattr           169 /* SunOS: semsys                               */
__SYSCALL(__NR_setxattr, sys_setxattr)
#define __NR_lsetxattr          170 /* SunOS: msgsys                               */
__SYSCALL(__NR_lsetxattr, sys_lsetxattr)
#define __NR_fsetxattr          171 /* SunOS: shmsys                               */
__SYSCALL(__NR_fsetxattr, sys_fsetxattr)
#define __NR_getxattr           172 /* SunOS: auditsys                             */
__SYSCALL(__NR_getxattr, sys_getxattr)
#define __NR_lgetxattr          173 /* SunOS: rfssys                               */
__SYSCALL(__NR_lgetxattr, sys_lgetxattr)
#define __NR_getdents           174 /* Common                                      */
__SYSCALL(__NR_getdents, sys_getdents)
#define __NR_setsid             175 /* Common                                      */
__SYSCALL(__NR_setsid, sys_setsid)
#define __NR_fchdir             176 /* Common                                      */
__SYSCALL(__NR_fchdir, sys_fchdir)
#define __NR_fgetxattr          177 /* SunOS: fchroot                              */
__SYSCALL(__NR_fgetxattr, sys_fgetxattr)
#define __NR_listxattr          178 /* SunOS: vpixsys                              */
__SYSCALL(__NR_listxattr, sys_listxattr)
#define __NR_llistxattr         179 /* SunOS: aioread                              */
__SYSCALL(__NR_llistxattr, sys_llistxattr)
#define __NR_flistxattr         180 /* SunOS: aiowrite                             */
__SYSCALL(__NR_flistxattr, sys_flistxattr)
#define __NR_removexattr        181 /* SunOS: aiowait                              */
__SYSCALL(__NR_removexattr, sys_removexattr)
#define __NR_lremovexattr       182 /* SunOS: aiocancel                            */
__SYSCALL(__NR_lremovexattr, sys_lremovexattr)
#define __NR_sigpending         183 /* Common                                      */
__SYSCALL(__NR_sigpending, sys_sigpending)
#define __NR_query_module	184 /* Linux Specific				   */
__SYSCALL(__NR_query_module, sys_query_module)
#define __NR_setpgid            185 /* Common                                      */
__SYSCALL(__NR_setpgid, sys_setpgid)
#define __NR_fremovexattr       186 /* SunOS: pathconf                             */
__SYSCALL(__NR_fremovexattr, sys_fremovexattr)
#define __NR_tkill              187 /* SunOS: fpathconf                            */
__SYSCALL(__NR_tkill, sys_tkill)
#define __NR_exit_group		188 /* Linux specific, sysconf undef SunOS         */
__SYSCALL(__NR_exit_group, sys_exit_group)
#define __NR_uname              189 /* Linux Specific                              */
__SYSCALL(__NR_uname, sys_uname)
#define __NR_init_module        190 /* Linux Specific                              */
__SYSCALL(__NR_init_module, sys_init_module)
#define __NR_personality        191 /* Linux Specific                              */
__SYSCALL(__NR_personality, sys_personality)
#define __NR_remap_file_pages   192 /* Linux Specific                              */
__SYSCALL(__NR_remap_file_pages, sys_remap_file_pages)
#define __NR_epoll_create       193 /* Linux Specific                              */
__SYSCALL(__NR_epoll_create, sys_epoll_create)
#define __NR_epoll_ctl          194 /* Linux Specific                              */
__SYSCALL(__NR_epoll_ctl, sys_epoll_ctl)
#define __NR_epoll_wait         195 /* Linux Specific                              */
__SYSCALL(__NR_epoll_wait, sys_epoll_wait)
#define __NR_ioprio_set         196 /* Linux Specific                              */
__SYSCALL(__NR_ioprio_set, sys_ioprio_set)
#define __NR_getppid            197 /* Linux Specific                              */
__SYSCALL(__NR_getppid, sys_getppid)
#define __NR_sigaction          198 /* Linux Specific                              */
__SYSCALL(__NR_sigaction, sys_sigaction)
#define __NR_sgetmask           199 /* Linux Specific                              */
__SYSCALL(__NR_sgetmask, sys_sgetmask)
#define __NR_ssetmask           200 /* Linux Specific                              */
__SYSCALL(__NR_ssetmask, sys_ssetmask)
#define __NR_sigsuspend         201 /* Linux Specific                              */
__SYSCALL(__NR_sigsuspend, sys_sigsuspend)
#define __NR_oldlstat           202 /* Linux Specific                              */
__SYSCALL(__NR_oldlstat, sys_oldlstat)
#define __NR_uselib             203 /* Linux Specific                              */
__SYSCALL(__NR_uselib, sys_uselib)
#define __NR_readdir            204 /* Linux Specific                              */
__SYSCALL(__NR_readdir, sys_readdir)
#define __NR_readahead          205 /* Linux Specific                              */
__SYSCALL(__NR_readahead, sys_readahead)
#define __NR_socketcall         206 /* Linux Specific                              */
__SYSCALL(__NR_socketcall, sys_socketcall)
#define __NR_syslog             207 /* Linux Specific                              */
__SYSCALL(__NR_syslog, sys_syslog)
#define __NR_lookup_dcookie     208 /* Linux Specific                              */
__SYSCALL(__NR_lookup_dcookie, sys_lookup_dcookie)
#define __NR_fadvise64          209 /* Linux Specific                              */
__SYSCALL(__NR_fadvise64, sys_fadvise64)
#define __NR_fadvise64_64       210 /* Linux Specific                              */
__SYSCALL(__NR_fadvise64_64, sys_fadvise64_64)
#define __NR_tgkill             211 /* Linux Specific                              */
__SYSCALL(__NR_tgkill, sys_tgkill)
#define __NR_waitpid            212 /* Linux Specific                              */
__SYSCALL(__NR_waitpid, sys_waitpid)
#define __NR_swapoff            213 /* Linux Specific                              */
__SYSCALL(__NR_swapoff, sys_swapoff)
#define __NR_sysinfo            214 /* Linux Specific                              */
__SYSCALL(__NR_sysinfo, sys_sysinfo)
#define __NR_ipc                215 /* Linux Specific                              */
__SYSCALL(__NR_ipc, sys_ipc)
#define __NR_sigreturn          216 /* Linux Specific                              */
__SYSCALL(__NR_sigreturn, sys_sigreturn)
#define __NR_clone              217 /* Linux Specific                              */
__SYSCALL(__NR_clone, sys_clone)
#define __NR_ioprio_get         218 /* Linux Specific                              */
__SYSCALL(__NR_ioprio_get, sys_ioprio_get)
#define __NR_adjtimex           219 /* Linux Specific                              */
__SYSCALL(__NR_adjtimex, sys_adjtimex)
#define __NR_sigprocmask        220 /* Linux Specific                              */
__SYSCALL(__NR_sigprocmask, sys_sigprocmask)
#define __NR_create_module      221 /* Linux Specific                              */
__SYSCALL(__NR_create_module, sys_create_module)
#define __NR_delete_module      222 /* Linux Specific                              */
__SYSCALL(__NR_delete_module, sys_delete_module)
#define __NR_get_kernel_syms    223 /* Linux Specific                              */
__SYSCALL(__NR_get_kernel_syms, sys_get_kernel_syms)
#define __NR_getpgid            224 /* Linux Specific                              */
__SYSCALL(__NR_getpgid, sys_getpgid)
#define __NR_bdflush            225 /* Linux Specific                              */
__SYSCALL(__NR_bdflush, sys_bdflush)
#define __NR_sysfs              226 /* Linux Specific                              */
__SYSCALL(__NR_sysfs, sys_sysfs)
#define __NR_afs_syscall        227 /* Linux Specific                              */
__SYSCALL(__NR_afs_syscall, sys_afs_syscall)
#define __NR_setfsuid           228 /* Linux Specific                              */
__SYSCALL(__NR_setfsuid, sys_setfsuid)
#define __NR_setfsgid           229 /* Linux Specific                              */
__SYSCALL(__NR_setfsgid, sys_setfsgid)
#define __NR__newselect         230 /* Linux Specific                              */
__SYSCALL(__NR__newselect, sys__newselect)
#ifdef __32bit_syscall_numbers__
#define __NR_time               231 /* Linux Specific                              */
__SYSCALL(__NR_time, sys_time)
#else
#endif
#define __NR_splice             232 /* Linux Specific                              */
__SYSCALL(__NR_splice, sys_splice)
#define __NR_stime              233 /* Linux Specific                              */
__SYSCALL(__NR_stime, sys_stime)
#define __NR_statfs64           234 /* Linux Specific                              */
__SYSCALL(__NR_statfs64, sys_statfs64)
#define __NR_fstatfs64          235 /* Linux Specific                              */
__SYSCALL(__NR_fstatfs64, sys_fstatfs64)
#define __NR__llseek            236 /* Linux Specific                              */
__SYSCALL(__NR__llseek, sys__llseek)
#define __NR_mlock              237
__SYSCALL(__NR_mlock, sys_mlock)
#define __NR_munlock            238
__SYSCALL(__NR_munlock, sys_munlock)
#define __NR_mlockall           239
__SYSCALL(__NR_mlockall, sys_mlockall)
#define __NR_munlockall         240
__SYSCALL(__NR_munlockall, sys_munlockall)
#define __NR_sched_setparam     241
__SYSCALL(__NR_sched_setparam, sys_sched_setparam)
#define __NR_sched_getparam     242
__SYSCALL(__NR_sched_getparam, sys_sched_getparam)
#define __NR_sched_setscheduler 243
__SYSCALL(__NR_sched_setscheduler, sys_sched_setscheduler)
#define __NR_sched_getscheduler 244
__SYSCALL(__NR_sched_getscheduler, sys_sched_getscheduler)
#define __NR_sched_yield        245
__SYSCALL(__NR_sched_yield, sys_sched_yield)
#define __NR_sched_get_priority_max 246
__SYSCALL(__NR_sched_get_priority_max, sys_sched_get_priority_max)
#define __NR_sched_get_priority_min 247
__SYSCALL(__NR_sched_get_priority_min, sys_sched_get_priority_min)
#define __NR_sched_rr_get_interval  248
__SYSCALL(__NR_sched_rr_get_interval, sys_sched_rr_get_interval)
#define __NR_nanosleep          249
__SYSCALL(__NR_nanosleep, sys_nanosleep)
#define __NR_mremap             250
__SYSCALL(__NR_mremap, sys_mremap)
#define __NR__sysctl            251
__SYSCALL(__NR__sysctl, sys__sysctl)
#define __NR_getsid             252
__SYSCALL(__NR_getsid, sys_getsid)
#define __NR_fdatasync          253
__SYSCALL(__NR_fdatasync, sys_fdatasync)
#define __NR_nfsservctl         254
__SYSCALL(__NR_nfsservctl, sys_nfsservctl)
#define __NR_sync_file_range	255
__SYSCALL(__NR_sync_file_range, sys_sync_file_range)
#define __NR_clock_settime	256
__SYSCALL(__NR_clock_settime, sys_clock_settime)
#define __NR_clock_gettime	257
__SYSCALL(__NR_clock_gettime, sys_clock_gettime)
#define __NR_clock_getres	258
__SYSCALL(__NR_clock_getres, sys_clock_getres)
#define __NR_clock_nanosleep	259
__SYSCALL(__NR_clock_nanosleep, sys_clock_nanosleep)
#define __NR_sched_getaffinity	260
__SYSCALL(__NR_sched_getaffinity, sys_sched_getaffinity)
#define __NR_sched_setaffinity	261
__SYSCALL(__NR_sched_setaffinity, sys_sched_setaffinity)
#define __NR_timer_settime	262
__SYSCALL(__NR_timer_settime, sys_timer_settime)
#define __NR_timer_gettime	263
__SYSCALL(__NR_timer_gettime, sys_timer_gettime)
#define __NR_timer_getoverrun	264
__SYSCALL(__NR_timer_getoverrun, sys_timer_getoverrun)
#define __NR_timer_delete	265
__SYSCALL(__NR_timer_delete, sys_timer_delete)
#define __NR_timer_create	266
__SYSCALL(__NR_timer_create, sys_timer_create)
/* #define __NR_vserver		267 Reserved for VSERVER */
#define __NR_io_setup		268
__SYSCALL(__NR_io_setup, sys_io_setup)
#define __NR_io_destroy		269
__SYSCALL(__NR_io_destroy, sys_io_destroy)
#define __NR_io_submit		270
__SYSCALL(__NR_io_submit, sys_io_submit)
#define __NR_io_cancel		271
__SYSCALL(__NR_io_cancel, sys_io_cancel)
#define __NR_io_getevents	272
__SYSCALL(__NR_io_getevents, sys_io_getevents)
#define __NR_mq_open		273
__SYSCALL(__NR_mq_open, sys_mq_open)
#define __NR_mq_unlink		274
__SYSCALL(__NR_mq_unlink, sys_mq_unlink)
#define __NR_mq_timedsend	275
__SYSCALL(__NR_mq_timedsend, sys_mq_timedsend)
#define __NR_mq_timedreceive	276
__SYSCALL(__NR_mq_timedreceive, sys_mq_timedreceive)
#define __NR_mq_notify		277
__SYSCALL(__NR_mq_notify, sys_mq_notify)
#define __NR_mq_getsetattr	278
__SYSCALL(__NR_mq_getsetattr, sys_mq_getsetattr)
#define __NR_waitid		279
__SYSCALL(__NR_waitid, sys_waitid)
#define __NR_tee		280
__SYSCALL(__NR_tee, sys_tee)
#define __NR_add_key		281
__SYSCALL(__NR_add_key, sys_add_key)
#define __NR_request_key	282
__SYSCALL(__NR_request_key, sys_request_key)
#define __NR_keyctl		283
__SYSCALL(__NR_keyctl, sys_keyctl)
#define __NR_openat		284
__SYSCALL(__NR_openat, sys_openat)
#define __NR_mkdirat		285
__SYSCALL(__NR_mkdirat, sys_mkdirat)
#define __NR_mknodat		286
__SYSCALL(__NR_mknodat, sys_mknodat)
#define __NR_fchownat		287
__SYSCALL(__NR_fchownat, sys_fchownat)
#define __NR_futimesat		288
__SYSCALL(__NR_futimesat, sys_futimesat)
#define __NR_fstatat64		289
__SYSCALL(__NR_fstatat64, sys_fstatat64)
#define __NR_unlinkat		290
__SYSCALL(__NR_unlinkat, sys_unlinkat)
#define __NR_renameat		291
__SYSCALL(__NR_renameat, sys_renameat)
#define __NR_linkat		292
__SYSCALL(__NR_linkat, sys_linkat)
#define __NR_symlinkat		293
__SYSCALL(__NR_symlinkat, sys_symlinkat)
#define __NR_readlinkat		294
__SYSCALL(__NR_readlinkat, sys_readlinkat)
#define __NR_fchmodat		295
__SYSCALL(__NR_fchmodat, sys_fchmodat)
#define __NR_faccessat		296
__SYSCALL(__NR_faccessat, sys_faccessat)
#define __NR_pselect6		297
__SYSCALL(__NR_pselect6, sys_pselect6)
#define __NR_ppoll		298
__SYSCALL(__NR_ppoll, sys_ppoll)
#define __NR_unshare		299
__SYSCALL(__NR_unshare, sys_unshare)
#define __NR_set_robust_list	300
__SYSCALL(__NR_set_robust_list, sys_set_robust_list)
#define __NR_get_robust_list	301
__SYSCALL(__NR_get_robust_list, sys_get_robust_list)
#define __NR_migrate_pages	302
__SYSCALL(__NR_migrate_pages, sys_migrate_pages)
#define __NR_mbind		303
__SYSCALL(__NR_mbind, sys_mbind)
#define __NR_get_mempolicy	304
__SYSCALL(__NR_get_mempolicy, sys_get_mempolicy)
#define __NR_set_mempolicy	305
__SYSCALL(__NR_set_mempolicy, sys_set_mempolicy)
#define __NR_kexec_load		306
__SYSCALL(__NR_kexec_load, sys_kexec_load)
#define __NR_move_pages		307
__SYSCALL(__NR_move_pages, sys_move_pages)
#define __NR_getcpu		308
__SYSCALL(__NR_getcpu, sys_getcpu)
#define __NR_epoll_pwait	309
__SYSCALL(__NR_epoll_pwait, sys_epoll_pwait)
#define __NR_utimensat		310
__SYSCALL(__NR_utimensat, sys_utimensat)
#define __NR_signalfd		311
__SYSCALL(__NR_signalfd, sys_signalfd)
#define __NR_timerfd_create	312
__SYSCALL(__NR_timerfd_create, sys_timerfd_create)
#define __NR_eventfd		313
__SYSCALL(__NR_eventfd, sys_eventfd)
#define __NR_fallocate		314
__SYSCALL(__NR_fallocate, sys_fallocate)
#define __NR_timerfd_settime	315
__SYSCALL(__NR_timerfd_settime, sys_timerfd_settime)
#define __NR_timerfd_gettime	316
__SYSCALL(__NR_timerfd_gettime, sys_timerfd_gettime)
#define __NR_signalfd4		317
__SYSCALL(__NR_signalfd4, sys_signalfd4)
#define __NR_eventfd2		318
__SYSCALL(__NR_eventfd2, sys_eventfd2)
#define __NR_epoll_create1	319
__SYSCALL(__NR_epoll_create1, sys_epoll_create1)
#define __NR_dup3		320
__SYSCALL(__NR_dup3, sys_dup3)
#define __NR_pipe2		321
__SYSCALL(__NR_pipe2, sys_pipe2)
#define __NR_inotify_init1	322
__SYSCALL(__NR_inotify_init1, sys_inotify_init1)
#define __NR_accept4		323
__SYSCALL(__NR_accept4, sys_accept4)
#define __NR_preadv		324
__SYSCALL(__NR_preadv, sys_preadv)
#define __NR_pwritev		325
__SYSCALL(__NR_pwritev, sys_pwritev)
#define __NR_rt_tgsigqueueinfo	326
__SYSCALL(__NR_rt_tgsigqueueinfo, sys_rt_tgsigqueueinfo)
#define __NR_perf_event_open	327
__SYSCALL(__NR_perf_event_open, sys_perf_event_open)
#define __NR_recvmmsg		328
__SYSCALL(__NR_recvmmsg, sys_recvmmsg)
#define __NR_fanotify_init	329
__SYSCALL(__NR_fanotify_init, sys_fanotify_init)
#define __NR_fanotify_mark	330
__SYSCALL(__NR_fanotify_mark, sys_fanotify_mark)
#define __NR_prlimit64		331
__SYSCALL(__NR_prlimit64, sys_prlimit64)
#define __NR_name_to_handle_at	332
__SYSCALL(__NR_name_to_handle_at, sys_name_to_handle_at)
#define __NR_open_by_handle_at	333
__SYSCALL(__NR_open_by_handle_at, sys_open_by_handle_at)
#define __NR_clock_adjtime	334
__SYSCALL(__NR_clock_adjtime, sys_clock_adjtime)
#define __NR_syncfs		335
__SYSCALL(__NR_syncfs, sys_syncfs)
#define __NR_sendmmsg		336
__SYSCALL(__NR_sendmmsg, sys_sendmmsg)
#define __NR_setns		337
__SYSCALL(__NR_setns, sys_setns)
#define __NR_process_vm_readv	338
__SYSCALL(__NR_process_vm_readv, sys_process_vm_readv)
#define __NR_process_vm_writev	339
__SYSCALL(__NR_process_vm_writev, sys_process_vm_writev)
#define __NR_kern_features	340
__SYSCALL(__NR_kern_features, sys_kern_features)
#define __NR_kcmp		341
__SYSCALL(__NR_kcmp, sys_kcmp)
#define __NR_finit_module	342
__SYSCALL(__NR_finit_module, sys_finit_module)

#endif /* ROACH_SPARC_SYSCALL_NAMES */
