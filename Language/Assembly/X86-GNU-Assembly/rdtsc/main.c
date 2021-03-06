/*
 * RDTSC - Read Time-Stamp Counter [x86]
 *
 * (C) 2020.10.02 BuddyZhang1 <buddy.zhang@aliyun.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

/* mdelay */
#include <linux/delay.h>

/*
 * RDTSC -- Read Time-Stamp Counter
 *
 * Description
 * Reads the current value of the processor's time-stamp counter (a 64-bit 
 * MSR) into the EDX:EAX registers. The EDX register is loaded with the 
 * high-order 32 bits of the MSR and the EAX register is loaded with the 
 * low-order 32 bits. (On processors that support the Intel 64 architecture,
 * the high-order 32 bits of each of RAX and RDX are cleared.)
 *
 * The processor monotonically increments the time-stamp counter MSR every
 * clock cycle and resets it to 0 whenever the processor is reset. The time
 * stamp disable (TSD) flag in register CR4 restricts the use of the RDTSC
 * instruction as follows. When the flag is clear, the RDTSC instruction can
 * be executed at any privilege level; when the flag is set, the instruction
 * can only be executed at privilege level 0
 * 
 * The time-stamp counter can also be read with RDMSR instruction, when execu-
 * ting at privilege level 0. The RDTSC instruction is not a serializing
 * instruction. It does not necessarily wait until all previous instruction
 * have been executed before reading the counter. Similarly, subsequent 
 * instructions may begin execution before the read operation is performed.
 * If software requires RDTSC to be executed only after all previous
 * instruction have completed locally, it can either use RDTSCP (if the
 * processor supports that instruction) or execute the sequence LFENCE;RDTSC.
 */

/*
 * both i386 and x86_64 returns 64-bit value in edx:eax, but gcc's "A"
 * constraint has different meanings. For i386, "A" means exactly
 * edx:eax, while for x86_64 it doesn't mean rdx:rax or edx:eax. Instead,
 * it means rax *or* rdx.
 */
#ifdef CONFIG_X86_64
#define DECLARE_ARGS(val, low, high)	unsigned low, high
#define EAX_EDX_VAL(val, low, high)	((low) | ((u64)(high) << 32))
#define EAX_EDX_ARGS(val, low, high)	"a" (low), "d" (high)
#define EAX_EDX_RET(val, low, high)	"=a" (low), "=d" (high)
#else
#define DECLARE_ARGS(val, low, high)	unsigned long long val
#define EAX_EDX_VAL(val, low, high)	(val)
#define EAX_EDX_ARGS(val, low, high)	"A" (val)
#define EAX_EDX_RET(val, low, high)	"=A" (val)
#endif

static __always_inline unsigned long long __native_read_tsc(void)
{
	DECLARE_ARGS(val, low, high);

	asm volatile("rdtsc" : EAX_EDX_RET(val, low, high));

	return EAX_EDX_VAL(val, low, high);
}

#define rdtscl(low)	((low) = (u32)__native_read_tsc())
#define rdtscll(val)	((val) = __native_read_tsc())

/* Module initialize entry */
static int __init BiscuitOS_init(void)
{
	u64 tsc_u64;
	u32 tsc_low;
	u64 tsc_a, tsc_b, result, mod;

	/* Read TSC 64bit contents */
	rdtscll(tsc_u64);
	printk("TSC 64bit: %#llx\n", tsc_u64);
	/* Read TSC low-order 32bit contents */
	rdtscl(tsc_low);
	printk("TSC low-order 32bit: %#x\n", tsc_low);

	/* CPU frequency */
	rdtscll(tsc_a);
	mdelay(1000);
	rdtscll(tsc_b);
	result = tsc_b - tsc_a;
	/* 64bit div */
	mod = do_div(result, 1 * 1024 * 1024);
	
	printk("CPU %d.%d MHz\n", result, mod);
	printk("Hello modules on BiscuitOS\n");

	return 0;
}

/* Module exit entry */
static void __exit BiscuitOS_exit(void)
{
}

module_init(BiscuitOS_init);
module_exit(BiscuitOS_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("BiscuitOS <buddy.zhang@aliyun.com>");
MODULE_DESCRIPTION("Common Device driver on BiscuitOS");
