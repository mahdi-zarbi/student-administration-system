#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int const max_student=100;
int const max_course=20;
struct date{
   int years;
   int month;
   int day;
};
struct course{
    char lesson_name[50];
    int course;
    char teacher_name[50];
    float grade;
    int lesson_code;
    
};
struct info{  
    int id;
    char last_name[255];
    char first_name[255];
    struct date birth;
    char gender[255];
    int national_code;
    char father_name[255];
    char major[255];
    struct course book[20];
    int number_courses;
    int number_all_courses;
};


void read_file(struct info stu[], int *count) {
    FILE *file = fopen("mahdi.txt", "r");
    if (!file) {
        printf("\nNO DATA AVAILABLE\n");
        return;
    }

    *count = 0; 
    while (*count < max_student) {
        if (fscanf(file, "%s %s %d %d/%d/%d %s %d %s %s %d",
                  stu[*count].first_name,
                  stu[*count].last_name,
                  &stu[*count].id,
                  &stu[*count].birth.years,
                  &stu[*count].birth.month,
                  &stu[*count].birth.day,
                  stu[*count].gender,
                  &stu[*count].national_code,
                  stu[*count].father_name,
                  stu[*count].major,
                  &stu[*count].number_courses) != 11) {
            break;
        }
        for (int j = 0; j < stu[*count].number_courses && j < max_course; j++) {
            if (fscanf(file, "%s  %s %f %d %d %d",
                      stu[*count].book[j].lesson_name,
                      stu[*count].book[j].teacher_name,
                      &stu[*count].book[j].grade,
                      &stu[*count].book[j].course,
                      &stu[*count].book[j].lesson_code,
                      &stu[*count].number_all_courses) != 6) {
                break;
            }
        }
        (*count)++;
    }
    fclose(file);
}

void update_file(struct info stu[], int* count) {
    FILE *file = fopen("mahdi.txt", "w");
    if (file == NULL) {
        printf("\nTHE FILE COULD NOT BE OPENED FOR WRITING \n");
        return;
    }

    for (int i = 0; i < *count; i++) {
        fprintf(file, "%s %s %d %d/%d/%d %s %d %s %s %d\n",
                stu[i].first_name, stu[i].last_name,
                stu[i].id,
                stu[i].birth.years,
                stu[i].birth.month,
                stu[i].birth.day,
                stu[i].gender,
                stu[i].national_code,
                stu[i].father_name,
                stu[i].major,
                stu[i].number_courses);

        for (int j = 0; j < stu[i].number_courses; j++) {
            fprintf(file, "%s  %s %.2f %d %d %d\n",
                    stu[i].book[j].lesson_name, 
                    stu[i].book[j].teacher_name,
                    stu[i].book[j].grade,
                    stu[i].book[j].course,
                    stu[i].book[j].lesson_code,
                    stu[i].number_all_courses);
        }
    }
    fclose(file);
}

void add_student(struct info stu[], int *count) {
    if (*count >= max_student) {
        printf("\nSorry, the list is full\n");
        return;
    }

    int i = *count;
    printf("\nid: ");
    scanf("%d", &stu[i].id);
    printf("first name: ");
    scanf("%s", stu[i].first_name);
    printf("last name: ");
    scanf("%s", stu[i].last_name);
    printf("date of birth (year month day): ");
    scanf("%d %d %d", &stu[i].birth.years, &stu[i].birth.month, &stu[i].birth.day);
    printf("gender: ");
    scanf("%s", stu[i].gender);
    printf("national code: ");
    scanf("%d",&stu[i].national_code);
    printf("father name: ");
    scanf("%s", stu[i].father_name);
    printf("major: ");
    scanf("%s", stu[i].major);
    
    stu[i].number_courses = 0;
    stu[i].number_all_courses = 0;
    
    (*count)++;
    update_file(stu, count);
    printf("\nStudent added successfully\n");
}

void remove_student(struct info stu[], int *count) {
    int i;
    int id;
    printf("enter id:");
    scanf("%d",&id);
    for (i = 0; i < *count; i++) {
        if (stu[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                stu[j] = stu[j + 1];
            }
            (*count)--;
            update_file(stu, count);
            printf("\nStudent removed successfully\n");
            return;
        }
    }
    printf("\nStudent not found\n");
}

void show(struct info stu[max_student],struct course book[],int *count){
  for(int i=0;i<*count;i++){
    printf("\nstudent%d\n        id:%d   name:%s %s   date birth:%d/%d/%d   gender:%s   national code:%d   father name:%s   major:%s\n"  
    ,i+1,stu[i].id,stu[i].first_name,stu[i].last_name,stu[i].birth.years,stu[i].birth.month,stu[i].birth.day
    ,stu[i].gender,stu[i].national_code,stu[i].father_name,stu[i].major);
    for(int j=0;j<stu[i].number_courses;j++){
      printf("        book%d:   lesson name:%s     theacher name:%s   cours:%d  grade:%.2f   code:%d  \n"
      ,j+1,stu[i].book[j].lesson_name,
      stu[i].book[j].teacher_name,stu[i].book[j].course,stu[i].book[j].grade,stu[i].book[j].lesson_code);
    }
    printf("        courses:%d\n",stu[i].number_all_courses);
  }
}

void add_lesson(struct info stu[max_student],int *count){  
int id,n;
int search_student=0;
printf("enter id:");
scanf("%d",&id);
for(int i=0;i<=*count;i++){
    if(id==stu[i].id){
        search_student=1;
        n=i;
    }    
}

if(search_student==0){
    printf("student not found\n");
}
else{
    printf("\n%s %s\n",stu[n].first_name,stu[n].last_name);
    if(stu[n].number_all_courses>=max_course){
        printf("oh sorry,courses is fully\n");
    } 
    else{
        printf("\nlesson name:");
        scanf("%s",stu[n].book[stu[n].number_courses].lesson_name);
        printf("course(1 or 2 or 3):");
        scanf("%d",&stu[n].book[stu[n].number_courses].course);
        if(stu[n].book[stu[n].number_courses].course<1||stu[n].book[stu[n].number_courses].course>3){
            printf("\nerror,try again\n");
            printf("course(1 or 2 or 3):");
            scanf("%d",&stu[n].book[stu[n].number_courses].course);
            printf("teacher name:");
            scanf("%s",stu[n].book[stu[n].number_courses].teacher_name);
            printf("grade(0<= grade <=20):");
            scanf("%f",&stu[n].book[stu[n].number_courses].grade);
            if(stu[n].book[stu[n].number_courses].grade<0||stu[n].book[stu[n].number_courses].grade>20){
                printf("\nerror,try again\n");
                printf("grade(0<= grade <=20):");
                scanf("%f",&stu[n].book[stu[n].number_courses].grade);
                printf("code:");
                scanf("%d",&stu[n].book[stu[n].number_courses].lesson_code);
                stu[n].number_all_courses=stu[n].number_all_courses+stu[n].book[stu[n].number_courses].course;
                stu[n].number_courses++;
                printf("\n\naddad lessons succesfully\n\n");
            }
            else{
                printf("code:");
                scanf("%d",&stu[n].book[stu[n].number_courses].lesson_code);
                stu[n].number_all_courses=stu[n].number_all_courses+stu[n].book[stu[n].number_courses].course;
                stu[n].number_courses++;
                printf("\n\naddad lessons succesfully\n\n");
            }
        }
        else{
            printf("teacher name:");
            scanf("%s",stu[n].book[stu[n].number_courses].teacher_name);
            printf("grade(0<= grade <=20):");
            scanf("%f",&stu[n].book[stu[n].number_courses].grade);
            printf("code:");
            scanf("%d",&stu[n].book[stu[n].number_courses].lesson_code);
            stu[n].number_all_courses=stu[n].number_all_courses+stu[n].book[stu[n].number_courses].course;
            stu[n].number_courses++;
            printf("\n\naddad lessons succesfully\n\n");
        }
    }     
}
update_file(stu,count);
}

void menu(){
printf("\n1.add student \n");
printf("2.show list\n");
printf("3.edit student \n");
printf("4.remove student\n");
printf("5.add lesson\n");
printf("6.edit lesson\n");
printf("7.remove lesson\n");
printf("8.search student id\n");
printf("9.search student national code\n");
printf("10.exit\n\n");
}

int edit_stu(struct info stu[max_student],struct course book[max_course],int *count){
  
 int id,i,n;
 int search_id=0;
 printf("\nenter id: ");
 scanf("%d",&id);  
 for( i=1;i<*count;i++){
  if(id==stu[i].id){
    search_id=1;
    n=i;
    }}
  if(search_id==0){
    printf("student not found\n");
  }
  else{
    printf("%s %s\n",stu[n].first_name,stu[n].last_name);
      printf("\nnew id(ex:403463133): ");
      scanf("%d",&stu[n].id);
      printf("new first name: ");
      scanf("%s",stu[n].first_name);
      printf("new last name: ");
      scanf("%s",stu[n].last_name);
      printf(">> date of birth << new year:");
      scanf("%d",&stu[n].birth.years);
      printf("                    new month: ");
      scanf("%d",&stu[n].birth.month);
      printf("                    new day: ");
      scanf("%d",&stu[n].birth.day);
      printf("new gender(male =  درم  ,   female =نز):");
      scanf("%s",stu[n].gender);
      printf("new national code:");
      scanf("%d",&stu[n].national_code);
      printf("new father name:");
      scanf("%s",stu[n].father_name);
      printf("new major(ex:computer engineering):");
      scanf("%s",stu[n].major);
      update_file(stu,count);
   }

}

void ser_id(struct info stu[max_student],int *count){
  int id,i;
  int search=0;
  printf("enter id:");
  scanf("%d",&id);
  for(int n=0;n<=*count;n++){
    if(id==stu[n].id){
      search=1;
      i=n;
    }
  }
  if(search==1){
     printf("student%d\n        id:%d   name:%s%s   date birth:%d/%d/%d   gender:%s   national code:%d   father name:%s   major:%s\n"  
    ,i+1,stu[i].id,stu[i].first_name,stu[i].last_name,stu[i].birth.years,stu[i].birth.month,stu[i].birth.day
    ,stu[i].gender,stu[i].national_code,stu[i].father_name,stu[i].major);
  

  }else{
    printf("a student not found\n");
  }

}

void ser_national_code(struct info stu[max_student],int *count){
  int national_code ,i,search=0 ;
  printf("enter national code:");
  scanf("%d",&national_code);
  for(int n=0;n<=*count;n++){
    if(national_code==stu[n].national_code){
      search=1;
      i=n;
    }
  }
  if(search==1){
     printf("student%d\n        id:%d   name:%s%s   date birth:%d/%d/%d   gender:%s   national code:%d   father name:%s   major:%s\n"  
    ,i+1,stu[i].id,stu[i].first_name,stu[i].last_name,stu[i].birth.years,stu[i].birth.month,stu[i].birth.day
    ,stu[i].gender,stu[i].national_code,stu[i].father_name,stu[i].major);
  }
  else{
    printf("a student not found\n");
  }
}

void edit_lesson(struct info stu[max_student],struct course book[max_course],int *count){
  int i,id,n,m;
  int search_student=0;
  int serach_lesson=0;
  int lesson_code;
  printf("enter id:");
  scanf("%d",&id);
  for(int i=0;i<=*count;i++){
    if(id==stu[i].id){
      search_student=1;
      n=i;
    }
  }  
    if(search_student==0){
      printf("student not found\n");
    }
    else{
      printf("%s %s  \n",stu[n].first_name,stu[n].last_name);
      printf("enter lesson code:");
      scanf("%d",&lesson_code);
      for(int j=0;j<stu[n].number_courses;j++){
        if(lesson_code==stu[n].book[j].lesson_code){
          serach_lesson=1;
          m=j;
        }
      }
      if(serach_lesson==0){
        printf("lesson not found\n");
      }
      else{
        stu[n].number_all_courses=stu[n].number_all_courses-stu[n].book[m].course;
          printf("new name lesson:");
          scanf("%s",stu[n].book[m].lesson_name);
          printf("new course(1 or 2 or 3):");
          scanf("%d",&stu[n].book[m].course);
          printf("new teacher name:");
          scanf("%s",stu[n].book[m].teacher_name);
          printf("new grade:");
          scanf("%f",&stu[n].book[m].grade);
          printf("new code:");
          scanf("%d",&stu[n].book[m].lesson_code);
          printf("\n edit lesson succesfully\n");
          stu[n].number_all_courses=stu[n].number_all_courses+stu[n].book[m].course;
        }
            }
      update_file(stu,count);
    } 


void remove_lesson(struct info stu[max_student],struct course book[max_course],int *count){
  int id,lesson_code,n,m;
  int search_student=0;
  int serach_lesson=0;
  printf("enter id:");
  scanf("%d",&id);
  for(int i=0;i<=*count;i++){
    if(id==stu[i].id){
      search_student=1;
      n=i;
    }
  }  
    if(search_student==0){
      printf("student not found\n");
    }
    else{
      printf("%s %s  \n",stu[n].first_name,stu[n].last_name);
      printf("enter lesson code:");
      scanf("%d",&lesson_code);
      for(int j=0;j<stu[n].number_courses;j++){
        if(lesson_code==stu[n].book[j].lesson_code){
          serach_lesson=1;
          m=j;
        }
      }
      if(serach_lesson==0){
        printf("lesson not found\n");
      }
      else{
          strcpy(stu[n].book[m].lesson_name,stu[n].book[m+1].lesson_name);
          stu[n].book[m].course=stu[n].book[m+1].course;
          strcpy(stu[m].book[m].teacher_name,stu[n].book[m+1].teacher_name);
          stu[n].book[m].grade=stu[n].book[m+1].grade;
          stu[n].book[m].lesson_code=stu[n].book[m+1].lesson_code;
          printf("\nremove lesson succesfully\n");
          stu[n].number_courses--;
          stu[n].number_all_courses=stu[n].number_all_courses-stu[n].book[m+1].course;
        }
      }
      update_file(stu,count);
    }


int main(){
  struct info stu[max_student];
  struct course book[max_course];
  printf("\nheloo\n");
  int count =0;
  int choose;
  int j;
  read_file(stu, &count);
  do{
    menu();
    printf("\nchoose number :");
    scanf("%d",&choose);

    switch(choose){
      case 1: add_student(stu,&count); break;
      case 2: show(stu,book,&count); break;
      case 3: edit_stu(stu,book,&count); break;
      case 4: remove_student(stu,&count); break;
      case 5: add_lesson(stu,&count); break;
      case 6: edit_lesson(stu,book,&count); break;
      case 7: remove_lesson(stu,book,&count); break;
      case 8: ser_id(stu,&count); break;
      case 9: ser_national_code(stu,&count); break;
      case 10: printf("\ngoodby!\n\n"); break;

    }}while(choose!=10); 
}