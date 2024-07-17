//task_17:Implement LKM to  get a pointer to the task that is currently executing on the current CPU i.e. calculate the value of current macro.
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>

// Module metadata
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aarti");
MODULE_DESCRIPTION("A simple example of getting the current task");

// Function to display current task information
static int __init start(void)
{
    struct task_struct *task = current; // Get the current task

    pr_info("current_task: Module loaded\n");
    pr_info("current_task: Current task info:\n");
    pr_info("current_task: PID: %d\n", task->pid);
    pr_info("current_task: Name: %s\n", task->comm);

    return 0;
}

static void __exit stop(void)
{
    pr_info("current_task: Module unloaded\n");
}

module_init(start);
module_exit(stop);

