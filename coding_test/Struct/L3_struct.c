#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

struct L3
{
	unsigned int version;
	unsigned int source_addr;
};

int init_hello(void)
{
	uint32_t *sip = NULL;
	struct L3 l3 = {0,};
	memset(&l3, 0, sizeof(l3));
	sip = &l3.source_addr;

	return 0;
}

void exit_hello(void)
{
	printk(KERN_ALERT "Goodbye World\n");
}

module_init(init_hello);
module_exit(exit_hello);
MODULE_LICENSE("GPL");
