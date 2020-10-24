#ifndef _FILESYS_H
#define _FILESYS_H
#include "types.h"

#define BLOCK_SIZE 4096
#define BLOCK_SIZE_LOG_2 12
#define BLOCK_MASK 0xFFF
#define FNAME_MAX_LEN 32
#define DENTRY_COUNT 63

typedef struct dentry_t {
    union {
        uint32_t val[16];
        struct {
            uint8_t name[FNAME_MAX_LEN];  /* name of file              */
            uint32_t file_type;           /* file type (0, 1, or 2)    */
            uint32_t inode_index;         /* index of associated inode */
            uint32_t reserved[6];
        } __attribute__ ((packed));
    };
} dentry_t;

typedef struct inode_t {
    union {
        uint32_t val[BLOCK_SIZE / 4];
        struct {
            uint32_t length;                             /* length in bytes        */
            uint32_t data_indices[(BLOCK_SIZE / 4) - 1]; /* indices of data blocks */
        } __attribute__ ((packed));
    };
} inode_t;

typedef struct boot_block_t {
    union {
        uint32_t val[BLOCK_SIZE / 4];
        struct {
            uint32_t dentry_count;             /* number of dentries    */
            uint32_t inode_count;              /* number of inodes      */
            uint32_t data_count;               /* number of data blocks */
            uint32_t reserved[13];
            dentry_t dentries[DENTRY_COUNT];   /* array of dentries     */
        } __attribute__ ((packed));
    };
} boot_block_t;

typedef struct data_block_t {
    uint8_t data[BLOCK_SIZE];
} data_block_t;

// filesystem
/* Initializes filesystem */
void init_filesys (uint32_t fs_addr);
/* Puts dentry_t data into pointer location based on file name */
int32_t read_dentry_by_name (const uint8_t* fname, dentry_t* dentry);
/* Puts dentry_t data into pointer location based on index */
int32_t read_dentry_by_index (uint32_t index, dentry_t* dentry);
/* Puts byte data from file into buffer based on inode and offset */
int32_t read_data (uint32_t inode_i, uint32_t offset, uint8_t* buffer, uint32_t length);
/* Returns the next file name in the filesys */
uint8_t* directory_read();

// file operations
/*  */
int32_t file_read();
/*  */
int32_t file_write();
/*  */
int32_t file_open();
/*  */
int32_t file_close();

// dir operations
/*  */
int32_t dir_read();
/*  */
int32_t dir_write();
/*  */
int32_t dir_open();
/*  */
int32_t dir_close();

#endif //_FILESYS_H