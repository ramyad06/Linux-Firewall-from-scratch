#include "firewalld.h"

void memorycopy(int8* dst , int8* src,int32 size){
    int8 *d,*s;
    int32 n;

    for(d=dst,s=src,n=size;n;d++,s++,n--)
        *d = *s;
    
    return p;
}
dynamic *mkdynamic(int16 entrysize,int8 *datatype){
    dynamic *p;
    int32 size;
    
    size = sizeof(struct s_dynamic)+(entrysize*Blocksize);
    p = (dynamic *)malloc(size);
    assert(p);
    zero($1 p,size);

    p->count = 0;
    p->capacity = Blocksize;
    p->entrysize = entrysize;
    memorycopy(p-> type,datatype,min(stringlen(datatype),15))
    return p;

}

void dynadd(dynamic *arr,void *entry){
    int32 size,n, cap;

    if(arr->count >= arr->capacity){
        cap = arr->capacity + Blocksize;
        size = (arr->entrysize*cap);
        n = sizeof(struct s_dynamic)+size;
        arr = (dynamic *)realloc(arr,$i n);
        assert(arr);
        arr->capacity = cap;
    }

    idx = arr->count;
    memorycopy($1 arr->data[idx],$1 entry,arr->size);
    arr->count++;

    return;
}

void dynprint_(dynamic *arr,int8 *var){
    assert(arr && arr->count)
    printf(
        "Printing '%s'\n"
        "  datatype: %s\n"
        "  capacity: %d\n"
        "  count: %d\n"
        "  entrysize: %d\n\n",
            var,arr->type,arr->capacity,
            arr->count, arr->entrysize);

        printhex(arr->data,min((arr->count*arr->entrysize),32),0);
        printf("\n");
    }

int main(int argc, char *argv[]) {
    dynamic arr;
    arr=mkdynamic(int);
    dynadd(arr, (void *)1);
    dynadd(arr, (void *)2);
    dynadd(arr, (void *)3);
    dynadd(arr, (void *)4);
    dynadd(arr, (void *)5);

    dynprint_(arr);
    free(arr);
    return 0;
}