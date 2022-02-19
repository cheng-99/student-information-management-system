#include<stdbool.h>

typedef struct student student;
typedef struct user user;
typedef struct student_linkedlist student_linkedlist;
typedef struct user_linkedlist user_linkedlist;


struct student
{
	char id[20];
	char name[26];
	int grades;
	student* next;
};

struct user
{
	int limit;//0-->admin 1-->normal
	char name[26];
	char password[20];
	user* next;
};

struct student_linkedlist
{
	student* head;
};

struct user_linkedlist
{
	user* head;
};

student_linkedlist* create_sl();// ����ѧ���������л�ѧ���ļ��е���Ϣ
user_linkedlist* create_ul();//�����û��������л��û��ļ��е���Ϣ
void save_file(user_linkedlist* userlist, student_linkedlist* studentlist);//���л�
void sysytem_init(user_linkedlist* userlist, student_linkedlist* studentlist);//�����л�
void login(user_linkedlist* userlist, student_linkedlist* studentlist);//��¼
void show_admin_menu(user_linkedlist* userlist, student_linkedlist* studentlist);//��ʾ����Ա�˵� search allʱ����
void show_normal_user_menu(user_linkedlist* userlist, student_linkedlist* studentlist);//��ʾ��ͨ�û��˵�
void user_menu(user_linkedlist* userlist, student_linkedlist* studentlist);// ����Ա�˵�
void search_student_information(student_linkedlist* studentlist);//����ѧ����Ϣ
void search_student_by_id(student_linkedlist* studentlist);//ͨ��ѧ��id����ѧ����Ϣ
void search_student_by_name(student_linkedlist* studentlist);//ͨ��ѧ����������ѧ����Ϣ
void add_student(student_linkedlist* studentlist, int n);//���ѧ�� nΪҪ��ӵ�ѧ������
void update_student(student_linkedlist* studentlist);//����ѧ����Ϣ 
void delete_student(student_linkedlist* studentlist);//ɾ��ѧ����Ϣ
void add_user(user_linkedlist* userlist, int m);//����˺�
void update_user(user_linkedlist* userlist);//�޸��˻�
int get_userlist_length(user_linkedlist* userlist);//��ȡuerlist���ȣ�����ɾ�����һλ����Ա
void delete_user(user_linkedlist* userlist);//ɾ���˺�
void search_user_account(user_linkedlist* userlist);//��ѯ�û��˺���Ϣ
void exit_system();//�˳�

