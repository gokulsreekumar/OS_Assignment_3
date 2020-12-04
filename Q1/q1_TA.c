#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "grade.h"

struct buffer
{
    long mtype;
    float data[10];
} message, message1;

float getGrade(float mark)
{
    if (mark <= 19)
        return E;
    else if (mark < 29)
        return B;
    else if (mark < 39)
        return A;
    else
        return S;
}

int main()
{
    int i = 0;
    key_t key;
    int msgid;

    float marks[5];
    float avg = 0;

    key = ftok(".", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Recieve the marks
    msgrcv(msgid, &message, sizeof(message), 10, 0);
    printf("Marks Recieved:\n");
    for (i = 0; i < 5; i++)
    {
        printf("Student ID: %d, Marks: %f \n", i, message.data[i]);
        marks[i] = message.data[i];
        avg += marks[i];
    }
    avg /= 5;

    message1.data[0] = avg;
    for (int i = 0; i < 5; i += 1)
    {
        message1.data[i + 1] = getGrade(marks[i]);
    }
    message1.mtype = 100;
    msgsnd(msgid, &message1, sizeof(message1), 0);
    printf("Grades and Average Sent to CI\n");

    return 0;
}