//program to count the number of vowels in a string using message queue
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

int count_vowel(char *messg )
{
    int i, count = 0;
    for(i = 0; i < strlen(messg); i++)
    {
        if(messg[i] == 'a' || messg[i] == 'e' || messg[i] == 'i'|| messg[i] == 'o' || messg[i] == 'u')
        {
            count++;
        }
    }
return count;
}

int main()
{
    int running = 1;
    char final_msg[MAX_LEN];
    int no_of_vowels;
    int msgid,nmsgid;
    struct messg msg_buf;
    key_t key;
    long int msg_recv = 0;
    msgid = msgget((key_t)12345, 0666 | IPC_CREAT);
    nmsgid = msgget((key_t)12346, 0666 | IPC_CREAT);
    struct messg new_msg;
    while(running)
    {
        msg_recv = msgrcv(msgid, (void *)&msg_buf, MAX_LEN, 1, 0);
        if(msg_recv == -1){
        printf("Error in receiving the message \n");
        exit(0);
    }
    printf("Message received: %s \n", msg_buf.some_msg);
    if(strncmp(msg_buf.some_msg, "exit", 4) == 0)
    {
        running = 0;
    }
    no_of_vowels = count_vowel(msg_buf.some_msg);
    snprintf(final_msg, MAX_LEN, "Number of vowels: %d",no_of_vowels);
    strcpy(new_msg.some_msg, final_msg);
    new_msg.msg_type = 2;
    msgsnd(nmsgid, (void *)&new_msg, strlen(new_msg.some_msg),0);
    }

return 0;

}
