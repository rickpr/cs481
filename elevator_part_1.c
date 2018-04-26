#include <stdio.h>
#include <pthread.h>
#include "elevator.h"

/* Called once at the beginning of the simulation */
void initialize_simulation(Elevator_Simulation *es) {
  /* It says in the other file to define es -> v. I will use the doubly-linked
   * list  provided, and use this as a queue. */
  es -> v = new_dllist();
}

/* Called once for each elevator, before the thread is created */
void initialize_elevator(Elevator *e) {
}

/* Called once for each person, before the thread is created */
void initialize_person(Person *p) {
  /* Add the person to the doubly-linked list. The list accepts only objects of
   * type JVal, so we cast this as a JVal using the helper function. */
  dll_append(p -> es -> v, new_jval_v(*p));
}

/* The following is called when a person first enters the system.  
   It should block until an elevator is on the person's "from" floor
   and the door is open.  When it does so, the person's e field
   should point to the elevator on which the person should get.  */
void wait_for_elevator(Person *p) {
  /* Since this is supposed to block, we should lock the mutex */
  pthread_mutex_lock(p -> lock);
  pthread_mutex_unlock(p -> lock);
}

/* The following is called after a person gets on the elevator.  It should block
   until the person is at his/her destination floor, and the elevator's
   door is open. */
void wait_to_get_off_elevator(Person *p) {
}

/* The following is called after a person gets off the elevator. */
void person_done(Person *p) {
}

Person check_for_people_to_unload() {
}

Person check_for_people_to_load(Elevator_Simulation *es) {
  return *(Person*) jval_v(dll_val(dll_first((Dllist) es -> v)));
}

void move(Elevator *elevator) {
}

/* The following is the main elevator thread.  It can only move and open/close
   its doors using the given procedures. */
void *elevator(void *arg) { /* The arg is the thread's Elevator struct */
  Elevator* elevator = arg;
  /* Poll for people */
  while(1) {
    pthread_mutex_lock(elevator -> es -> lock);
    if(dll_empty(elevator -> es -> v)) {
      /* do nothing if no people */
      printf("WOOSH\n");
    } else {
      Person person = check_for_people_to_load(elevator -> es);
      person.e = elevator;
      printf("id: %d\n", person.e->id);
    }
    pthread_mutex_unlock(elevator -> es -> lock);
  }
  return NULL;
}
