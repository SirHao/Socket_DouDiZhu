#include "../../lib/redis_utils.h"  
int main()  
{  
    //set
    redis_execute("foo","123",1); 

    //get
    char *value=malloc(10);
    memset(value,0,sizeof(value));
    redis_execute("foo",value,2);
    printf("set and get   key:foo value:%s\n",value);
    free(value);
  
    //del
    redis_execute("foo",NULL,3);
    return 0;  
}