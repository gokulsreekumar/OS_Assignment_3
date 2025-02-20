#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "grade.h"

struct message_buffer
{
    long mtype;     // Type Of Message
    float data[10]; // Message
} message, message1, message2;

int main()
{
    key_t key;
    int msgid;

    key = ftok(".", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    int i;

    float avg;
    float marks[5] = {10, 20, 30, 40, 50};

    for (int i = 0; i < 5; i++)
    {
        printf("Marks for Student with ID-%d :\n", i + 1);
        scanf("%f", &marks[i]);
    }

    // Send to Students
    printf("Sending Marks to Students....\n");
    for (int i = 0; i < 5; i++)
    {
        message.mtype = i + 1;
        message.data[0] = marks[i];
        printf("Sent Student with ID: %d, %f marks\n", i + 1, marks[i]);
        msgsnd(msgid, &message, sizeof(message), 0);
    }

    // Send to TA
    printf("Sending Marks To TA....");
    for (int i = 0; i < 5; i++)
    {
        message1.data[i] = marks[i];
    }
    message1.mtype = 10;
    msgsnd(msgid, &message1, sizeof(message1), 0);
    printf("Sent\n");

    printf("Waiting for Avg and Grades from TA..\n");

    msgrcv(msgid, &message2, sizeof(message2), 100, 0);
    printf("Average Marks: %f\n", message2.data[0]);
    printf("Grades of Students Recieved:\n");
    for (int i = 0; i < 5; i++)
    {
        if (message2.data[i + 1] == S)
        {
            printf("Student ID %d: %c\n", i + 1, 'S');
        }
        else if (message2.data[i + 1] == A)
        {
            printf("Student ID %d: %c\n", i + 1, 'A');
        }
        else if (message2.data[i + 1] == B)
        {
            printf("Student ID %d: %c\n", i + 1, 'B');
        }
        else if (message2.data[i + 1] == E)
        {
            printf("Student ID %d: %c\n", i + 1, 'E');
        };
    }

    msgctl(msgid, IPC_RMID, NULL);
}