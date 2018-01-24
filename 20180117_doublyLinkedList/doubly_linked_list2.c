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

/*
struct List
{
	Node *head;
	Node *tail;
};
*/

static void init(void)
{
	head = NULL;
	tail = NULL;
}

static void insert(int data)
{
	struct Node* new = (struct Node*)kmalloc(sizeof(struct Node),GFP_KERNEL);
	new->data = data;
	new->next = NULL;
	new->prev = NULL;

	if (head != NULL)
	{
		tail->next = new;
		new->prev = tail;
		tail = new;

	}
	else
	{
		head = new;
		tail = new;
	}
}

static void delete(int data)
{
	struct Node* p = head;

	//지우고 싶은 node와 일치 할때까지 다음칸으로 이동하며
	while( p != NULL )
	{
		if (p->data == data)
			break;
		p = p->next;
	}

	//지우고 싶은 node인 경우 아래를 실행.
	if ( p == head )
	{
		head = head->next;
		p->next->prev = NULL;
	}
	else if ( p == tail )
	{
		tail = tail->prev;
		p->prev->next = NULL;
	}
	else
	{
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
}

static void print(void)
{
	struct Node* p = head;
	while(p != tail)
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
