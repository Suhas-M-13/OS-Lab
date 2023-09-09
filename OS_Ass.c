#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

int numLanes; // Number of lanes in the traffic intersection
sem_t semaphore; // Semaphore to control access to the intersection
int* vehicleQueue; // Queue indicating whether a lane has vehicles waiting
pthread_cond_t threadFinishedCondition; // Condition variable to wait for thread execution
pthread_mutex_t threadFinishedMutex; // Mutex to protect the condition variable
int count = 0;
volatile int terminate = 0; // Termination condition variable

void generate(int* a) {
    for (int i = 0; i < numLanes; i++)
        a[i] = i;
}

void* simulateIntersection(void* arg) {
    int laneIndex = (int)arg;
    int currentLane = vehicleQueue[laneIndex];

    // Signal the waiting lane to turn signal to green
    if (currentLane != -1) {
        printf("Signal turned to green for Lane %d\n", currentLane);

        // Acquire semaphore to enter the intersection
        sem_wait(&semaphore);

        // Display that signals of other lanes are red
        printf("Signal turned RED for all other lanes\n");

        // Display the vehicle entering the intersection
        printf("Vehicles of Lane %d entered intersection\n", currentLane);
        sleep(3);
        // Simulate crossing the intersection
        // ...

        // Display that the vehicle crossed the intersection
        printf("Vehicles of Lane %d crossed the intersection\n", currentLane);

        // Turn signal back to red and remove the semaphore
        printf("Signal turned to red for Lane %d\n", currentLane);
        vehicleQueue[laneIndex] = -1;
        sem_post(&semaphore);
    }

    // Signal the main thread that the thread has finished execution
    pthread_mutex_lock(&threadFinishedMutex);
    pthread_cond_signal(&threadFinishedCondition);
    pthread_mutex_unlock(&threadFinishedMutex);

    free(arg); // Free the memory allocated for the thread's argument

    pthread_exit(NULL);
}

void* userInput(void* arg) {
    char input[10];
    while (1) {
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%s", input) == 1 && input[0] == 'q') {
            terminate = 1;
            printf("Terminating the program...\n");
            break;
        }
    }
    return NULL;
}

int main() {
    // Take input for the number of lanes
    printf("Enter the number of lanes in the traffic intersection: ");
    scanf("%d", &numLanes);
    if(numLanes<3){
    printf("Invalid input\nTerminated...\n");
     return 0;
     }
    printf("NOTE:Press 'q' to terminate\n"); 
    vehicleQueue = (int*)calloc(numLanes, sizeof(int));
    if (vehicleQueue == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Initialize semaphore
    if (sem_init(&semaphore, 0, 1) != 0) {
        printf("Semaphore initialization failed.\n");
        return 1;
    }

    // Initialize the condition variable and mutex
    pthread_cond_init(&threadFinishedCondition, NULL);
    pthread_mutex_init(&threadFinishedMutex, NULL);

    srand(time(NULL)); // Seed the random number generator

    // Create the user input thread
    pthread_t userInputThread;
    if (pthread_create(&userInputThread, NULL, userInput, NULL) != 0) {
        printf("Failed to create user input thread.\n");
        return 1;
    }

    while (numLanes >= 3 && count < 10 && !terminate) {
        for (int i = 0; i < numLanes; i++) {
            vehicleQueue[i] = -1;
        }
        
        generate(vehicleQueue);
        if (count < numLanes + 1) {
            for (int i = 0; i < count; i++) {
                int r = rand() % numLanes;
                vehicleQueue[r] = -1;
            }
        }
         if(count == numLanes+1) {
            for (int i = 0; i < numLanes; i++) {
                vehicleQueue[i] = -1;
            }
        }
        
        // Display the generated sequence
        int vehicleExists = 0;
        for (int i = 0; i < numLanes; i++) {
            if (vehicleQueue[i] != -1) {
                printf("Vehicles waiting in lane %d\n", vehicleQueue[i]);
                vehicleExists = 1;
            }
        }
        
        if (!vehicleExists) {
            printf("NO WAITING VEHICLES\nALL SIGNALS ARE SHOWING RED\n");
        }

        for (int i = 0; i < numLanes; i++) {
            if (vehicleQueue[i] != -1) {
                int* lane = (int*)malloc(sizeof(int));
                *lane = i;

                pthread_t thread;
                if (pthread_create(&thread, NULL, simulateIntersection, (void*)lane) != 0) {
                    printf("Thread creation failed.\n");
                    return 1;
                }

                // Wait for the thread to finish execution
                pthread_mutex_lock(&threadFinishedMutex);
                pthread_cond_wait(&threadFinishedCondition, &threadFinishedMutex);
                pthread_mutex_unlock(&threadFinishedMutex);
            }
        }

        sleep(2);
        count++;
        if (count < 10 && !terminate) {
            printf("\nNext Round:\n");
            generate(vehicleQueue);
        }
    }

    // Destroy semaphore
    sem_destroy(&semaphore);

    // Destroy the condition variable and mutex
    pthread_cond_destroy(&threadFinishedCondition);
    pthread_mutex_destroy(&threadFinishedMutex);

    free(vehicleQueue); // Free the memory allocated for the vehicle queue

    // Wait for the userInputThread to finish
    pthread_join(userInputThread, NULL);

    return 0;
}