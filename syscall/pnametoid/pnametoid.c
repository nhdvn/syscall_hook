#include <linux/syscalls.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/tty.h>
#include <linux/string.h>

asmlinkage long sys_pnametoid(char *name)
{
    char buffer[32];

    strncpy_from_user(buffer, name, sizeof buffer);

    printk("pnametoid: search pname %s", buffer);

    struct task_struct *task;
    
    int pid = -1;

    for_each_process(task)
    {
        if (strcmp(task->comm, buffer) == 0)
        {
            pid = task->pid;
        }
    }

    printk("pnametoid: return result %ld", (long)pid);

    return (long)pid;
}
