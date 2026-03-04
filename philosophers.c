#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* doubler(void* arg) {
    int* val = (int*)arg;
    printf("Double: %d\n", (*val) * 2);
    return NULL;
}

void* squarer(void* arg) {
    int* val = (int*)arg;
    printf("Square: %d\n", (*val) * (*val));
    return NULL;
}

int main() {
    pthread_t t1_doubler, t2_squarer;

    int input = 5;

    pthread_create(&t1_doubler, NULL, doubler, &input);
    // TASK 2: Create the 'doubler' thread. 
    // Pass 'input' as the argument.
    // pthread_create( ??? );

    pthread_create(&t2_squarer, NULL, squarer, &input);
    // TASK 3: Create the 'squarer' thread.
    // Pass 'input' as the argument.
    // pthread_create( ??? );

    // TASK 4: Why is it a bad idea to leave the code like this 
    // and just let main() finish right now? 
    // (We haven't learned pthread_join yet, but tell me the 'why')
    // It is a bad idea since we loose track of both threads
    sleep(1);
    
    return 0;
}