#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

struct Node
{
	int data;
	struct Node *prev;
	struct Node *next;
};
struct Node *head, *tail;

static void init(void)
{
	head = (struct Node*)kmalloc(sizeof(struct Node),GFP_KERNEL);
	tail = (struct Node*)kmalloc(sizeof(struct Node),GFP_KERNEL);
	head->data = 0;
	tail->data = 0;

	head->next = tail;
	head->prev = head;
	tail->prev = head;
	tail->next = tail;
}

static void insert(int data)
{
	struct Node* new = (struct Node*)kmalloc(sizeof(struct Node),GFP_KERNEL);
	new->data = data;
	new->next = NULL;
	new->prev = NULL;

	if ( head->data == 0 )
	{
		head = new;
	}

	tail->prev->next = new;
	new->prev = tail->prev;
	tail->prev = new;
	new->next = tail;
}

static void delete(int data)
{
	struct Node* p = head;
	while(p->next != tail)
	{
		if(p->data == data)
		{
			p->next->prev = p->prev;
			p->prev->next = p->next;
		}
		p = p->next;
	}
}

static void print(void)
{
	struct Node* p;
	p = head;
	while(p->next != tail)
	{
		printk("data (%d)->", p->data);
		p = p->next;
	}
	printk("data (%d)\n", p->data);
}

int init_hello(void)
{
	init();

	insert(10);
	insert(20);
	insert(30);
	insert(40);
	print();
	
	delete(20);
	print();

	return 0;
}

void exit_hello(void)
{
	printk(KERN_ALERT "Goodbye World\n");
}

module_init(init_hello);
module_exit(exit_hello);
MODULE_LICENSE("GPL");
