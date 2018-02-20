#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

// ================= old ver struct =================
/*
struct L2
{
	unsigned char[6] des_addr;
	unsigned char[6] source_addr;
	unsigned short int type;
	void* data;
	unsigned int fcs;
};

struct L3
{
	unsigned int version:4
		unsigned int IHL:4
		unsigned char tos;
	unsigned short total_length;
	unsigned short identification;
	unsigned short fragment_offset;
	unsigned char ttl;
	unsigned char protocol;
	unsigned short checksum;
	unsigned int sa
		unsigned int da
		unsigned int oprion
		void* data;
};

struct L7
{
	unsigned short source_port;
	unsigned short dest_port;
	unsigned int seq_number;
	unsigned int ack_number;
	unsigned char data_offset:4;
	unsigned char reserved:4;
	unsigned char cwr:1;
	unsigned char ecn:1;
	unsigned char urg:1;
	unsigned char ack:1;
	unsigned char psh:1;
	unsigned char rst:1;
	unsigned char syn:1;
	unsigned char fin:1;
	unsigned short window_size;
	unsigned short checksum;
	unsigned short urgent pointer;
};
*/
// ================= new ver struct =================

//Ethernet Header
struct L2
{
	unsigned char	dest_addr[6];
	unsigned char	source_addr[6];
	__be16	type;
	void*	data;
	__be32	fcs;

};

//IP Header
struct L3 
{
	__u8	version:4,
		ihl:4;
	__u8	tos;
	__be16	totla_len;
	__be16	identification;
	__be16	fragment_offset;
	__u8	ttl;
	__u8	protocol;
	__be16	checksum;
	__be32	sa;
	__be32	da;
	__be32	option;
	void* 	data;
};

//TCP Header
struct L7
{
	__be16	source_port;
	__be16	dest_post;
	__be32	seq_num;
	__be32	ack_num;
	__u16	data_offset:4,
		reserved:4,
		cwr:1,
		ecn:1,
		urg:1,
		ack:1,
		psh:1,
		rst:1,
		syn:1,
		fin:1;
	__be16	window_size;
	__be16	checksum;
	__be16	urgent_pointer;
};

int init_hello(void)
{
	struct L2	*l2;
	struct L3	*l3;
	struct L7	*l7;
	
	printk("struct C file!!\n");
	return 0;
}

void exit_hello(void)
{
	printk(KERN_ALERT "struct GOOD BYEBYEBYE ~\n");
}

module_init(init_hello);
module_exit(exit_hello);
MODULE_LICENSE("GPL");
