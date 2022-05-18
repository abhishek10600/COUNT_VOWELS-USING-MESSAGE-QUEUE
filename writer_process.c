//program to count the vowel in a string using message queue
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MAX_LEN 512

struct messg
{
    long int msg_type;
    char some_msg[MAX_LEN];
};

int main()
{
    int running = 1;
    int running2 = 1;
    int msgid,nmsgid;
    struct messg msg_buf;
    long int msg_recv = 0;
    char buffer[50];
    msgid = msgget((key_t)12345, 0666 | IPC_CREAT);
    nmsgid = msgget((key_t)12346, 0666 | IPC_CREAT);
    if(msgid == -1)
    {
        printf("Error in creating the message queue \n");
        exit(0);
    }
    //Sending the data from the process 1 to process 2
    while(running)
    {
        printf("Enter the message to be sent: ");
        fgets(buffer, 50, stdin);
        if(strncmp(buffer, "exit", 4) == 0)
        {
            running = 0;
        }
        else
        {
            strcpy(msg_buf.some_msg, buffer);
            msg_buf.msg_type = 1;
            msgsnd(msgid, (void *)&msg_buf,
            strlen(msg_buf.some_msg), 0);
        }
    }
    //Here we are recieving the data from the process 2 ;
    while(running2)
    {
        msg_buf.msg_type = 2;
        msg_recv = msgrcv(nmsgid, (void *)&msg_buf, MAX_LEN, 2,0);
        if(msg_recv == -1)
        {
            printf("Error in receiving the message \n");
            exit(0);
        }
        printf("Message received: %s \n", msg_buf.some_msg);
    }
}
