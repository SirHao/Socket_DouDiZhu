#include "handler.h"

int quit_handler(int client_fd){
    struct quit_req_body*  quit_req=malloc(sizeof(struct quit_req_body));
    struct quit_rsp_body*  quit_rsp=malloc(sizeof(struct quit_rsp_body));


    
    
    free(quit_req);
    free(quit_rsp);
    return 0;
}