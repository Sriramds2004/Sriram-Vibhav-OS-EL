

//This is the systemcall implementation

#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/crypto.h>
#include <crypto/hash.h>
#include <linux/slab.h>

#define MAX_FILE_PATH_LEN 256
#define SHA256_DIGEST_SIZE 32

SYSCALL_DEFINE6(hash_file, const char __user *, filename, size_t, filename_len, unsigned char __user *, hash_output)
{
    struct file *file;
    loff_t pos = 0;
    ssize_t len;
    char *buf;
    struct crypto_shash *tfm;
    struct shash_desc *desc;
    unsigned char hash[SHA256_DIGEST_SIZE];
    int ret = 0;

    // Allocate buffer
    buf = kmalloc(PAGE_SIZE, GFP_KERNEL);
    if (!buf)
        return -ENOMEM;

    // Open the file
    file = filp_open(filename, O_RDONLY, 0);
    if (IS_ERR(file)) {
        ret = PTR_ERR(file);
        goto out_free_buf;
    }

    // Allocate hash transformation object
    tfm = crypto_alloc_shash("sha256", 0, 0);
    if (IS_ERR(tfm)) {
        ret = PTR_ERR(tfm);
        goto out_close_file;
    }

    // Allocate and initialize shash descriptor
    desc = kmalloc(sizeof(struct shash_desc) + crypto_shash_descsize(tfm), GFP_KERNEL);
    if (!desc) {
        ret = -ENOMEM;
        goto out_free_tfm;
    }
    desc->tfm = tfm;
    ret = crypto_shash_init(desc);
    if (ret) {
        goto out_free_desc;
    }

    // Read file content and update hash
    while ((len = kernel_read(file, buf, PAGE_SIZE, &pos)) > 0) {
        ret = crypto_shash_update(desc, buf, len);
        if (ret) {
            goto out_free_desc;
        }
    }
    if (len < 0) {
        ret = len;
        goto out_free_desc;
    }

    // Finalize hash
    ret = crypto_shash_final(desc, hash);
    if (ret) {
        goto out_free_desc;
    }

    // Copy hash to user space
    if (copy_to_user(hash_output, hash, SHA256_DIGEST_SIZE)) {
        ret = -EFAULT;
        goto out_free_desc;
    }

out_free_desc:
    kfree(desc);
out_free_tfm:
    crypto_free_shash(tfm);
out_close_file:
    filp_close(file, NULL);
out_free_buf:
    kfree(buf);

    return ret;
}
