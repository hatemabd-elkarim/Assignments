#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/jiffies.h>
#include <linux/version.h>
#include <linux/uaccess.h>

#define BUFFER_SIZE 128
#define PROC_NAME "jiffies"

/* Called each time /proc/jiffies is read. */
static ssize_t proc_read(struct file *file, char __user *usr_buf,
			 size_t count, loff_t *pos)
{
	char buffer[BUFFER_SIZE];
	int len;

	/* Already returned the data once: signal EOF. */
	if (*pos > 0)
		return 0;

	len = snprintf(buffer, BUFFER_SIZE, "%lu\n", jiffies);

	/* copy kernel buffer to user space */
	if (copy_to_user(usr_buf, buffer, len))
		return -EFAULT;

	*pos = len;
	return len;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0)
static const struct proc_ops my_proc_ops = {
	.proc_read = proc_read,
};
#else
static const struct file_operations my_proc_ops = {
	.owner = THIS_MODULE,
	.read = proc_read,
};
#endif

static int __init proc_init(void)
{
	proc_create(PROC_NAME, 0444, NULL, &my_proc_ops);
	printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
	return 0;
}

static void __exit proc_exit(void)
{
	remove_proc_entry(PROC_NAME, NULL);
	printk(KERN_INFO "/proc/%s removed\n", PROC_NAME);
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("/proc/jiffies module");
MODULE_AUTHOR("hatemabd-elkarim");
