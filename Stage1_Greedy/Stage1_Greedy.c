#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// gcc -m32 -O0 -fno-stack-protector -mpreferred-stack-boundary=2 -z execstack -o Stage1_Greedy.o Stage1_Greedy.c

typedef struct Book_ {
  int book_id;
  char title[64];
  char borrowerName[16];  
  int isBorrowed;
} Book;

typedef struct Student_ {
  char name[16];                
  char department[16];  
} Student;

void initializeData(Book *books, Student *student, int *totalBooks);
void epilogue(Book *books, Student *student, int totalBooks);
void menu(Book *books, Student *student, int *totalBooks);
void register_student(Student *student);
void borrow_book(Book *books, Student *student, int totalBooks);
void list_books(Book *books, int totalBooks);
void get_flag();

void initializeData(Book *books, Student *student, int *totalBooks) {
  strcpy(books[0].title, "Shakespeare Literature");
  books[0].book_id = 0;
  books[0].isBorrowed = 0;
  books[0].borrowerName[0] = '\0';

  strcpy(books[1].title, "Programming Languages");
  books[1].book_id = 1;
  books[1].isBorrowed = 0;
  books[1].borrowerName[0] = '\0';

  *totalBooks = 2;

  strcpy(student->department, "Computer");
}

void menu(Book *books, Student *student, int *totalBooks) {
  int choice;

  while (1) {
    printf("\n===== Library System =====\n");
    printf("1. Register / Update Name\n");
    printf("2. Borrow a Book\n");
    printf("3. View Book List\n");
    printf("4. Exit\n");
    printf("Choice: ");

    if (scanf("%d", &choice) != 1) {
      printf("Invalid input.\n");
      return;
    }

    switch (choice) {
      case 1:
        register_student(student);
        break;
      case 2:
        borrow_book(books, student, *totalBooks);
        break;
      case 3:
        list_books(books, *totalBooks);
        break;
      case 4:
        printf("Exiting program.\n");
        exit(0);
      default:
        printf("Invalid choice.\n");
    }
  }
}

void register_student(Student *student) {
  char nameInput[64]; 

  printf("\n===== Student Registration =====\n");
  printf("Enter your name: ");
  scanf("%63s", nameInput);  

  strcpy(student->name, nameInput);

  printf("Registration complete! ( Department: %s)\n", student->department);
}

void borrow_book(Book *books, Student *student, int totalBooks) {
  int bookId;

  printf("\n===== Borrow a Book =====\n");
  printf("Enter book ID: ");

  if (scanf("%d", &bookId) != 1) {
    printf("Invalid input.\n");
    return;
  }

  if (bookId < 0 || bookId >= totalBooks) {
    printf("Invalid book ID.\n");
    return;
  }

  if (bookId == 0 && strcasecmp(student->department, "english") != 0) {
    printf("This book is only available to 'English' department students.\n");
    return;
  }

  if (books[bookId].isBorrowed) {
    printf("This book is already borrowed.\n");
    return;
  }

  books[bookId].isBorrowed = 1;
  printf("You have borrowed '%s'.\n", books[bookId].title);

  if (bookId == 0 && strcasecmp(student->department, "english") == 0) {
    get_flag();
    exit(0);
  }
}

void list_books(Book *books, int totalBooks) {
  printf("\n===== Book List =====\n");
  printf("%-3s  %-10s  %-10s  %-10s  %-30s\n", "ID", "Status", "Borrower", "Department", "Title");
  printf("-------------------------------------------------------------------------------\n");

  for (int i = 0; i < totalBooks; i++) {
    char *department = (i == 0) ? "English" : "Computer";  // ID 0 → English, ID 1 → Computer

    printf("%-3d  %-10s  %-10s  %-10s  %-30s\n",
           books[i].book_id,
           books[i].isBorrowed ? "Borrowed" : "Available",
           books[i].borrowerName[0] ? books[i].borrowerName : "-",
           department,
           books[i].title);
  }
}

void epilogue(Book *books, Student *student, int totalBooks) {
  printf("----------------------------------------------\n");
  printf("Major textbooks are restricted to\n");
  printf("students of that department only.\n\n");

  printf("Youngjae is studying Computer Science.\n");

  printf("But he wants to check out an English department book\n");
  printf("as a gift for his girlfriend, who is obsessed with Shakespeare.\n\n");

  printf("Unfortunately, the system enforces strict borrowing rules,\n");
  printf("preventing students from accessing books outside their department.\n\n");

  printf("Still, Youngjae refuses to give up.\n");

  printf("Determined to borrow the English textbook,\n");
  printf("he sets out to hack the system!\n");

  printf("----------------------------------------------\n\n");

  printf("Currently available books:\n");
  list_books(books, totalBooks);
  printf("\n(Current Department: %s)\n", student->department);
}

void get_flag() {
  FILE *file = fopen("flag.txt", "r");
  if (!file) {
    printf("Unable to open flag file.\n");
    return;
  }

  char flag[100];
  if (fgets(flag, sizeof(flag), file) != NULL) {
    printf("FLAG: %s\n", flag);
  } else {
    printf("Failed to read FLAG.\n");
  }

  fclose(file);
}

int main() {
  Book books[100];
  Student student;
  int totalBooks = 0;
  
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
  
  initializeData(books, &student, &totalBooks);
  epilogue(books, &student, totalBooks);
  menu(books, &student, &totalBooks);

  return 0;
}