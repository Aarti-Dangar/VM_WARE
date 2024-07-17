//task_7:Extend above LKM to Sort the integers in decreasing order and print them. Define your own function or find & use the one available in Linux  headers.
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/sort.h>

#define MY_ARRAY_SIZE 10

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aarti");
MODULE_DESCRIPTION("A module to accept an array of integers as a command-line argument, sort them, and print them");

static int arr[MY_ARRAY_SIZE];
static int arr_argc = 0;

module_param_array(arr, int, &arr_argc, 0000);
MODULE_PARM_DESC(arr, "An array of integers");

static int cmp_func(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

static int __init array_param_init(void) {
    int i;

    if (arr_argc != MY_ARRAY_SIZE) {
        pr_info("Expected exactly %d elements, but got %d\n", MY_ARRAY_SIZE, arr_argc);
        return 0;
    }

    sort(arr, MY_ARRAY_SIZE, sizeof(int), cmp_func, NULL);

    pr_info("Sorted array elements in decreasing order are:\n");
    for (i = 0; i < MY_ARRAY_SIZE; i++) {
        pr_info("arr[%d] = %d\n", i, arr[i]);
    }
    return 0;
}

static void __exit array_param_exit(void) {
    pr_info("Exiting module\n");
}

module_init(array_param_init);
module_exit(array_param_exit);

