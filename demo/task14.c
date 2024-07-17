//task_14implement LKM to print  the current date and time. Keep the GMT time zones in mind.
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/time.h>
#include <linux/rtc.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aarti");
MODULE_DESCRIPTION("A simple kernel module to print the current date and time in GMT.");
static int  __init start(void)
{
	 struct timespec64 ts;
    struct rtc_time tm;

    ktime_get_real_ts64(&ts);  // Get the current time in seconds and nanoseconds
    rtc_time64_to_tm(ts.tv_sec, &tm);  // Convert to rtc_time structure

    pr_info("Current GMT date and time: %04d-%02d-%02d %02d:%02d:%02d\n",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
            tm.tm_hour, tm.tm_min, tm.tm_sec);

    return 0;
}
static void  __exit stop(void)
{
    pr_info("Goodbye from the LKM!\n");
}

module_init(start);
module_exit(stop);
	
