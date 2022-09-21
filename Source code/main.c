#include <stdio.h>
#include "wallet.h"
#include <stdlib.h>
#include<string.h>
#include<conio.h>

typedef struct Date{
    int year,month,day;
}Date;
typedef struct Data{
    Date date;
    char type[20+1];
    char category[20+1];
    int amount;
    struct Data *next;
    }Data;

//Add information for each entry
void write()
{
   struct Data d[50];
   char c;
    FILE *fptr=fopen("Wallet.txt","w");
    if(fptr==NULL){
        printf("File does not exist");
    }

    int i=0;
    do{
    printf("Enter date\n");
    printf("Day: ");
    scanf("%d",&d[i].date.day);
    fprintf(fptr,"%d ",d[i].date.day);
    printf("Month: ");
    scanf("%d",&d[i].date.month);
    fprintf(fptr,"%d ",d[i].date.month);
    printf("Year: ");
    scanf("%d",&d[i].date.year);
    fprintf(fptr,"%d ",d[i].date.year);
    printf("Enter type: ");
    scanf("%s", d[i].type);
    fprintf(fptr,"%s ",d[i].type);
    printf("Enter category:");
    scanf("%s", d[i].category);
    fprintf(fptr,"%s ",d[i].category);
    printf("Enter amount:");
    scanf("%d",&d[i].amount);
    fprintf(fptr,"%d\n",d[i].amount);



    ++i;

    printf("\n\nDo you want to add another entry?, press [y/n]\n");
    scanf(" %c",&c);

    }while(c=='y'||c=='Y');

    fclose(fptr);

}

//Add new entry to the database
void add_new_entry(){
    struct Data data;
    char ch;
    FILE *fptr = fopen("Wallet.txt","a+");
     if(fptr==NULL){
        printf("File does not exist");
    }

    printf("Enter date\n\n");
    printf("Day: ");
    scanf("%d",&data.date.day);
    printf("Month: ");
    scanf("%d",&data.date.month);
    printf("Year: ");
    scanf("%d",&data.date.year); printf("\n");
    printf("Enter type: ");
    scanf("%s", data.type);  printf("\n");
    printf("Enter category:");
    scanf("%s", data.category);  printf("\n");
    printf("Enter amount:");
    scanf("%d",&data.amount);

    fprintf(fptr,"\n");
    fprintf(fptr,"%d ",data.date.day);
    fprintf(fptr,"%d ",data.date.month);
    fprintf(fptr,"%d ",data.date.year);
    fprintf(fptr,"%s ",data.type);
    fprintf(fptr,"%s ",data.category);
    fprintf(fptr,"%d",data.amount);


    printf("\n\nDo you want to add more entry? pres [y/n]: ");
    scanf(" %c",&ch);

    printf("\n\n");


    if(ch=='y'||ch=='Y')
        add_new_entry();

}



//view data from file or load data
void view_data(){

            Data *head=NULL,*new_el;

        char tmp_type[20+1],tmp_cat[20+1];
        int tmp_day,tmp_mon,tmp_year,tmp_amount;

        FILE *fptr = fopen("Wallet.txt","r");
         if(fptr==NULL){
        printf("File does not exist");
    }

        while(fscanf(fptr,"%d %d %d %20s %20s %d",&tmp_day,&tmp_mon,&tmp_year,tmp_type,tmp_cat,&tmp_amount) !=EOF)
            {

            new_el = (Data*)malloc(sizeof(Data));

            new_el->date.day = tmp_day;
            new_el->date.month = tmp_mon;
            new_el->date.year = tmp_year;
            strcpy(new_el->type,tmp_type);
            strcpy(new_el->category,tmp_cat);
            new_el->amount = tmp_amount;
            new_el->next = head;
            head = new_el;

        }

        printf("Date\t\tTYPE\t\tCATEGORY\tAMOUNT(HUF)\n");

        while(head!=NULL){

          printf("%d.%d.%d\t",head->date.day,head->date.month,head->date.year);
          printf("%s\t\t",head->type);
          printf("%s\t\t",head->category);
          printf("%d\n",head->amount);

          head = head->next;
        }
       printf("\n\n");
        free(head);
        fclose(fptr);
}
//Calculate the total income, expenses and total balance
void total()
 {

        Data *head=NULL,*new_el;
        int total_inc=0,total_exp=0,total_bal;
        char tmp_type[20+1],tmp_cat[20+1];
        int tmp_day,tmp_mon,tmp_year,tmp_amount;

        FILE *fptr = fopen("Wallet.txt","r");
         if(fptr==NULL){
        printf("File does not exist");
    }

        while(fscanf(fptr,"%d %d %d %20s %20s %d",&tmp_day,&tmp_mon,&tmp_year,tmp_type,tmp_cat,&tmp_amount) !=EOF)
            {

            new_el = (Data*)malloc(sizeof(Data));
            strcpy(new_el->type,tmp_type);
            new_el->amount = tmp_amount;
            new_el->next = head;
            head = new_el;


        }
        while(head!=NULL){

             if(strstr(head->type,"income") != NULL)
               {
                   total_inc+=head->amount;
               }
               if(strstr(head->type,"expense") != NULL)
               {
                   total_exp+=head->amount;

               }

               head = head->next;
            }

            total_bal = total_inc-total_exp;
            printf("your total amount of income is: %d HUF\n",total_inc);
            printf("Your total amount of expenses is: %d HUF\n",total_exp);
            printf("Your total balance is: %d HUF\n\n",total_bal);

             free(head);
            fclose(fptr);

 }


//Display the most expensive category and money spent for that
 void most_exp_cat()
 {

        Data *head=NULL,*new_el;
        int max=0;
        char tmp_type[20+1],tmp_cat[20+1],cat_name[20+1];
        int tmp_day,tmp_mon,tmp_year,tmp_amount;

        FILE *fptr = fopen("Wallet.txt","r");
         if(fptr==NULL){
        printf("File does not exist");
    }

        while(fscanf(fptr,"%d %d %d %20s %20s %d",&tmp_day,&tmp_mon,&tmp_year,tmp_type,tmp_cat,&tmp_amount) !=EOF)
            {

            new_el = (Data*)malloc(sizeof(Data));
            strcpy(new_el->type,tmp_type);
            strcpy(new_el->category,tmp_cat);
            new_el->amount = tmp_amount;
            new_el->next = head;
            head = new_el;
             }

        while(head!=NULL){

             if((strstr(head->type,"expense") != NULL) && (head->amount>max))
            {
                max = head->amount;
                strcpy(cat_name,head->category);
            }


               head = head->next;
            }

///////////////////////////////

                printf("\nMost expensive category is: %s\n",cat_name);
                printf("And amount spent for this is: %d HUF\n\n",max);


              free(head);

            fclose(fptr);

 }


//Add new category to the database
 void addNEW_cat(){

     struct Data d;

     FILE *fptr = fopen("Wallet.txt","a+");
      if(fptr==NULL){
        printf("File does not exist");
    }

     printf("Enter date:\n\n");
     printf("Enter day: ");
     scanf("%d",&d.date.day);
     printf("Enter month: ");
     scanf("%d",&d.date.month);
     printf("Enter year: ");
     scanf("%d",&d.date.day);  printf("\n");
     printf("Enter category type: ");
     scanf("%s",d.type);   printf("\n");
     printf("Enter category name: ");
     scanf("%s",d.category);  printf("\n");
     printf("Enter amount: ");
     scanf("%d",&d.amount);
     printf("\n\n");
     char cat[20+1];
     strcpy(cat,d.category);


     Data *head=NULL,*new_el;
        char tmp_type[20+1],tmp_cat[20+1];
        int tmp_day,tmp_mon,tmp_year,tmp_amount;


      while(fscanf(fptr,"%d %d %d %20s %20s %d",&tmp_day,&tmp_mon,&tmp_year,tmp_type,tmp_cat,&tmp_amount) !=EOF)
            {

            new_el = (Data*)malloc(sizeof(Data));
            strcpy(new_el->category,tmp_cat);
            new_el->next = head;
            head = new_el;
             }

      while(head!=NULL){
        if(strstr(head->category,cat)!=NULL){
            printf("You already have this category\nAdd new one...\n\n ");
            addNEW_cat();
            return;
        }
        head = head->next;
      }

      fprintf(fptr,"%d ",d.date.day);
      fprintf(fptr,"%d ",d.date.month);
      fprintf(fptr,"%d ",d.date.year);
      fprintf(fptr,"%s ",d.type);
      fprintf(fptr,"%s ",d.category);
      fprintf(fptr,"%d ",d.amount);

      printf("\n\n");

      fclose(fptr);
 }

//Display information for each category for user selected time period
 void usr_selected_duration(){

     int st_day,st_month,end_day,end_month,st_year,end_year;
     printf("Enter start date:\n");
     printf("day: "); scanf("%d",&st_day);
     printf("month: "); scanf("%d",&st_month);
     printf("year: "); scanf("%d",&st_year);

     printf("\n\nEnter end date:\n");
     printf("day: "); scanf("%d",&end_day);
     printf("month: "); scanf("%d",&end_month);
     printf("year: "); scanf("%d",&end_year);
     printf("\n\n");

     if(st_month>end_month||st_year>end_year){
        printf("Wrong date, enter valid date...\n\n");
        usr_selected_duration();
        return;
     }


      Data *head=NULL,*new_el;
        char tmp_type[20+1],tmp_cat[20+1];
        int tmp_day,tmp_mon,tmp_year,tmp_amount;

        FILE *fptr = fopen("Wallet.txt","r");
         if(fptr==NULL){
        printf("File does not exist");
    }

        while(fscanf(fptr,"%d %d %d %20s %20s %d",&tmp_day,&tmp_mon,&tmp_year,tmp_type,tmp_cat,&tmp_amount) !=EOF)
            {

            new_el = (Data*)malloc(sizeof(Data));
            new_el->date.day= tmp_day;
            new_el->date.month=tmp_mon;
            new_el->date.year=tmp_year;
            strcpy(new_el->type,tmp_type);
            strcpy(new_el->category,tmp_cat);
            new_el->amount = tmp_amount;
            new_el->next = head;
            head = new_el;
             }
             printf("Date\t\tTYPE\t\tCATEGORY\tAMOUNT(HUF)\n");

    while(head!=NULL){
     if((new_el->date.day>=st_day&&new_el->date.month>=st_month)&&(new_el->date.day<=end_day&&new_el->date.month<=end_month))
        {

          printf("%d.%d.%d\t",head->date.day,head->date.month,head->date.year);
          printf("%s\t\t",head->type);
          printf("%s\t\t",head->category);
          printf("%d\n",head->amount);

          head = head->next;
        }
    }
             printf("\n\n");
             free(head);
         fclose(fptr);
      }


 void main_menue_2(){
    int choice;
    do{
    printf("1.View the database\n");
    printf("2.Add a new entry to the database\n");
    printf("3.Create new category\n");
    printf("4.Display total income, expense and balance you have\n");
    printf("5.Display most expensive category and money for that category\n");
    printf("6.Display statics for each category for user selected time period\n");
    printf("7.Exit\n\n");

    printf("Enter your choice: ");
    scanf("%d",&choice);
    printf("\n\n");


    switch(choice){
    case 1:
        view_data();
        break;
    case 2:
        add_new_entry();
        break;
    case 3:
        addNEW_cat();
        break;
    case 4:
        total();
        break;
    case 5:
        most_exp_cat();
        break;
    case 6:
        usr_selected_duration();
        break;
    case 7:
        return;
        break;
    }
    }while(choice>=1&&choice<=7);
}


    void main_menue_1(){

        int choice;
        do{
        printf("   MAIN MENU\n\n");
        printf("1.Load the database\n");
        printf("2.Create a new database\n");
        printf("3.Exit\n\n");

        printf("Enter your choice: ");
        scanf("%d",&choice);
        printf("\n\n");

        switch(choice){
        case 1:
            main_menue_2();
            break;

        case 2:
            write();

        case 3:
            return;
            break;
        }
        }while(choice>=1&&choice<=3);
    }





int main()
{

 printf("\n\n\n");
 printf("\t\t%%WELCOME TO THE WALLET DATABASE%%\n\n\n\n");
 main_menue_1();

    return 0;
}
