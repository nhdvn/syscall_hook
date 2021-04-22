#include <linux/syscalls.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/tty.h>
#include <linux/string.h>

#define LENKERNEL 60

asmlinkage long sys_pidtoname(int pid, char *buffer, int len)
{
    struct task_struct *task;

    char *process_name = kmalloc(LENKERNEL, GFP_KERNEL);

    printk("pidtoname: search pid %d", pid);

    for_each_process(task)
    {
        if (task_pid_nr(task) == pid)
        {
            strcpy(process_name, task->comm);

            if (strlen(task->comm) <= LENKERNEL)
            {
                process_name[strlen(task->comm)] = 0;
            }

            printk("pidtoname: found pname %s", process_name);

            copy_to_user(buffer, process_name, len - 1);

            if (strlen(process_name) > len - 1)
            {
                printk("pidtoname: plength %d", strlen(process_name));

                return strlen(process_name);
            }
            else return 0;
        }
    }

    printk("pidtoname: unknown pid");

    return -1;
}
