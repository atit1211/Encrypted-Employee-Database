#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<string.h>
#include<conio.h>
FILE *f;
struct node
{
	int key;
    int level;
    int salary;
    int id;
	char name[11];
	char phno[11];
    char email[21];
	struct node* child1;
	struct node* child2;
    struct node* child3;
};
struct node* admin=NULL;
struct node* pnode=NULL;
void dealoc(struct node* ptr)
{
    if(ptr==NULL)
        return;
    dealoc(ptr->child1);
    dealoc(ptr->child2);
    dealoc(ptr->child3);
    free(ptr);
}
void del(struct node* follow,struct node* ptr,int key)
{
    if(ptr==NULL)
    {
        return;
    }
    if (ptr->key==key)
    {   
        if(ptr==follow->child1)
            follow->child1=NULL;
        else if(ptr==follow->child2)
            follow->child2=NULL;
        else if(ptr==follow->child3)
            follow->child3=NULL;
        dealoc(ptr);
        return;
    }
    del(ptr,ptr->child1,key);
    del(ptr,ptr->child2,key);
    del(ptr,ptr->child3,key);
}
void upointer(int key,struct node* ptr)//returns the universal node pointer
{
    if(ptr==NULL)
        return;
    if(key==ptr->key)
    {
        pnode=ptr;
    }
    upointer(key,ptr->child1);
    upointer(key,ptr->child2);
    upointer(key,ptr->child3);
}
void flevel(int level,struct node* ptr)//printing employes at a certain level with key
{
    if(ptr==NULL)
        return;
    if(ptr->level==level)
    {
        printf("\n%d   ",ptr->key);
        puts(ptr->name);   
    }
    flevel(level,ptr->child1);
    flevel(level,ptr->child2);
    flevel(level,ptr->child3);
}
void add()
{
    system("cls");
    struct node* new,*ptr;
    char name[11],phno[10],email[100];
    int key,temp,flag=0,level;
    new=(struct node*)malloc(sizeof(struct node));
    new->child1=NULL;
    new->child2=NULL;
    new->child3=NULL;
    printf("enter the level of the employee:-\n");
    printf("level 1\nlevel 2\nlevel 3\n");
    scanf("%d",&level);
    new->level=level;
    if(level==1&&admin->child1!=NULL&&admin->child2!=NULL&&admin->child3!=NULL)
    {
        printf("new employee cannot be added at this level\n");
        printf("all position are occupied\n");
        free(new);
        return;
    }
    printf("Enter the details:-\n");
    printf("1:Name(first name only. max 10 characters):");
    scanf("%s",&name);
    strcpy(new->name,name);
    printf("2:Phone number(10 digits):");
    scanf("%s",&phno);
    strcpy(new->phno,phno);
    printf("3:Email address(max 20 Characters):");
    scanf("%s",&email);
    strcpy(new->email,email);
    printf("4:Employee ID(max 2 digits):");
    scanf("%d",&new->id);
    printf("5.Enter the Employee Salary(max 9,00,000):-");
    scanf("%d",&new->salary);
    printf("enter the key for who must the employee be added under");
    flevel(level-1,admin);
    printf("key:-");
    scanf("%d",&key);
    upointer(key,admin);
    if(pnode==NULL)
    {
        printf("ERROR!!!!!\nemployee canot be added\n");
        getch();
        return;
    }
    if(pnode->child1==NULL)
    {
        pnode->child1=new;
        temp=pnode->key;
        new->key=1*pow(10,level-1)+temp;
        printf("employee added succesfully\n");
    }
    else if(pnode->child2==NULL)
    {
        pnode->child2=new;
        temp=pnode->key;
        new->key=2*pow(10,level-1)+temp;
        printf("employee added succesfully\n");
    }
    else if(pnode->child3==NULL)
    {
        pnode->child3=new;
        temp=pnode->key;
        new->key=3*pow(10,level-1)+temp;
        printf("employee added succesfully\n");
    }
    else
    {
        printf("employee can't be added under this key\nall positions are occupied\n");
        return;
    }
    pnode=NULL;
    getch();
    return;
}
void display()
{
    int key;
    struct node* poi;
    struct node* ptr;
    //system("cls");
    printf("enter the key of the employee you want to search for\n(or enter 0 to display all)\nkey:-");
    scanf("%d",&key);
    if(key==0)
    {
        flevel(1,admin);
        printf("\n");
        flevel(2,admin);
        printf("\n");
        flevel(3,admin);
        printf("\n");
        printf("enter the key of the employee you want to search for\nkey:-");
        scanf("%d",&key);
    }
    upointer(key,admin);
    system("cls");
    if(pnode==NULL)
        return;
    printf("details of the employee:\n");
    printf("name:-%s\n",pnode->name);
    printf("ID:-%d\n",pnode->id);
    printf("key:-%d\n",pnode->key);
    printf("Phno:-%s\n",pnode->phno);
    printf("email:-%s\n",pnode->email);
    printf("people overseeing:\n");
    if(pnode->child1!=NULL)
    {   
        poi=pnode->child1;
        printf("%s\n",poi->name);
    }
    if(pnode->child2!=NULL)
    {    
        poi=pnode->child2;
        printf("%s\n",poi->name);
    }
    if(pnode->child3!=NULL)
    {
        poi=pnode->child3;
        printf("%s\n",poi->name);
    }
    pnode=NULL;
    getch();
}
void file_write(struct node* ptr)
{
    int pos,i;
    char buf[21];
    static int ref=64;
    static int count=1;
    struct node node;
    if (ptr==NULL)
    {
        return;
    }
    node.key=ptr->key+123;
    node.id=ptr->id+53;
    node.level=ptr->level+142;
    node.salary=ptr->salary+74563;
    strcpy(buf,ptr->name);
    for ( i = 0; i < 11; i++)
    {
        if (buf[i]=='\0')
        {
            node.name[i]=buf[i];
            break;
        }
        
        node.name[i]=(char)((int)buf[i]+1);
    }
    strcpy(buf,ptr->phno);
    for ( i = 0; i < 11; i++)
    {
        if (buf[i]=='\0')
        {
            node.phno[i]=buf[i];
            break;
        }
        
        node.phno[i]=(char)((int)buf[i]+1);
    }
    strcpy(buf,ptr->email);
    for ( i = 0; i < 21; i++)
    {
        if (buf[i]=='\0')
        {
            node.email[i]=buf[i];
            break;
        }
        
        node.email[i]=(char)((int)buf[i]+1);
    }
    fprintf(f,"                                                              ");
    pos=(ref*count)+0;
    fseek(f,pos,SEEK_SET);
    fprintf(f,"%d",node.key);
    pos=(ref*count)+4;
    fseek(f,pos,SEEK_SET);
    fprintf(f,"%d",node.id);
    pos=(ref*count)+8;
    fseek(f,pos,SEEK_SET);
    fprintf(f,"%d",node.level);
    pos=(ref*count)+14;
    fseek(f,pos,SEEK_SET);
    fprintf(f,"%s",node.name);
    pos=(ref*count)+25;
    fseek(f,pos,SEEK_SET);
    fprintf(f,"%s",node.phno);
    pos=(ref*count)+36;
    fseek(f,pos,SEEK_SET);
    fprintf(f,"%d",node.salary);
    pos=(ref*count)+44;
    fseek(f,pos,SEEK_SET);
    fprintf(f,"%s ",node.email);
    fseek(f,0,SEEK_END);
    fprintf(f,"\n");
    count++;
    file_write(ptr->child1);
    file_write(ptr->child2);
    file_write(ptr->child3);
}
int file_tree(int count2)
{
    struct node* ptr;
    struct node node;
    int pos,i,j,temp,end;
    int pkey,flag=0;
    static int ref=64;
    char buf[21];
    fseek(f,0,SEEK_END);
    end=ftell(f);
    if(end<=129)
    {
        return 0;
    }
    pos=(ref*count2)+0;
    fseek(f,pos,SEEK_SET);
    fscanf(f,"%d",&node.key);
    pos=(ref*count2)+4;
    fseek(f,pos,SEEK_SET);
    fscanf(f,"%d",&node.id);
    pos=(ref*count2)+8;
    fseek(f,pos,SEEK_SET);
    fscanf(f,"%d",&node.level);
    pos=(ref*count2)+14;
    fseek(f,pos,SEEK_SET);
    fscanf(f,"%s",&node.name);
    pos=(ref*count2)+25;
    fseek(f,pos,SEEK_SET);
    fscanf(f,"%s",&node.phno);
    pos=(ref*count2)+36;
    fseek(f,pos,SEEK_SET);
    fscanf(f,"%d",&node.salary);
    pos=(ref*count2)+44;
    fseek(f,pos,SEEK_SET);
    fscanf(f,"%s",&node.email);
    if (ftell(f)<end-21)
    {
        flag=1;
    }
    ptr=(struct node*)malloc(sizeof(struct node));
    ptr->key=node.key-123;
    ptr->id=node.id-53;
    ptr->level=node.level-142;
    ptr->salary=node.salary-74563;
    for ( i = 0; i < 11; i++)
    {
        if (node.name[i]=='\0')
        {
            buf[i]=node.name[i];
            break;
        }
        
        buf[i]=(char)((int)node.name[i]-1);
    }
    strcpy(ptr->name,buf);
    for ( i = 0; i < 11; i++)
    {
        if (node.phno[i]=='\0')
        {
            buf[i]=node.phno[i];
            break;
        }
        
        buf[i]=(char)((int)node.phno[i]-1);
    }
    strcpy(ptr->phno,buf);
    for ( i = 0; i < 21; i++)
    {
        if (node.email[i]=='\0')
        {
            buf[i]=node.email[i];
            break;
        }
        
        buf[i]=(char)((int)node.email[i]-1);
    }
    strcpy(ptr->email,buf);
    ptr->child1=NULL;
    ptr->child2=NULL;
    ptr->child3=NULL;
    pkey=ptr->key;
    if (pkey>100)
    {
        pkey=pkey%100;
    }
    else if(pkey>10&&pkey<100)
    {
        pkey=pkey%10;
    }
    else
    {
        pkey=0;
    }
    upointer(pkey,admin);
    if(pnode->child1==NULL)
    {
        pnode->child1=ptr;
        temp=pkey;
        ptr->key=1*pow(10,ptr->level-1)+pkey;
    }
    else if(pnode->child2==NULL)
    {
        pnode->child2=ptr;
        temp=pkey;
        ptr->key=2*pow(10,ptr->level-1)+pkey;
    }
    else if(pnode->child3==NULL)
    {
        pnode->child3=ptr;
        temp=pkey;
        ptr->key=3*pow(10,ptr->level-1)+pkey;
    }
    else
    {
        printf("employee can't be added under this key\nall positions are occupied\n");
        return 0;
    }
    pnode=NULL;
    if (flag==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
int main()
{
    char str[100],pass[100],emp[100];
    int option=0,key,i;
    int pos,stat=1,co;
    char ch;
    f=fopen("data.txt","r+");
    admin=(struct node*)malloc(sizeof(struct node));
    admin->child1=NULL;
    admin->child2=NULL;
    admin->child3=NULL;
    admin->key=0;
    admin->salary=125000;
    strcpy(admin->name,"admin");
    strcpy(admin->email,"admin@com.inc.com");
    admin->id=00;
    admin->level=0;
    strcpy(admin->phno,"080-777777");
    fseek(f,0,SEEK_END);
    if(ftell(f)>0)
    {
        fseek(f,0,SEEK_SET);
        co=2;
        while(stat)
        {
            stat=file_tree(co);
            co++;
        }
    }
    system("cls");
    printf("enter the Admin Password\n");
    i=0; 
    do{ 
        pass[i]=getch(); 
        if(pass[i]!='\r'){ 
            printf("*"); 
        } 
        i++; 
    }while(pass[i-1]!='\r'); 
    pass[i-1]='\0'; 
    printf("\n");
    if(strcmp(pass,"atit1234\0")!=0)
    {
        printf("wrong password\nACCESS DENIED\n");
        return 0;
    }
    else
    {
        printf("ACCESS GRANTED\n");
    }
    while(option==1||option==2||option==3||option==0)
    {
        printf("select an operation\n");
        printf("1:Add Employee\t2:Remove Employee\t3:Get Employee details\t4:exit\n");
        scanf("%d",&option);
        if(option==1)
            add();
        else if(option==2)
        {
            flevel(1,admin);
            flevel(2,admin);
            flevel(3,admin);
            printf("enter the key of the employee you want to delete\n");
            scanf("%d",&key);
            del(NULL,admin,key);
            printf("employee removed successfuly\n");
            getch();
        }
        else if(option==3)
        {    
            display();
        }
        system("cls");
    }
    fclose(f);
    f=fopen("data.txt","w+");
    fprintf(f,"Key ID  Level Name       Phno       Salary  E-mail            \n");
    file_write(admin);
    fseek(f,0,SEEK_END);
    fclose(f);
    printf("Thankyou for using the program\nDATA-BASE LOCKED\n");
    getch();
    return 0;
}