#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// gcc -m32 -O0 -fno-stack-protector -mpreferred-stack-boundary=2 -z execstack -o Stage2_Innocent_sheep.o Stage2_Innocent_sheep.c

typedef struct Student_ {
  char name[32];
  int student_id;
  char is_overdue;
} Student;

void menu(Student *youngjae, Student *seogyeong);
void borrow_book(Student *youngjae, Student *seogyeong);
void check_status(Student *youngjae, Student *seogyeong);
void get_system_info(Student *youngjae, Student *seogyeong);
void epilogue();

void menu(Student *youngjae, Student *seogyeong) {
  int choice;
  printf("\n=== Library System Menu ===\n");
  printf("1. Borrow a book\n");
  printf("2. Check status\n");
  scanf("%d", &choice);
  
  if(choice == 1)
    borrow_book(youngjae, seogyeong);
  else if(choice == 2)
    check_status(youngjae, seogyeong);
  else if(choice == 3)
    get_system_info(youngjae, seogyeong);
  else
    printf("Invalid choice.\n");
}

void borrow_book(Student *youngjae, Student *seogyeong) {
  youngjae->is_overdue = 'Y';
  printf("You are trying to borrow a book...\n");
  printf("Enter your name: \n");
  read(0, youngjae->name, 100);
  if(youngjae->is_overdue == 'Y') {
    printf("You have overdue books. Cannot borrow.\n");
  } else {
    printf("Book borrowed successfully!\n");
  }
  printf("Your overdue status: %c\n", youngjae->is_overdue);
}

void check_status(Student *youngjae, Student *seogyeong) {
  printf("\n=== Student Overdue Status ===\n");
  printf("Youngjae (ID: %d): %s\n", 
         youngjae->student_id, 
         youngjae->is_overdue == 'Y' ? "Overdue" : "Normal");
  
  printf("Seogyeong (ID: %d): %s\n", 
         seogyeong->student_id, 
         seogyeong->is_overdue == 'Y' ? "Overdue" : "Normal");
}

void get_system_info(Student *youngjae, Student *seogyeong) {
  if(youngjae->is_overdue == 'N' && seogyeong->is_overdue == 'Y')
    printf("Stack address: %p\n", youngjae->name);
  else
    printf("Access denied.\n");
}

void epilogue() {
  printf("--------------------------------------------------------------------------\n");
  printf("Unfortunately, Youngjae broke up with his girlfriend before getting the book back.\n");
  printf("The library begins pressuring him about how he managed to borrow an English department book\n");
  printf("and why he hasn't returned it yet.\n");
  printf("However, Youngjae's ex-girlfriend isn't responding to any messages.\n\n");
  
  printf("Eventually, Youngjae decides to find an innocent scapegoat, and that's Seogyeong.\n");
  printf("Youngjae plans to change his overdue record to Seogyeong's name instead.\n");
  printf("To accomplish this, gaining shell access to the system is essential.\n");
  printf("--------------------------------------------------------------------------\n\n");
}

int main() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
  epilogue();
  Student seogyeong = {"seogyeong", 20230002, 'N'};
  Student youngjae = {"youngjae", 20230001, 'Y'};
  printf("[Library Management System]\n\n");
  
  int i;
  for(i = 0; i < 10; i++) {
    menu(&youngjae, &seogyeong);
  }
  
  printf("\nProgram terminated.\n");
  return 0;
}