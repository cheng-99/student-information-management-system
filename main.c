#include<stdio.h>
#include"stu_info_m_sys.h"


int main()
{
	user_linkedlist* userlist = create_ul();
	student_linkedlist* studentlist = create_sl();
	sysytem_init(userlist, studentlist);
	login(userlist, studentlist);
	save_file(userlist, studentlist);
}