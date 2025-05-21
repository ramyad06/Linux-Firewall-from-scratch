/* firewalld.h */
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;

#define $1 (int8 *)
#define $2 (int16)
#define $4 (int32)
#define $8 (int64)
#define $c (char *)
#define $i (int)

#define dynprint(x)     dynprint_((x), $1 # x)
#define mkdynamic(x)    mkdynamic_(sizeof(x), $1 # x)
#define min(x,y)        ((x) < (y)) ? (x) : (y)

int main(int,char**);

/*

interface e0/0 --
  mac address 0001.384a.1216 --
  ip address 192.168.10.1/24 --
  no layer 1 shutdown --
  no layer 3 shutdown --
  zone inside --
  security-level e --
end

user jonas pin 0123 root --
root key 312-590211 --

access-list 5 permit 192.168.10.0/24 --
access-list 5 permit host 5.5.5.5 --
access-list 5 drop any --

access-group 5 inbound int e0/0

*/

typedef int8    ifnumber;
typedef int64   macadress;
typedef int32   ipadress;
typedef int8    cidr;
typedef int8    seclevel;
typedef int16   pincode;
typedef int16    subkey;
typedef int32   rounds;

#define Blocksize 10

enum e_action {
    permit = 1,
    drop = 2
};
typedef enum e_action action;

struct s_network {
    ipadress ip;
    cidr size;
};
typedef struct s_network network;

struct s_rootkey {
    subkey key:10;
    rounds n:21;
};
typedef struct s_rootkey rootkey;

struct s_user {
    int8 username[16];
    pincode pin:14;
    bool root:1;
};
typedef struct s_user user;

struct s_stdace {
    action act:3;
    network net;
};
typedef struct s_stdace stdace;
typedef stdace stdacl[99];

struct s_interface {
    ifnumber id:3;
    macadress mac:48;
    network net;
    struct {
        bool l1:1;
        bool l3:1;
    } shutdown;
    int8 zone[16];
    seclevel level:4;
    stdacl *aclin;
    stdacl *aclout;
};
typedef struct s_interface interface;

struct s_config {
    interface *iface[7];
    user account;
    rootkey *key;
    stdacl acl[99];
};
typedef struct s_config config;

struct s_dynamic {
    int32 count;
    int32 entrysize;
    int32 capacity;
    int8 type[16];
    int8 data[];
};
typedef struct s_dynamic dynamic;

// constructor
dynamic *mkdynamic_(int16, int8*);

void memorycopy(int8*,int8*,int32);
int16 stringlen(int8*);

void dynadd(dynamic*,void*);
void dynprint_(dynamic*,int8*);