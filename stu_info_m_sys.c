#define _CRT_SECURE_NO_WARNINGS
#include"stu_info_m_sys.h"
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

student_linkedlist* create_sl()
{
	return calloc(1, sizeof(student));
}

user_linkedlist* create_ul()
{
	return calloc(1, sizeof(user));
}

void sysytem_init(user_linkedlist* userlist, student_linkedlist* studentlist)
{
	int counts = 0;//用于标记是否是学生链表第一次插入
	int countu = 0;//用于标记是否是使用者链表第一次插入
	FILE* fp1 = fopen("student.txt", "r");
	if (fp1 == NULL)
	{
		ferror("fopen");
	}
	while (!feof(fp1))
	{
		student* st = (student*)calloc(1, sizeof(student));
		fscanf(fp1, "%s %s %d\n", st->id, st->name, &st->grades);
		if (counts == 0)
		{
			studentlist->head = st;
			counts++;
		}
		else
		{
			st->next = studentlist->head;
			studentlist->head = st;
			counts++;
		}
	}

	FILE* fp2 = fopen("user.txt", "r");
	if (fp2 == NULL)
	{
		ferror("fopen");
	}
	while (!feof(fp2))
	{
		user* us = (user*)calloc(1, sizeof(user));
		fscanf(fp2, "%d %s %s\n", &us->limit, us->name, us->password);
		if (countu == 0)
		{
			userlist->head = us;
			countu++;
		}
		else
		{
			us->next = userlist->head;
			userlist->head = us;
			countu++;
		}
	}
	fclose(fp1);
	fclose(fp2);
}

void login(user_linkedlist* userlist, student_linkedlist* studentlist)
{
	char name[26];
	char password[20];
	printf("Hello, welcome to use the student information management system!\n");
	printf("Please enter user name:\n");
	scanf("%s", name);
	printf("\nHello %s,please enter your password!\n", name);
	char ch;
	int index = 0;
	while ((ch = _getch()) != '\r')
	{
		if (ch != '\b')
		{
			printf("*");
			password[index++] = ch;
		}
		else
		{
			printf("\b \b");
			index--;
		}
	}
	password[index] = '\0';
	int limit;//权限

	user* temp = userlist->head;
	while (temp)
	{
		if (strcmp(name, temp->name) == 0 && strcmp(password, temp->password) == 0)
		{
			limit = temp->limit;
			break;
		}
		temp = temp->next;
	}
	if (temp == NULL)//说明未匹配到此使用者
	{
		printf("Sorry, the information you entered is wrong, please log out and log in again!\n");
		system("pause");
		exit(0);
	}
	else
	{
		if (limit == 0)
		{
			show_admin_menu(userlist, studentlist);
		}
		else if (limit == 1)
		{
			show_normal_user_menu(userlist, studentlist);
		}
	}
}

void show_admin_menu(user_linkedlist* userlist, student_linkedlist* studentlist)
{
	printf("\n0:search all\n");
	printf("1:search by name\n");
	printf("2:search by id\n");
	printf("3:exit\n");
	int flag;
	scanf("%d", &flag);
	switch (flag)
	{
	case 0:
		user_menu(userlist, studentlist);
		break;
	case 1:
		search_student_by_name(studentlist);
		break;
	case 2:
		search_student_by_id(studentlist);
		break;
	case 3:
		exit(0);
		break;
	}
}


void show_normal_user_menu(user_linkedlist* userlist, student_linkedlist* studentlist)
{
	printf("\n0:search by name\n");
	printf("1:search by id\n");
	printf("2:exit\n");
	int flag;
	scanf("%d", &flag);
	switch (flag)
	{
	case 0:
		search_student_by_name(studentlist);
		break;
	case 1:
		search_student_by_id(studentlist);
		break;
	case 2:
		exit(0);
		break;	
	}
}

void user_menu(user_linkedlist* userlist, student_linkedlist* studentlist)
{
	int choice;
	int n;//要添加的学生数量，如有需要
	int m;//要添加的账号数量,如有需要
	printf("***           1.search student information            ***\n");
	printf("***           2.add student information               ***\n");
	printf("***           3.update student information            ***\n");
	printf("***           4.delete student information            ***\n");
	printf("***           5.add user account                      ***\n");
	printf("***           6.update user account                   ***\n");
	printf("***           7.delete user account                   ***\n");
	printf("***           8.search user account                   ***\n");
	printf("***           9.exit                                  ***\n");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		search_student_information(studentlist);
		break;
	case 2:
		printf("Please enter the number of students to be inserted:\n");
		scanf("%d", &n);
		add_student(studentlist, n);
		break;
	case 3:
		update_student(studentlist);
		break;
	case 4:
		delete_student(studentlist);
		break;
	case 5:
		printf("Please enter the number of user account to be inserted:\n");
		scanf("%d", &m);
		add_user(userlist, m);
		break;
	case 6:
		update_user(userlist);
		break;
	case 7:
		delete_user(userlist);
		break;
	case 8:
		search_user_account(userlist);
		break;
	case 9:
		exit_system();
		break;
	}
}


void search_student_information(student_linkedlist* studentlist)
{
	int choice;
	printf("Do you want to look it up by name or by student number?\n");
	printf("Enter 1 to search by name\nEnter 2 to search by id\n");
	scanf("%d", &choice);
	if (choice == 1)
	{
		search_student_by_name(studentlist);
	}
	else if(choice==2)
	{
		search_student_by_id(studentlist);
	}
	else//输入有错误
	{
		while (choice != 1 && choice != 2)
		{
			printf("Input error, please enter again:\n");
			scanf("%d", &choice);
			if (choice == 1)
			{
				search_student_by_name(studentlist);
				break;
			}
			else if (choice == 2)
			{
				search_student_by_id(studentlist);
				break;
			}
		}
	}
}


void search_student_by_id(student_linkedlist* studentlist)
{
	char id[20];
	scanf("%s", id);
	student* t = studentlist->head;
	while (t)
	{
		if (strcmp(id, t->id) == 0)
		{
			printf("%s %s %d\n", t->id, t->name, t->grades);
			return;
		}
		t = t->next;
	}
	if (t == NULL)//说明没有找到
	{
		printf("Sorry , the student you are looking for has not been recorded in the system!\n");
	}
}


void search_student_by_name(student_linkedlist* studentlist)
{
	char name[26];
	scanf("%s", name);
	student* t = studentlist->head;
	while (t)
	{
		if (strcmp(name, t->name) == 0)
		{
			printf("%s %s %d\n", t->id, t->name, t->grades);
			return;
		}
		t = t->next;
	}
	if (t == NULL)//说明没有找到
	{
		printf("Sorry , the student you are looking for has not been recorded in the system!\n");
	}
}


void add_student(student_linkedlist* studentlist, int n)
{
	while (n--)
	{
		if (studentlist->head == NULL)
		{
			student* newstudent =(student*) calloc(1, sizeof(student));
			scanf("%s%s%d", newstudent->id, newstudent->name, &newstudent->grades);
			studentlist->head = newstudent;
		}
		else
		{
			student* newstudent = calloc(1, sizeof(student));
			scanf("%s%s%d", newstudent->id, newstudent->name, &newstudent->grades);
			newstudent->next = studentlist->head;
			studentlist->head = newstudent;
		}
	}
}


//更新学生信息首先要找到该学生，因为学号不能更改，所以通过学号查找
void update_student(student_linkedlist* studentlist)
{
	char id[20];
	scanf("%s",id);
	student* t = studentlist->head;
	while (t)
	{
		if (strcmp(id, t->id) == 0)
		{
			scanf("%s%s%d", t->id, t->name, &t->grades);
			break;
		}
		t = t->next;
	}
	if(t==NULL)
	{
		printf("The student you want to modify has not been entered into the system!\n");
		exit(0);
	}
}

//删除学生信息，通过学号查找删除
void delete_student(student_linkedlist* studentlist)
{
	char id[20];
	scanf("%s", id);
	student* t = studentlist->head;
	student* pre = NULL;
	int count = 0;//作为是不是待删除的第一个结点的标识
	while (t)
	{
		if (strcmp(id, t->id) == 0 && count == 0)
		{
			studentlist->head = studentlist->head->next;
			free(t);
			return;
		}
		else if (strcmp(id, t->id) == 0 && count > 0)
		{
			pre->next = t->next;
			free(t);
			return;
		}
		pre = t;
		t = t->next;
		count++;
	}
	if (t == NULL)
	{
		printf("The student you want to delete has not been entered into the system!\n");
		exit(0);
	}
}


void add_user(user_linkedlist* userlist,int m)
{
	while (m--)
	{
		if (userlist->head == NULL)
		{
			user* newuser = calloc(1, sizeof(user));
			scanf("%d%s%s", &newuser->limit, newuser->name, newuser->password);
			userlist->head = newuser;
		}
		else
		{
			user* newuser = calloc(1, sizeof(user));
			scanf("%d%s%s", &newuser->limit, newuser->name, newuser->password);
			newuser->next = userlist->head;
			userlist->head = newuser;
		}
	}
}


void update_user(user_linkedlist* userlist)
{
	char name[26];
	scanf("%s", name);
	user* u = userlist->head;
	while (u)
	{
		if (strcmp(name, u->name) == 0)
		{
			scanf("%d%s%s", &u->limit, u->name, u->password);
			break;
		}
		u = u->next;
	}
	if (u == NULL)
	{
		printf("The user you want to modify has not been entered into the system!\n");
		exit(0);
	}
}

int get_userlist_length(user_linkedlist* userlist)
{
	int count = 0;
	user* t = userlist->head;
	while (t)
	{
		count++;
		t = t->next;
	}
	return count;
}

void delete_user(user_linkedlist* userlist)
{
	char name[26];
	scanf("%s", name);
	user* u = userlist->head;
	user* pre = NULL;
	int count = 0;//作为是否是删除头结点的标记与是否是最后一个管理员账户的标识
	while (u)
	{
		if (get_userlist_length(userlist) == 1)//此时只剩最后一位管理员，不执行删除操作，退出
		{
			printf("Sorry, you have been the last administrator, the deletion operation has been terminated!\n");
			exit(0);
		}
		if (strcmp(u->name, name) == 0 && count == 0)//u是第一个结点
		{
			userlist->head = userlist->head->next;
			free(u);
			return;
		}
		else if (strcmp(u->name, name) == 0 && count != 0)
		{
			pre->next = u->next;
			free(u);
			return;
		}
		pre = u;
		u = u->next;
		count++;
	}
	if (u == NULL)
	{
		printf("The user account you want to delete has not been entered into the system!\n");
		exit(0);
	}
}


void search_user_account(user_linkedlist* userlist)
{
	char name[26];
	scanf("%s", name);
	user* u = userlist->head;
	while (u)
	{
		if (strcmp(name, u->name) == 0)
		{
			printf("%d %s %s\n", u->limit, u->name, u->password);
			return;
		}
		u = u->next;
	}
	if (u == NULL)//说明没有找到
	{
		printf("Sorry , the user account you are looking for has not been recorded in the system!\n");
	}
}


void exit_system()
{
	printf("Thanks for using the Student Administration system!\n");
	exit(0);
}

void save_file(user_linkedlist* userlist, student_linkedlist* studentlist)
{
	FILE* fp1 = fopen("student.txt", "w");
	if (fp1 == NULL)
	{
		ferror("fopen");
	}
	student* t = studentlist->head;
	while (t)
	{
		fprintf(fp1, "%s %s %d\n", t->id, t->name, t->grades);
		t = t->next;
	}

	FILE* fp2 = fopen("user.txt", "w");
	if (fp2 == NULL)
	{
		ferror("fopen");
	}
	user* u = userlist->head;
	while (u)
	{
		fprintf(fp2, "%d %s %s\n", u->limit, u->name, u->password);
		u = u->next;
	}
	
	fclose(fp1);
	fclose(fp2);
}