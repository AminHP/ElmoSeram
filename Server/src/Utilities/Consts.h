#ifndef __CONSTS_H_
#define __CONSTS_H_

#include <iostream>

#include <openssl/md5.h>

// ##################### FUNCTIONS #########################
#define arrlen(x) (sizeof(x) / sizeof(*x))
#define int2str(x) (std::to_string(x))

#define HASH(x) std::string((char*) MD5((unsigned char*) x.c_str(), x.size(), NULL))


// ##################### SOCKET #########################
#define CONNECTION_PORT 10000
#define CONNECTION_END_STR "<|.|>"


// ##################### DATABASE #########################
#define DB_HOST "127.0.0.1"
#define DB_PORT "3306"
#define DB_USER "root"
#define DB_PASS "root"
#define DB_NAME "elmoseram"



#endif // __CONSTS_H_
