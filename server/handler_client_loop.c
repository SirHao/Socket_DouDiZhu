#include "handler.h"

void client_loop_handler(int client_fd)
{
    printf("[info] a client join fd:%d\n", client_fd);
    int ret, status = -1;
    int quit_flag = false;
    char req_header;

    while (1)
    {
        ret = recv(client_fd, &req_header, sizeof(req_header), MSG_WAITALL);
        printf("[debug1]接收%d\n", ret);
        if (ret < 0 || req_header != LOGIN_REQ)
            perror("[info]recv login error:");
        else
        {
            status = login_handler(client_fd);
            if (status == 0)
                break;
            else
                sleep(1);
            fflush(stdout);
        }
    }
    printf("[info]start service for user\n");
    while (quit_flag == 0)
    {
        ret = recv(client_fd, &req_header, sizeof(req_header), MSG_WAITALL);
        printf("[info]recv hdr,size:%d,type:%c\n", ret, req_header);
        fflush(stdout);
        switch (req_header)
        {
        //退出
        case QUIT_REQ:
            quit_flag = quit_handler(client_fd);
            break;
        case USER_INFO_REQ:
            user_info_handler(client_fd);
            break;
        case CREATE_JOIN_ROOM_REQ:
            create_join_room_handler(client_fd);
            break;
        default:
            printf("[error] no expected choice\n");
        }
    }
}
