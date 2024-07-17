//Which function to call for measuring how much time required to insert new node in linked list (ex.8). Implement LKM to get the time in nanoseconds.
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/init.h>
#include <linux/minmax.h>
#include <linux/moduleparam.h>
#include <linux/version.h>
#include <linux/sort.h>
#include <linux/random.h>
#include <linux/slab.h>
#include <linux/timekeeping.h>
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aarti");
MODULE_DESCRIPTION("Linked list module");
 
static int len=10;
 
module_param(len, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(len, "A integer value");
 
typedef struct list{
	int num;
	int sqrt;
	struct list *next;
}LIST;
 
LIST *head=NULL,*last=NULL,*tmp=NULL,*new=NULL;
 
unsigned int sqrt_int(unsigned int number) {
    unsigned int result = 0;
    unsigned int bit = 1u << 30; // The second-to-top bit is set
 
    // "bit" starts at the highest power of four <= the argument.
    while (bit > number)
        bit >>= 2;
 
    while (bit != 0) {
        if (number >= result + bit) {
            number -= result + bit;
            result = (result >> 1) + bit;
        } else {
            result >>= 1;
        }
        bit >>= 2;
    }
 
    return result;
}
 
static LIST* createnode(void)
{
	LIST *newnode=kmalloc(sizeof(LIST),GFP_DMA);
	newnode->num=get_random_int();
	if(newnode->num<0)
		newnode->num=-newnode->num;
	newnode->sqrt=sqrt_int(newnode->num);
	return newnode;
}
static LIST* reverse_list(LIST *head)
{
	LIST *T,*prev,*next_node;
        prev=NULL;
        T=head;
        while(T!=NULL)
        {
                next_node=T->next;
                T->next=prev;
                prev=T;
                T=next_node;
        }
	head=prev;
	return head;
}
 
static void print_list(LIST *tmp)
{
	while(tmp!=NULL)
	{
		pr_info("num:%d sqrt:%d\n",tmp->num,tmp->sqrt);
		tmp=tmp->next;
	}
}
 
static int __init start_fun(void)
{
	int i;
	ktime_t start, end;
	s64 elapsed;
	for(i=0;i<len;i++)
	{
		start = ktime_get();
		new=createnode();
		if(head==NULL)
			head=new;
		else
			last->next=new;
		last=new;
		end = ktime_get();
		elapsed = ktime_to_ns(ktime_sub(end, start));
		pr_info("node %d Time: %lld ns\n",i+1, elapsed);
	}
	pr_info("List is printing\n");
	print_list(head);
	head=reverse_list(head);
	pr_info("List is printing in reverse order\n");
	print_list(head);
 
	pr_info("Successfully performed all the tasks\n");
	return 0;
}
 
static void __exit stop_fun(void)
{
	//deleting nodes and freed memory
	while(head!=NULL)
        {
		tmp=head;
                head=head->next;
		kfree(tmp);
        }
	pr_info("deleted nodes and freed memory\n");
	pr_info("Linked list module is unloaded\n");
}
 
module_init(start_fun);
module_exit(stop_fun);
