#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Class Person
 */

struct Person_class {
  void*   super;
  char* (* toString ) (void*);
};

struct Person {
  struct Person_class *class;
  char *name;
};

char* Person_toString (void* this) {
  char *buf = malloc(sizeof(char)*1000);
  snprintf (buf, 1000, "Name: %s", ((struct Person*)this)->name);
  return buf;
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
  char*         (* toString ) (void*);
};

struct Student {
  struct Student_class* class;
  char *name;
  int sid;
};

char* Student_toString (void* this) {
  struct Student *s = (struct Student*)this;
  char *prev = s->class->super->toString(s);

  char *buf = malloc(sizeof(char)*1000);
  snprintf (buf, 1000, "%s, SID: %d", prev, s->sid);
  free(prev);
  return buf;
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
  char *s = a->class->toString(a);
  printf("%s\n", s);
  free(s);
}

int main (int argc, char** argv) {
  struct Person *people[2] = {new_Person("Alex"), (struct Person*)new_Student("Alice", 300)};
  for (int i=0; i<2;i++) {
    print(people[i]);
  }
}
