#include<stdio.h>
#include<process.h>
#include<string.h>
#include<stdlib.h>

struct student{
    char prn[12];
    char name[25];
    float per;
}*a;
int cnt=0;

int validatePerc(float p)
{
    if(p<0 || p>100)
      return 0;
    else
      return 1;
}

int validatePRN(char p[])
{
    int x;
    if(strlen(p)!=11)
      return 0;
    for(x=0;p[x]!='\0';p++)
      {
          if(p[x]<48 || p[x]>57)
             return 0;
      }
    return 1;
}

void create()                //creates multiple records at one go
{
    int n,i;
    printf("\nEnter how many records you want to enter :");
    scanf("%d",&n);
    a=(struct student*)malloc(n*sizeof(struct student));
    for(i=0;i<n;i++)                     
      {
          printf("\nEnter PRN : ");
          fflush(stdin);
          gets((a+i)->prn);
          while(!validatePRN((a+i)->prn))
           {
               printf("\nInvalid PRN! Enter only digits from 0 to 9:");
               fflush(stdin);
               gets((a+i)->prn);
           }
          printf("\nEnter name : ");
          fflush(stdin);
          gets((a+i)->name);
          printf("\nEnter percentage : ");
          scanf("%f",&((a+i)->per));
          while(!validatePerc((a+i)->per))
             {
                 printf("\nInvalid input for percentage!Enter again between 0 to 100: ");
                 scanf("%f",&((a+i)->per));
             }
          cnt++;       //keeps the track of no of records entered
      } 
    printf("\n\nCreated Successfully!\n");
}
void delete()
{
    int pos=search();                      //returns the position of element searched
    if(pos==-1)
        printf("\nRecord not found!");
    else
    {
      while(pos<cnt-1)                           //shift the elements to left from pos to last index of the structure array
        {
             *(a+pos)=*(a+pos+1);
             pos++;
        }  
     cnt--;  
     a=(struct student *)realloc(a,cnt*sizeof(struct student));                                     //decrement count since one record is deleted
     printf("\nRecord Deleted successfully!\n");
    }
}
void insert()                          //insert only one record
{
    cnt++;
    a=(struct student *)realloc(a,cnt*sizeof(struct student));
    printf("\nEnter PRN : ");
    fflush(stdin);
    gets((a+cnt-1)->prn);
    while(!validatePRN((a+cnt-1)->prn))
        {
           printf("\nInvalid PRN! Enter only digits from 0 to 9:");
           fflush(stdin);
           gets((a+cnt-1)->prn);
        }
    printf("\nEnter name : ");
    fflush(stdin);
    gets((a+cnt-1)->name);
    printf("\nEnter percentage : ");
    scanf("%f",&((a+cnt-1)->per));
    while(!validatePerc((a+cnt-1)->per))
     {
         printf("\nInvalid input for percentage!Enter again between 0 to 100: ");
         scanf("%f",&((a+cnt-1)->per));
     }
    printf("\n\nInsertion Successful!\n");                                     //update the total no of records
}
int search()
{
    char prn[12];
    int i;
    printf("\nEnter PRN : ");
    fflush(stdin);
    gets(prn);
    while(!validatePRN(prn))
      {
         printf("\nInvalid PRN! Enter only digits from 0 to 9:");
         fflush(stdin);
         gets(prn);
     }
    for(i=0;i<cnt;i++)
      {
          if(strcmp((a+i)->prn,prn)==0)
            {
                printf("\nStudent Name: %s",(a+i)->name);
                printf("\nPRN: %s",(a+i)->prn);
                printf("\nPercentage: %f",(a+i)->per);
                return i;
            }
      }
    return -1;
}
void modify()
{
    int pos=search();
    int chng;
    if(pos==-1)
       printf("\nRecord not found!");
    else
    {
        printf("\n\nStudent name: %s",(a+pos)->name);
        printf("\nEnter 1 to change, 0 to retain : ");
        scanf("%d",&chng);
        if(chng==1)
           {
               printf("\nEnter new name: ");
               fflush(stdin);
               gets((a+pos)->name);
               printf("\nName changed!");
           }
        else
             printf("\nKeeping the old name!");
        
        printf("\nPercentage: %f",(a+pos)->per);
        printf("\nEnter 1 to change, 0 to retain : ");
        scanf("%d",&chng);
        if(chng==1)
           {
               printf("\nEnter new percentage : ");
               scanf("%f",&((a+pos)->per));
                while(!validatePerc((a+pos)->per))
                  {
                     printf("\nInvalid input for percentage!Enter again between 0 to 100: ");
                     scanf("%f",&((a+pos)->per));
                  }
               printf("\nPercentage Modified!");
           }
        else
           printf("\nKeeping the old percentage!");
        printf("\nRecord Modified!");
    }    
}

void display()
{
   int i;
   printf("\n\tPRN\tStudent Name\tPercentage");
   for(i=0;i<cnt;i++)
      printf("\n\t%s\t%s\t%f",(a+i)->prn,(a+i)->name,(a+i)->per);
}

int main()
{
    int opt;
    printf("\n Student details: ");
    printf("\n Creating student database ");
    create();
    while(1)
    {
      printf("\n1. Display all records ");
      printf("\n2. Search by PRN ");
      printf("\n3. Delete a record ");
      printf("\n4.. Insert a record");
      printf("\n5. Modify a record");
      printf("\n6. Exit");
      printf("\nEnter your choice: ");
      fflush(stdin);
      scanf("%d",&opt);
      switch(opt)
       {   
           case 1:
              display();
              break;
        
           case 2:
               if(search()==-1)
                  printf("\nRecord not found!");
               break;
            
           case 3:
              delete();
              break;
            
           case 4:
               insert();
               break;
            
           case 5:
               modify();
               break;
            
            case 6: 
                free(a);
                exit(0);
          default:
              printf("\nInvalid choice!");
       }
    }
}
