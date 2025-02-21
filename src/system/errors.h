#pragma once
// A list of all possible error codes from the sysem



#define SUCCESS          0
// General Error Codes are Reserved Space 1-49
#define EIO_SYS         -1
#define EFAIL           -2
#define ENOMEM_SYS      -3
#define ENULLARG        -4
#define ETIMEOUT        -5
#define ENOSUPPORT      -6

// Networking Error Codes

#define EOT_NOINIT      -50
#define EOT_FAIL        -51
#define EOT_CONFIG      -52