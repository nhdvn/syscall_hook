#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/unistd.h>
#include <asm/current.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/delay.h>
#include <asm/paravirt.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("18120019_Nguyen_Hoang_Dung - 18120052_Le_Hanh_Linh");
MODULE_DESCRIPTION("Syscall_Hook");

unsigned long *sys_call_table;

asmlinkage int (*original_write) (unsigned int, const char __user *, size_t);
asmlinkage int (*original_open) (const char __user *, int, mode_t);


asmlinkage int new_write(unsigned int fd, const char __user *buf, size_t nBytes)
{
    if (strcmp(current->comm, "peterpan") == 0)
    {
	    printk(KERN_INFO "HOOK DETECTED: PROCESS NAME [%s] WITH FILE DISCRIPTION [%d] WRITING [%d] BYTES \n", current->comm, fd, (int)nBytes);
    }

	return original_write(fd, buf, nBytes);	
}

asmlinkage int new_open(const char __user * filename, int flags, mode_t mode)
{
    if (strcmp(current->comm, "peterpan") == 0)
    {
        printk( KERN_INFO "HOOK DETECTED: PROCESS NAME [%s] OPENING FILE [%s] \n", current->comm, filename);
    }

    return original_open(filename, flags, mode);
}

static void find_sys_call_table(void)
{
    unsigned long int offset;

    for (offset = PAGE_OFFSET; offset < ULLONG_MAX; offset += sizeof(void *))
    {
		sys_call_table = ( unsigned long *) offset;

		if (( unsigned long * ) sys_call_table[ __NR_close ] == ( unsigned long * ) sys_close) break;
    }

	printk(KERN_EMERG "HOOK DETECTED: SYSCALL TABLE ADDRESS: %p \n", sys_call_table);
}

static void enable_writing( void )
{
    write_cr0( read_cr0() & ~0x10000 );
}

static void disable_writing( void )
{
    write_cr0( read_cr0() | 0x10000 );
}

static int __init init_mod( void )
{
    find_sys_call_table();

    original_write = ( void * ) sys_call_table[ __NR_write ];
    original_open = ( void * ) sys_call_table[ __NR_open ];
  
    enable_writing();
    
    sys_call_table[ __NR_write ] = (unsigned long *) new_write;
    sys_call_table[ __NR_open ] = (unsigned long *) new_open;
  
    disable_writing();

    return 0;
}

static void __exit exit_mod( void )
{
    enable_writing();
  
    sys_call_table[ __NR_write ] = ( unsigned long * ) original_write;
    sys_call_table[ __NR_open ] = ( unsigned long * ) original_open;

    disable_writing();
}

module_init( init_mod );
module_exit( exit_mod );