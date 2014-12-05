#include <stdio.h>
#include <pthread.h>

struct Data {
    char * msg;
    int threadID;
};

// Function declarations
void print_message(void * ptr);

int main(void)
{
    pthread_t thread1, thread2, thread3, thread4, thread5;

    struct Data data1 = { "Hello world from Thread ID #", 1 };
    struct Data data2 = { "Hello world from Thread ID #", 2 };
    struct Data data3 = { "Hello world from Thread ID #", 3 };
    struct Data data4 = { "Hello world from Thread ID #", 4 };
    struct Data data5 = { "Hello world from Thread ID #", 5 };
   
    // Create threads
    pthread_create(&thread1, NULL, (void *) &print_message, (void *) &data1);
    pthread_create(&thread2, NULL, (void *) &print_message, (void *) &data2);
    pthread_create(&thread3, NULL, (void *) &print_message, (void *) &data3);
    pthread_create(&thread4, NULL, (void *) &print_message, (void *) &data4);
    pthread_create(&thread5, NULL, (void *) &print_message, (void *) &data5);

    // Wait until all threads have completed
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);

    return 0;
}

void print_message(void * ptr)
{
    struct Data * data = (struct Data *) ptr;
    printf("%s%d\n", data->msg, data->threadID);
}
