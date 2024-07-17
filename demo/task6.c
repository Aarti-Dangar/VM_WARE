// task_6:Implement  LKM a module to accept an array of integers as the command-line argument. The number of elements should be fixed (say 10) and the module should exit after printing suitable message if the number of elements passed is not equal to 10; print the integers in the array otherwise.
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

#define my_ARRAY_SIZE 10

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A module to accept an array of integers as a command-line argument");

static int arr[my_ARRAY_SIZE];
static int arr_argc = 0;

module_param_array(arr, int, &arr_argc, 0000);
MODULE_PARM_DESC(arr, "An array of integers");

static int __init array_param_init(void) {
    int i;

    if (arr_argc != my_ARRAY_SIZE) {
        pr_info("Expected exactly %d elements, but got %d\n", my_ARRAY_SIZE, arr_argc);
        return 0;
    }

    pr_info("Array elements are:\n");
    for (i = 0; i < my_ARRAY_SIZE; i++) {
        pr_info("arr[%d] = %d\n", i, arr[i]);
    }
    return 0;
}

static void __exit array_param_exit(void) {
    pr_info("Exiting module\n");
}

module_init(array_param_init);
module_exit(array_param_exit);

