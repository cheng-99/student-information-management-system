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

student_linkedlist* create_sl();// 创建学生链表反序列化学生文件中的信息
user_linkedlist* create_ul();//创建用户链表反序列化用户文件中的信息
void save_file(user_linkedlist* userlist, student_linkedlist* studentlist);//序列化
void sysytem_init(user_linkedlist* userlist, student_linkedlist* studentlist);//反序列化
void login(user_linkedlist* userlist, student_linkedlist* studentlist);//登录
void show_admin_menu(user_linkedlist* userlist, student_linkedlist* studentlist);//显示管理员菜单 search all时调出
void show_normal_user_menu(user_linkedlist* userlist, student_linkedlist* studentlist);//显示普通用户菜单
void user_menu(user_linkedlist* userlist, student_linkedlist* studentlist);// 管理员菜单
void search_student_information(student_linkedlist* studentlist);//查找学生信息
void search_student_by_id(student_linkedlist* studentlist);//通过学生id查找学生信息
void search_student_by_name(student_linkedlist* studentlist);//通过学生姓名查找学生信息
void add_student(student_linkedlist* studentlist, int n);//添加学生 n为要添加的学生数量
void update_student(student_linkedlist* studentlist);//更新学生信息 
void delete_student(student_linkedlist* studentlist);//删除学生信息
void add_user(user_linkedlist* userlist, int m);//添加账号
void update_user(user_linkedlist* userlist);//修改账户
int get_userlist_length(user_linkedlist* userlist);//获取uerlist长度，避免删除最后一位管理员
void delete_user(user_linkedlist* userlist);//删除账号
void search_user_account(user_linkedlist* userlist);//查询用户账号信息
void exit_system();//退出

