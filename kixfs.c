/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

static struct file_system_type kixfs_fs_type;


static int kixfs_fill_super(struct super_block *sb, void *data, int silent)
{
        int ret = -EINVAL;

        return ret;
}

static struct dentry *kixfs_mount(struct file_system_type *fs_type, int flags,
                                  const char *dev_name, void *data)
{
        return mount_bdev(fs_type, flags, dev_name, data, kixfs_fill_super);
}

static void kixfs_kill_super_block(struct super_block *sb)
{
}

static struct file_system_type kixfs_fs_type = {
        .owner = THIS_MODULE,
        .name = "kixfs",
        .mount = kixfs_mount,
        .kill_sb = kixfs_kill_super_block,
        .fs_flags = FS_REQUIRES_DEV
};

MODULE_ALIAS_FS("kixfs");

static int __init kixfs_init(void)
{
        int ret = 0;

        ret = register_filesystem(&kixfs_fs_type);
        if (ret)
                goto err;

        printk(KERN_INFO "[kixfs] Register filesystem.\n");
        printk(KERN_INFO "kixfs - The kix filesystem.\n");
        return ret;

err:
        printk(KERN_ERR "Failed to register kixfs: %d.\n", ret);
        return ret;
}

static void __exit kixfs_exit(void)
{
        int ret;

        ret = unregister_filesystem(&kixfs_fs_type);
        if (ret)
                printk(KERN_ERR "Failed to unregister kixfs: %d.\n", ret);
        else
                printk(KERN_INFO "[kixfs] Unregister Filesystem.\n");
}


module_init(kixfs_init);
module_exit(kixfs_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Partha Susarla");
