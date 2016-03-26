#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "spinlock.h"
#include "uthread.h"

#define MAX_ITEMS 10

int items = 0;

const int NUM_ITERATIONS = 200;
const int NUM_CONSUMERS  = 1;
const int NUM_PRODUCERS  = 4;

int producer_wait_count;     // # of times producer had to wait
int consumer_wait_count;     // # of times consumer had to wait
int histogram [MAX_ITEMS+1]; // histogram [i] == # of times list stored i items

spinlock_t lock;

void produce() {
  spinlock_lock(&lock);
  while (items >= MAX_ITEMS) {
    producer_wait_count++;
    spinlock_unlock(&lock);
    spinlock_lock(&lock);
  }
  assert (items < MAX_ITEMS);
  items++;
  histogram [items] += 1;
  spinlock_unlock(&lock);
}

void consume() {
  spinlock_lock(&lock);
  while (items <= 0) {
    consumer_wait_count++;
    spinlock_unlock(&lock);
    spinlock_lock(&lock);
  }
  assert (items > 0);
  items--;
  histogram [items] += 1;
  spinlock_unlock(&lock);
}

void* producer(void* n) {
  for (int i=0; i < NUM_ITERATIONS/NUM_PRODUCERS; i++) {
    produce();
  }
  return NULL;
}

void* consumer(void* n) {
  for (int i=0; i< NUM_ITERATIONS/NUM_CONSUMERS; i++) {
    consume();
  }
  return NULL;
}

int main (int argc, char** argv) {
  // TODO create threads to run the producers and consumers
  uthread_init(4);
  spinlock_create (&lock);

  uthread_t t[NUM_CONSUMERS+NUM_PRODUCERS];

  for (int i=0; i<NUM_CONSUMERS; i++) {
    t[i] = uthread_create(&consumer, NULL);
  }
  for (int i=0; i<NUM_PRODUCERS; i++) {
    t[i+NUM_CONSUMERS] = uthread_create(&producer, NULL);
  }

  for (int i=0; i<NUM_CONSUMERS+NUM_PRODUCERS; i++) {
    void *res;
    uthread_join(t[i], &res);
  }

  printf("Producer wait: %d\nConsumer wait: %d\n",
         producer_wait_count, consumer_wait_count);
  for(int i=0;i<MAX_ITEMS+1;i++)
    printf("items %d count %d\n", i, histogram[i]);
}
