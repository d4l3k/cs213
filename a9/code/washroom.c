#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

#ifdef VERBOSE
#define VERBOSE_PRINT(S, ...) printf (S, ##__VA_ARGS__);
#else
#define VERBOSE_PRINT(S, ...) ;
#endif

#define MAX_OCCUPANCY      3
#define NUM_ITERATIONS     100
#define NUM_PEOPLE         20
#define FAIR_WAITING_COUNT 4

/**
 * You might find these declarations useful.
 */
enum Sex {MALE = 0, FEMALE = 1};
const static enum Sex otherSex [] = {FEMALE, MALE};

struct Washroom {
  uthread_mutex_t mutex;
  uthread_cond_t  male;
  uthread_cond_t  female;
  int count;
  enum Sex sex;
};

struct Washroom* createWashroom() {
  struct Washroom* washroom = malloc (sizeof (struct Washroom));
  washroom->mutex   = uthread_mutex_create();
  washroom->male   = uthread_cond_create (washroom->mutex);
  washroom->female   = uthread_cond_create (washroom->mutex);
  washroom->count = 0;
  washroom->sex = 0;
  return washroom;
}

#define WAITING_HISTOGRAM_SIZE (NUM_ITERATIONS * NUM_PEOPLE)
int             entryTicker;  // incremented with each entry
int             waitingHistogram         [WAITING_HISTOGRAM_SIZE];
int             waitingHistogramOverflow;
uthread_mutex_t waitingHistogrammutex;
int             occupancyHistogram       [2] [MAX_OCCUPANCY + 1];

void signalSexN(struct Washroom* w, enum Sex sex, int n) {
  for (int i=0; i<n; i++) {
    if (sex == MALE) {
      uthread_cond_signal(w->male);
    } else if (sex == FEMALE) {
      uthread_cond_signal(w->female);
    }
  }
}

void waitSex(struct Washroom* w, enum Sex sex) {
  if (sex == MALE) {
    uthread_cond_wait(w->male);
  } else if (sex == FEMALE) {
    uthread_cond_wait(w->female);
  }
}

void enterWashroom (struct Washroom* w, enum Sex sex) {
  uthread_mutex_lock(w->mutex);
  if (w->count==0) {
    w->sex = sex;
  } else {
    waitSex(w,sex);
  }
  w->count++;
  occupancyHistogram[sex][w->count]++;
  uthread_mutex_unlock(w->mutex);
}

void leaveWashroom (struct Washroom* w) {
  uthread_mutex_lock(w->mutex);
  w->count--;
  occupancyHistogram[w->sex][w->count]++;
  if (w->count == 0) {
    w->sex = otherSex[w->sex];
    signalSexN(w, w->sex, 3);
  }
  uthread_mutex_unlock(w->mutex);
}

void recordWaitingTime (int waitingTime) {
  uthread_mutex_lock (waitingHistogrammutex);
  if (waitingTime < WAITING_HISTOGRAM_SIZE)
    waitingHistogram [waitingTime] ++;
  else
    waitingHistogramOverflow ++;
  uthread_mutex_unlock (waitingHistogrammutex);
}

void* person (void* av) {
  struct Washroom* w = av;
  enum Sex gender = random() % 2;
  for (int i=0;i<NUM_ITERATIONS;i++) {
    enterWashroom(w, gender);
    for (int i=0;i<NUM_PEOPLE;i++) {
      uthread_yield();
    }
    leaveWashroom(w);
    for (int i=0;i<NUM_PEOPLE;i++) {
      uthread_yield();
    }
  }
}

//
// TODO
// You will probably need to create some additional produres etc.
//

int main (int argc, char** argv) {
  uthread_init (1);
  struct Washroom* washroom = createWashroom();
  uthread_t        pt [NUM_PEOPLE];
  waitingHistogrammutex = uthread_mutex_create ();

  for (int i=0; i<NUM_PEOPLE; i++) {
    pt[i] = uthread_create(person, washroom);
  }
  for (int i=0; i<NUM_PEOPLE; i++) {
    uthread_join(pt[i], 0);
  }

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
