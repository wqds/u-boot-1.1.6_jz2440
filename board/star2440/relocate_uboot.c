#include <common.h>
#include <s3c2410.h>


#define TACLS  0
#define TWRPH0 1
#define TWRPH1 0
#define REST_CMD 0xff
#define STATE_CMD 0x70
#define READ_CMD1 0x00
#define READ_CMD2 0x30
#define PAGE_SIZE 2048

void nand_flash_init(void);
void nand_read(unsigned int start_page_num, unsigned char *dest_addr, unsigned int page_length);
void nand_send_cmd(unsigned char cmd);
void nand_send_addr(unsigned int page_num);
void nand_select_chip(unsigned int state);
void nand_wait_idle(void);
void nand_flash_reset(void);
int is_in_norflash(void);



void nand_flash_init(void)
{
	S3C2440_NAND *nand_ctl = (S3C2440_NAND *)0x4e000000;
	nand_ctl->NFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4);
	nand_ctl->NFCONT = (0<<13)|(0<<12)|(0<<10)|(0<<9)|(0<<8)|(1<<6)|(1<<5)|(1<<4)|(1<<1)|(1<<0);
	nand_flash_reset();
	//NFCONF = 0x100;
	//NFCONT = 0x071;
	//nand_flash_reset();
}


void nand_read(unsigned int start_page_num, unsigned char *dest_addr, unsigned int page_length)
{
	S3C2440_NAND *nand_ctl = (S3C2440_NAND *)0x4e000000;
	unsigned int i,j;
	//volatile unsigned char *data = (volatile unsigned char *)&NFDATA;
	for(j = 0; j < page_length; j++){
		nand_select_chip(1);
		nand_send_cmd(READ_CMD1);
		nand_send_addr(start_page_num + j);
		nand_send_cmd(READ_CMD2);
		nand_wait_idle();
		
		for(i = 0; i < PAGE_SIZE; i++){
			*dest_addr++ = nand_ctl->NFDATA;
			//*dest_addr++ = *data;
		}
		nand_select_chip(0);
	}
}

void nand_send_cmd(unsigned char cmd)
{
	S3C2440_NAND *nand_ctl = (S3C2440_NAND *)0x4e000000;
	nand_ctl->NFCMD = cmd;
}

void nand_send_addr(unsigned int page_num)
{
	S3C2440_NAND *nand_ctl = (S3C2440_NAND *)0x4e000000;
	nand_ctl->NFADDR = 0x00;
	nand_ctl->NFADDR = 0x00;
	nand_ctl->NFADDR = page_num & 0xff;
	nand_ctl->NFADDR = (page_num>>8) & 0xff;
	nand_ctl->NFADDR = (page_num>>16) & 0xff;
}

//state: 0 失能片选，1 使能片选
void nand_select_chip(unsigned int state)
{
	S3C2440_NAND *nand_ctl = (S3C2440_NAND *)0x4e000000;
	if(!state)
		nand_ctl->NFCONT |= (1<<1);
	else
		nand_ctl->NFCONT &= ~(1<<1);
}

void nand_wait_idle(void)
{
	S3C2440_NAND *nand_ctl = (S3C2440_NAND *)0x4e000000;
	while(!(nand_ctl->NFSTAT & 0x01));
}

void nand_flash_reset(void)
{
	nand_select_chip(1);
	nand_send_cmd(REST_CMD);
	nand_wait_idle();
	nand_select_chip(0);
}

int is_in_norflash(void)
{
	volatile unsigned int *test = (volatile unsigned int *) 0x00;
	int p = *test;
	*test = 0x123876;
	if(*test == 0x123876){
		*test = p;
		return 0;
	}
	else
		return 1;
}

void copy_code_to_sdarm(unsigned char *src_addr, unsigned char *dest_addr, unsigned int length)
{
	
	unsigned int start_page_num = 0, page_length = 0, i = 0;
	/*if(is_in_norflash()){
		for(i = 0; i < length; i++)
			*dest_addr++ = *src_addr++;
	}
	else{*/
		start_page_num = (unsigned int)src_addr / PAGE_SIZE;
		page_length    = length / PAGE_SIZE ;
		nand_flash_init();
		nand_read(start_page_num, dest_addr, page_length);
	//}
}

