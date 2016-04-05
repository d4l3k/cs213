#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include "uthread.h"
#include "uthread_sem.h"

#ifdef VERBOSE
#define VERBOSE_PRINT(S, ...) printf (S, ##__VA_ARGS__);
#else
#define VERBOSE_PRINT(S, ...) ;
#endif

#define MAX_OCCUPANCY      3
#define NUM_ITERATIONS     100
#define NUM_PEOPLE         20

#define WAITING_HISTOGRAM_SIZE (NUM_ITERATIONS * NUM_PEOPLE)
int           entryTicker;
int           waitingHistogram         [WAITING_HISTOGRAM_SIZE];
int           waitingHistogramOverflow;
uthread_sem_t waitingHistogramMutex;
int           occupancyHistogram       [2] [MAX_OCCUPANCY + 1];

/**
 * You may find these declarations useful.
 */
enum Sex {MALE = 0, FEMALE = 1};
const static enum Sex otherSex [] = {FEMALE, MALE};

struct Washroom {
  // TODO
};

struct Washroom* createWashroom() {
  struct Washroom* washroom = malloc (sizeof (struct Washroom));
  // TODO
  return washroom;
}

void enterWashroom (struct Washroom* washroom, enum Sex Sex) {
  // TODO
}

void leaveWashroom (struct Washroom* washroom) {
  // TODO
}

void recordWaitingTime (int waitingTime) {
  uthread_sem_wait (waitingHistogramMutex);
    if (waitingTime < WAITING_HISTOGRAM_SIZE)
      waitingHistogram [waitingTime] ++;
    else
      waitingHistogramOverflow ++;
  uthread_sem_signal (waitingHistogramMutex);
}

//
// TODO
// Other procedures etc.
//

int main (int argc, char** argv) {
  uthread_init (1);
  struct Washroom* washroom = createWashroom();
  waitingHistogramMutex     = uthread_sem_create (1);

  // TODO
  
  printf ("Times with 1 male    %d\n", occupancyHistogram [MALE]   [1]);
  printf ("Times with 2 males   %d\n", occupancyHistogram [MALE]   [2]);
  printf ("Times with 3 males   %d\n", occupancyHistogram [MALE]   [3]);
  printf ("Times with 1 female  %d\n", occupancyHistogram [FEMALE] [1]);
  printf ("Times with 2 females %d\n", occupancyHistogram [FEMALE] [2]);
  printf ("Times with 3 females %d\n", occupancyHistogram [FEMALE] [3]);
  printf ("Waiting Histogram\n");
  for (int i=0; i<WAITING_HISTOGRAM_SIZE; i++)
    if (waitingHistogram [i])
      printf ("  Number of times people waited for %d %s to enter: %d\n", i, i==1?"person":"people", waitingHistogram [i]);
  if (waitingHistogramOverflow)
    printf ("  Number of times people waited more than %d entries: %d\n", WAITING_HISTOGRAM_SIZE, waitingHistogramOverflow);
}