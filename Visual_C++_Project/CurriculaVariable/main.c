#include<stdio.h>
#include<stdlib.h>

/* 结构体相关 --------------------------------------------------------------------*/

int N1,N2,kk1,kk2,kk3;
struct couse * head1;
struct student * head2;
struct couse  //课程信息结构体
{
    int num1;
    char name1[20];
    int score;
    int nelepeo;  //课程已选人数
    int Melepeo;  //课程人数上限
    struct couse * next;
};
struct student//学生信息结构体
{
    int num2;
    char name2[20];
    int nelenum[50];  //已选课程编号
    int nelen;  //已选课程数量
    struct student * next;
};

void Ms()
{
    for(kk1=0;kk1<1100;kk1++)
                for(kk2=0;kk2<1200;kk2++)
                    for(kk3=0;kk3<1200;kk3++);
}

/* 文件加载模块 ------------------------------------------------------------------------*/

void readfile_course()  //加载课程信息
{
    FILE * fp;
    char filepath[20];
    struct couse *p1,*p2;
    N1=0;
    fp=fopen("info-course.txt","r");
    if((fp=fopen("info-course.txt","r"))==NULL)
    {
        printf("+---------------------------------------------------------+\n");
        printf("| 找不到info-course.txt文件!                               |\n");
        exit(0);
    }
    p1=p2=(struct couse*)malloc(sizeof(struct couse));
    fscanf(fp,"%d%s%d%d%d",&p1->num1,p1->name1,&p1->score,&p1->nelepeo,&p1->Melepeo);
    head1=NULL;
    while(!feof(fp))
    {
        N1=N1+1;
        if(N1==1)head1=p1;
        else p2->next=p1;
        p2=p1;
        p1=(struct couse * )malloc(sizeof(struct couse));
        fscanf(fp,"%d%s%d%d%d",&p1->num1,p1->name1,&p1->score,&p1->nelepeo,&p1->Melepeo);
    }
    p2->next=NULL;
}

void readfile_student()  //加载学生信息
{
    int i=0;
    FILE * fp;
    char filepath[20];
    struct student *p1,*p2;
    N2=0;
    fp=fopen("info-student.txt","r");
    if((fp=fopen("info-student.txt","r"))==NULL)
    {
        printf("+---------------------------------------------------------+\n");
        printf("|找不到info-student.txt文件!                               |\n");
        exit(0);
    }
    p1=p2=(struct student*)malloc(sizeof(struct student));
    fread(p1,sizeof(struct student),1,fp);
    head2=NULL;
    while(!feof(fp))
    {
        i=0;
        N2=N2+1;
        if(N2==1)head2=p1;
        else p2->next=p1;
        p2=p1;
        p1=(struct student * )malloc(sizeof(struct student));
        fread(p1,sizeof(struct student),1,fp);
    }
    p2->next=NULL;
}

/* 课程管理模块----------------------------------------------------------------------------------------*/

void insert_course(struct couse *incouse) //课程管理子函数(增加课程)
{
    struct couse *p0,*p1,*p2;
    p1=head1;
    p0=incouse;
    if(head1==NULL)
    {
        head1=p0;
        p0->next=NULL;
    }
    else
    {
        while((p0->num1 > p1->num1) && (p1->next!=NULL))
        {
            p2=p1;
            p1=p1->next;
        }
        if(p0->num1 <= p1->num1)
        {
            if(head1==p1) head1=p0;
            else p2->next=p0;
            p0->next=p1;
        }
        else
        {
            p1->next=p0;
            p0->next=NULL;
        }
    }
    N1=N1+1;
}
void delete_course(int num1)  //课程管理子函数(删除课程)
{
    struct couse *p1,*p2;
    if(head1==NULL)
    {
        printf("+---------------------------------------------------------+\n");
        printf("| 没有课程,无法删除!                                       |\n");
        printf("+---------------------------------------------------------+\n");
        printf("\n");
        printf("\n");
        goto end;
    }
    p1=head1;
    while(num1!=p1->num1 && p1->next!=NULL)
    {
        p2=p1;
        p1=p1->next;
    }
    if(num1==p1->num1)
    {
        if(p1==head1) head1=p1->next;
        else p2->next=p1->next;
        printf("+---------------------------------------------------------+\n");
        printf("|已删除该编号课程!                                        |\n");
        printf("+---------------------------------------------------------+\n");
        printf("\n");
        printf("\n");
        N1=N1-1;
    }
    else
    {
        printf("+---------------------------------------------------------+\n");
        printf("| 无该编号的课程!                                         |\n");
        printf("+---------------------------------------------------------+\n");
        printf("\n");
        printf("\n");
    }
    end:;
}
void management_course()  //课程管理主函数
{
    struct couse * incouse;
    int i,num1;
    printf("+---------------------------------------------------------+\n");
    printf("|                        课程管理                         |\n");
    printf("+--+------------------------------------------------------+\n");
    printf("|1 | 新增课程                                             |\n");
    printf("+--+------------------------------------------------------+\n");
    printf("|2 | 删除课程                                             |\n");
    printf("+--+------------------------------------------------------+\n");
    printf("|3 | 返回主菜单                                           |\n");
    printf("+--+------------------------------------------------------+\n");
    printf("| 请选择(1~3):                                            |\n");
    scanf("%d",&i);
    switch(i)
    {
    case(1):
        {
            system("cls");
            incouse=(struct couse *)malloc(sizeof(struct couse));
            printf("+--------+------------------------------+----+------------+\n");
            printf("|课程编号|课程名称                      |学分|课程人数上限|\n");
            printf("+--------+------------------------------+----+------------+\n");
            scanf("%d%s%d%d",&incouse->num1,incouse->name1,&incouse->score,&incouse->Melepeo);
            incouse->nelepeo=0;
            insert_course(incouse);
            system("cls");
            printf("+---------------------------------------------------------+\n");
            printf("| 添加成功!                                               |\n" );
            break;
        }
    case(2):
        {
            system("cls");
            printf("+---------------------------------------------------------+\n");
            printf("|请输入要删除课程的编号:                                  |\n");
            scanf("%d",&num1);
            delete_course(num1);
            system("cls");
            printf("+---------------------------------------------------------+\n");
            printf("| 删除成功!                                               |\n");
            break;
        }
    case(3):system("cls");break;
    }
}



/* 学生信息管理模块--------------------------------------------------------------------------- */

void insert_student(struct student * incouse)  //学生信息管理子函数(填加学生信息)
{
    struct student *p0,*p1,*p2;
    p1=head2;
    p0=incouse;
    if(head2==NULL)
    {
        head2=p0;
        p0->next=NULL;
    }
    else
    {
        while((p0->num2 > p1->num2) && (p1->next!=NULL))
        {
            p2=p1;
            p1=p1->next;
        }
        if(p0->num2 <= p1->num2)
        {
            if(head2==p1) head2=p0;
            else p2->next=p0;
            p0->next=p1;
        }
        else
        {
            p1->next=p0;
            p0->next=NULL;
        }
    }
    N2=N2+1;
}
void delete_student(int num2)  //学生信息管理子函数（删除学生信息)
{
    struct student *p1,*p2;
    if(head2==NULL)
    {
        printf("+---------------------------------------------------------+\n");
        printf("| 没有该学生信息,无法删除!                                   |\n");
        printf("+---------------------------------------------------------+\n");
        printf("\n");
        printf("\n");
        goto end;
    }
    p1=head2;
    while(num2!=p1->num2 && p1->next!=NULL)
    {
        p2=p1;
        p1=p1->next;
    }
    if(num2==p1->num2)
    {
        if(p1==head2) head2=p1->next;
        else p2->next=p1->next;
        printf("+---------------------------------------------------------+\n");
        printf("|已删除该学生信息!                                        |\n");
        N2=N2-1;
    }
    else
    {
      printf("+---------------------------------------------------------+\n");
      printf("|无该学号的学生!                                          |\n");
    }
    end:;
}
void management_student()  //学生信息管理主函数
{
    struct student * incouse;
    int i,num2;
    printf("+---------------------------------------------------------+\n");
    printf("|                      学生信息管理                       |\n");
    printf("+--+------------------------------------------------------+\n");
    printf("|1 | 新增学生信息                                         |\n");
    printf("+--+------------------------------------------------------+\n");
    printf("|2 | 删除学生信息                                         |\n");
    printf("+--+------------------------------------------------------+\n");
    printf("|3 | 返回主菜单                                           |\n");
    printf("+--+------------------------------------------------------+\n");
    printf("|请选择(1~3):                                             |\n");
    scanf("%d",&i);
    switch(i)
    {
    case(1):
        {
            system("cls");
            incouse=(struct student *)malloc(sizeof(struct student));
            incouse->nelen=0;
            incouse->nelenum[0]=0;
            printf("+--------+--------+---------------------------------------+\n");
            printf("|学生学号|学生姓名|                                       |\n");
            printf("+--------+--------+---------------------------------------+\n");
            scanf("%d %s",&incouse->num2,incouse->name2);
            insert_student(incouse);
            system("cls");
            printf("+---------------------------------------------------------+\n");
            printf("| 新增成功!                                               |\n" );
            break;
        }
    case(2):
        {
            system("cls");
            printf("+---------------------------------------------------------+\n");
            printf("|请输入要删除学生的学号:                                  |\n");
            scanf("%d",&num2);
            system("cls");
            delete_student(num2);
            break;
        }
    case(3):system("cls");break;
    }
}
void elect(struct student * s)//选课
{
    struct couse * p;
    int num1,i;
    system("cls");
    printf("+---------------------------------------------------------+\n");
    printf("|请输入要选课的编号:                                       |\n");
    scanf("%d",&num1);
    for(i=0;s->nelenum[i]!=0;i++);
    s->nelenum[i]=num1;
    (s->nelen)++;
    p=head1;
    while(p->num1!=num1) p=p->next;
    (p->nelepeo)++;
    system("cls");
    printf("+---------------------------------------------------------+\n");
    printf("| 选课成功!                                               |\n");
    printf("+---------------------------------------------------------+\n");
}

/* 选课系统部分-------------------------------------------------------------------------- */

void cheak() //学生选课子函数(查询可选课程)
{
    char e;
    struct couse * c;
    struct student * s;
    int num2,i,j=0,t=0;
    printf("+---------------------------------------------------------+\n");
    printf("|请输入你的学号:                                          |\n");
    scanf("%d",&num2);
    s=head2;
    while(s->num2!=num2 && s->next!=NULL) s=s->next;
    if(s->num2!=num2)
    {
        printf("+---------------------------------------------------------+\n");
        printf("|不存在你的信息,请让教师录入你的信息!                     |\n");
        printf("+---------------------------------------------------------+\n");
        goto end;
    }
    c=head1;
    system("cls");
    printf("+---------------------------------------------------------+\n");
    printf("|你的可选课程编号:                                        |\n");
    printf("+---------------------------------------------------------+\n");
    while(c!=NULL)
    {
        for(t=0,i=0;s->nelenum[i]!=0;i++)
        {
            if(c->num1==s->nelenum[i]) t=1;
        }
        if(t==0 && (c->nelepeo!=c->Melepeo))
        {
            printf("|%-4d|                                                    |\n",c->num1);
            printf("+---------------------------------------------------------+\n");
            j++;
        }
        c=c->next;
    }
    if(j==0)
    {
        printf("| 你已选完所有课程，无法再多选!                              |\n");
        printf("+---------------------------------------------------------+\n");
        goto end;
    }
    printf("|选课(y/n)?:                                              |\n");
    getchar();
    e=getchar();
    i=0;
    while(e=='y')
    {
        elect(s);

        printf("|继续选课(y/n)?:                                          |\n");
        getchar();
        e=getchar();
    }
    system("cls");
    end:;
}
void back(struct student * p)  //退课
{
    struct couse * p1;
    int num1,i,j;
    system("cls");
    printf("+---------------------------------------------------------+\n");
    printf("|请输入你要退掉的课程编号:                                |\n");
    scanf("%d",&num1);
    p1=head1;
    while(p1->num1!=num1) p1=p1->next;
    for(i=0;p->nelenum[i]!=num1;i++);
    for(j=i;p->nelenum[j]!=0;j++) p->nelenum[j]=p->nelenum[j+1];
    p->nelenum[--j]=0;
    (p1->nelepeo)--;
    printf("+---------------------------------------------------------+\n");
    printf("| 退课成功!                                               |\n");
    printf("+---------------------------------------------------------+\n");
}
void hcheak()  //学生选课子函数（查询已选课程)
{
    char c;
    struct couse * p0;
    struct student * p;
    int num2,i,f=0;
    system("cls");
    printf("+---------------------------------------------------------+\n");
    printf("| 请输入学号:                                             |\n");
    scanf("%d",&num2);
    p=head2;
    system("cls");
    while(p->num2!=num2 && p!=NULL) p=p->next;
    if(p==NULL)
    {
        printf("+---------------------------------------------------------+\n");
        printf("|不存在你的信息,请回主菜单录入信息:                          |\n");
        printf("+---------------------------------------------------------+\n");
        printf("\n");
        printf("\n");
        goto end;
    }
    printf("+--------------+------------------------------------------+\n");
    printf("| 已选课程编号 |                                          |\n");
    printf("+---------------------------------------------------------+\n");
    if(p->nelenum[0]==0)
    {
        printf("+---------------------------------------------------------+\n");
        printf("| 你还没选课!                                              |\n");
        printf("+---------------------------------------------------------+\n");
        printf("\n");
        printf("\n");
        goto end;
    }
    for(i=0;p->nelenum[i]!=0;i++)
    {
        printf("|%14d|                                          |\n",p->nelenum[i]);
        p0=head1;
        while(p0->num1!=p->nelenum[i]) p0=p0->next;
        f=f+p0->score;
    }
    printf("+---------------------------------------------------------+\n");
    printf("|总学分: %d                                               |\n",f);
    printf("+---------------------------------------------------------+\n");
    printf("| 是否进行退课(y/n)?                                      |\n");
    getchar();
    c=getchar();
    while(c=='y')
    {
        system("cls");
        back(p);
        printf("| 继续退课(y/n)?                                          |\n");
        getchar();
        c=getchar();
        (p->nelen)--;
    }
    system("cls");
    end:;
}
void elective()//学生选课主函数
{
    int i;
    printf("+---------------------------------------------------------+\n");
    printf("|                         学生选课                        |\n");
    printf("+--+------------------------------------------------------+\n");
    printf("|1 | 查询可选课程                                         |\n");
    printf("+--+------------------------------------------------------+\n");
    printf("|2 | 查询已选课程                                         |\n");
    printf("+--+------------------------------------------------------+\n");
    printf("|3 | 返回主菜单                                           |\n");
    printf("+--+------------------------------------------------------+\n");
    printf("请输入(1~3):                                              |\n");
    scanf("%d",&i);
    switch(i)
    {
    case(1):system("cls");cheak();break;
    case(2):system("cls");hcheak();break;
    case(3):system("cls");break;
    }
}
void list_course()//输出课程信息
{
    struct couse * p;
    p=head1;
    printf("+--------+----------------+----+------------+-------------+\n");
    printf("|课程编号|        课程名称|学分|课程已选人数| 课程人数上限|\n");
    printf("+--------+----------------+----+------------+-------------+\n");
    while(p!=NULL)
    {
        printf("|%8d|%16s|%4d|%12d|%13d|\n",p->num1,p->name1,p->score,p->nelepeo,p->Melepeo);
        p=p->next;
    }
    printf("+--------+----------------+----+------------+-------------+\n");
    printf("\n");
    printf("\n");
}

void list_student()//输出学生信息
{
    struct student * p;
    p=head2;
    printf("+--------+-----------------------------------+------------+\n");
    printf("|学生学号|                           学生姓名|已选课程数量|\n");
    printf("+--------+-----------------------------------+------------+\n");
    while(p!=NULL)
    {
        printf("|%8d|%35s|%12d|\n",p->num2,p->name2,p->nelen);
        p=p->next;
    }
    printf("+--------+-----------------------------------+------------+\n");
    printf("\n");
    printf("\n");
}

/* 储存模块函数----------------------------------------------------------------------- */

void savefile_course()//存储课程信息
{
    FILE * fp;
    struct couse * p;
    char filepath[30];
    fp=fopen("info-course.txt","w");
    if((fp=fopen("info-course.txt","w"))==NULL)
    {
        printf("\n+---------------------------------------------------------+\n");
        printf("| 保存失败!                                               |\n");
        exit(0);
    }
    p=head1;
    while(p!=NULL)
    {
        fprintf(fp,"%d %s %d %d %d\n",p->num1,p->name1,p->score,p->nelepeo,p->Melepeo);
        p=p->next;
    }
    fclose(fp);
    printf("\n+---------------------------------------------------------+\n");
    printf("| 课程信息已保存在info-course.txt中!                      |\n");
}
void savefile_student() //存储学生信息
{
    FILE * fp;
    struct student * p;
    char filepath[30];
    fp=fopen("info-student.txt","w");
    if((fp=fopen("info-student.txt","w"))==NULL)
    {
        printf("+---------------------------------------------------------+\n");
        printf("| 保存失败!                                               |\n");
        exit(0);
    }
    p=head2;
    while(p!=NULL)
    {
        fwrite(p,sizeof(struct student),1,fp);
        p=p->next;
    }
    fclose(fp);
    printf("+---------------------------------------------------------+\n");
    printf("| 学生信息已保存在info-student.txt中!                     |\n");
}
void save_all() //存储信息
{
    savefile_course();
    savefile_student();
}


/* 主函数&&菜单函数 ------------------------------------------------------------------------------ */

void index_info()//信息主函数
{
    int i;
    printf("+---------------------------------------------------------+\n");
    printf("| 选课信息及存储                                          |\n");
    printf("|---------------------------------------------------------|\n");
    printf("|1 | 查看课程信息                                         |\n");
    printf("|--+------------------------------------------------------|\n");
    printf("|2 | 存储信息                                             |\n");
    printf("|--+------------------------------------------------------|\n");
    printf("|3 | 返回主菜单                                           |\n");
    printf("|---------------------------------------------------------|\n");
    printf("|请输入(1~3):                                             |\n");
    scanf("%d",&i);
    switch(i)
    {
    case(1):system("cls");list_course();break;
    case(2):system("cls");save_all();break;
    case(3):system("cls");break;
    }
}
void teacher_manage()
{
    int p,i;
    printf("+---------------------------------------------------------+\n");
    printf("| 教师管理系统                                            |\n" );
    printf("+---------------------------------------------------------|\n");
    printf("请输入密码                                                |\n");
    scanf("%d",&p);
    if(p==12345678)
    {
        system("cls");
        printf("+---------------------------------------------------------+\n");
        printf("|                           菜单                          |\n");
        printf("|---------------------------------------------------------|\n");
        printf("|1 | 增加/删除课程                                        |\n");
        printf("|--+------------------------------------------------------|\n");
        printf("|2 | 查看课程信息                                         |\n");
        printf("|--+------------------------------------------------------|\n");
        printf("|3 | 增加/删除学生                                        |\n");
        printf("|--+------------------------------------------------------|\n");
        printf("|4 | 查看学生信息                                         |\n");
        printf("|--+------------------------------------------------------|\n");
        printf("|5 | 返回主菜单                                           |\n");
        printf("|---------------------------------------------------------|\n");
        printf("|请输入(1~5):                                             |\n");
        scanf("%d",&i);
        switch (i) {
            case (1):system("cls");management_course();break;
            case (2):system("cls");list_course();break;
            case (3):system("cls");management_student();break;
            case (4):system("cls");list_student();break;
            case(5):system("cls");break;
        }
    }
    else
    {
        printf("+---------------------------------------------------------+\n");
        printf("| 密码错误                                                |\n");
    }
}

int main()  //主函数
{
    int i;
    system("cls");
    readfile_course();
    readfile_student();

    printf("+---------------------------------------------------------+\n");
    printf("|                   欢迎使用学生选课系统!                 |\n");
    start:
    printf("+---------------------------------------------------------+\n");
    printf("|                           主菜单                        |\n");
    printf("|---------------------------------------------------------|\n");
    printf("|1 | 学生选课                                             |\n");
    printf("|--+------------------------------------------------------|\n");
    printf("|2 | 教师管理                                             |\n");
    printf("|--+------------------------------------------------------|\n");
    printf("|3 | 选课信息及存储                                       |\n");
    printf("|--+------------------------------------------------------|\n");
    printf("|4 | 保存并退出系统                                       |\n");
    printf("|--+------------------------------------------------------|\n");
    printf("|5 | 退出系统                                             |\n");
    printf("|---------------------------------------------------------|\n");
    printf("|请输入菜单选项(1~5):                                     |\n");
    scanf("%d",&i);
    if(i<1 || i>5)
    {
        printf("\n");
        printf("+---------------------------------------------------------+\n");
        printf("| 输入错误,请重输:                                        |\n");
        goto start;
    }
    switch(i)
    {
    case(1):
        {
            system("cls"); // windows cls
            elective();
            goto start;
            break;
        }
    case(2):
        {
            system("cls");
            teacher_manage();
            goto start;
            break;
        }
    case(3):
        {
            system("cls");
            index_info();
            goto start;
            break;
        }
    case(4):
        {
            system("cls");
            savefile_course();
            savefile_student();
            printf("+---------------------------------------------------------+\n");
            printf("|  感谢使用本系统!再见!                                   |\n");
            printf("+---------------------------------------------------------+\n");
        }
    case(5):
        {
            system("cls");
            printf("+---------------------------------------------------------+\n");
            printf("|  感谢使用本系统!再见!                                   |\n");
            printf("+---------------------------------------------------------+\n");
        }
    }
    return(0);
}