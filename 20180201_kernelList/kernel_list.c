#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/list.h>

struct Node {
	int data;
	struct list_head list;
};

LIST_HEAD(Node_head);

static void insert(int data)
{
	struct Node *new = (struct Node*)kmalloc(sizeof(struct Node), GFP_KERNEL);
	new->data = data;
	list_add_tail(&new->list, &Node_head);
}

static void delete(int data)
{

	struct Node *p, *tmp;
	list_for_each_entry_safe(p, tmp, &Node_head, list)
	{
		if(p->data == data)
		{
			printk("delete data (%d)\n", p->data);
			list_del(&p->list);
			kfree(p);
		}
	}
}

static void print(void)
{
	struct Node *p;
	list_for_each_entry(p, &Node_head, list)
	{
		printk("data (%d)", p->data);
		if((p->list).next != &Node_head)
		{
			printk("->");
		}
	}
	printk("\n");
}

int __init init_hello(void)
{
	printk("===kernel list api test===\n");
	insert(10);
	insert(20);
	insert(30);
	print();

	delete(20);
	print();

	return 0;
}

void __exit exit_hello(void)
{
	printk(KERN_ALERT "Goodbye World\n");
}

module_init(init_hello);
module_exit(exit_hello);
MODULE_LICENSE("GPL");
