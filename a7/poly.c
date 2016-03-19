#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Class Person
 */

struct Person_class {
  void*   super;
  void (* toString ) (void*, char*, int);
};

struct Person {
  struct Person_class *class;
  char *name;
};

void Person_toString (void* this, char* buf, int bufSize) {
  snprintf (buf, bufSize, "Name: %s", ((struct Person*)this)->name);
}

struct Person_class Person_class_obj = {NULL, Person_toString};

struct Person* new_Person(char *name) {
  struct Person* obj = malloc (sizeof (struct Person));
  obj->class = &Person_class_obj;
  obj->name = strdup(name);
  return obj;
}


/*
 * Class Student extends Person
 */

struct Student_class {
  struct Person_class* super;
  void         (* toString ) (void*, char*, int);
};

struct Student {
  struct Student_class* class;
  char *name;
  int sid;
};

void Student_toString (void* this, char* buf, int bufSize) {
  struct Student *s = (struct Student*)this;
  char* prev = malloc(sizeof(char)*bufSize);
  s->class->super->toString(s, prev, bufSize);
  snprintf (buf, bufSize, "%s, SID: %d", prev, s->sid);
  free(prev);
}

struct Student_class Student_class_obj = {&Person_class_obj, Student_toString};

struct Student* new_Student(char *name, int sid) {
  struct Student* obj = malloc (sizeof (struct Student));
  obj->class = &Student_class_obj;
  obj->name = strdup(name);
  obj->sid = sid;
  return obj;
}


/*
 * Main
 */

void print (void* aVP) {
  struct Person* a = aVP;
  char *buf = malloc(sizeof(char)*1000);
  a->class->toString(a, buf, 1000);
  printf("%s\n", buf);
  free(buf);
}

int main (int argc, char** argv) {
  struct Person *people[2] = {new_Person("Alex"), (struct Person*)new_Student("Alice", 300)};
  for (int i=0; i<2;i++) {
    print(people[i]);
  }
}
