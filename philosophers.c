#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int tickets_remaining = 10;  // The shared resource
pthread_mutex_t ticket_lock; // The lock variable

void* sell_tickets(void* arg) {
    char* agent_name = (char*)arg;

    while (1) {
        pthread_mutex_lock(&ticket_lock);
        // TASK 1: The agent is about to check the computer. 
        // Grab the lock so no other agent can look at the same time!
        // ???

        if (tickets_remaining > 0) {
            // --- CRITICAL SECTION START ---
            printf("%s sold a ticket! Tickets left: %d\n", agent_name, tickets_remaining - 1);
            tickets_remaining--;
            // --- CRITICAL SECTION END ---
            
            pthread_mutex_unlock(&ticket_lock);
            // TASK 2: The sale is complete. Release the lock so the other agent can work.
            // ???
            
            // Wait a tiny bit before trying to sell the next one
            usleep(100000); 
        } else {
            pthread_mutex_unlock(&ticket_lock);
            // TASK 3: We are out of tickets! We need to break out of the loop.
            // BUT WAIT! We grabbed the lock at the top of the loop (Task 1).
            // What MUST we do here before we hit 'break;'?
            // ???
            
            break; 
        }
    }
    return NULL;
}

int main() {
    pthread_t agent1, agent2;

    pthread_mutex_init(&ticket_lock, NULL);
    // TASK 4: Initialize the lock before we create the threads
    // ???

    pthread_create(&agent1, NULL, sell_tickets, "Agent Smith");
    pthread_create(&agent2, NULL, sell_tickets, "Agent Jones");

    pthread_join(agent1, NULL);
    pthread_join(agent2, NULL);

    // TASK 5: The cinema is closed. Destroy the lock to free memory.
    // ???
    pthread_mutex_destroy(&ticket_lock);

    printf("All tickets sold out cleanly!\n");
    return 0;
}