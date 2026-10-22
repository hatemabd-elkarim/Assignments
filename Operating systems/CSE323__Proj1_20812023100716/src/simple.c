#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <linux/jiffies.h>
#include <asm/param.h>

static unsigned long start_jiffies;

/* Called when the module is loaded. */
static int __init simple_init(void)
{
	start_jiffies = jiffies;
	printk(KERN_INFO "Loading Kernel Module\n");

	/* Step 1: golden ratio prime (older kernels) or 64-bit golden ratio (newer) */
#ifdef GOLDEN_RATIO_PRIME
	printk(KERN_INFO "GOLDEN_RATIO_PRIME = %llu\n", (unsigned long long)GOLDEN_RATIO_PRIME);
#else
	printk(KERN_INFO "GOLDEN_RATIO_64 = %llu\n", (unsigned long long)GOLDEN_RATIO_64);
#endif

	/* Timer values */
	printk(KERN_INFO "jiffies = %lu, HZ = %d\n", jiffies, HZ);
	return 0;
}

/* Called when the module is removed. */
static void __exit simple_exit(void)
{
	printk(KERN_INFO "GCD(3300, 24) = %lu\n", gcd(3300UL, 24UL));
	printk(KERN_INFO "jiffies = %lu\n", jiffies);
	printk(KERN_INFO "Seconds since load = %lu\n", (jiffies - start_jiffies) / HZ);
	printk(KERN_INFO "Removing Kernel Module\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("hatemabd-elkarim");
