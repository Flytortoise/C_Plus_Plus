#include <stdio.h>
#include "interface.h"

int AB_Interface::Action(){}
int AB_Interface::Action(int t){}
void AB_Interface::Action_pass(){}
void AB_Interface::Action(char *){}
void AB_Interface::Action2(char *){}


Interface::Interface(){}

Interface * Interface::GetInterface()
{
	if(interface_ == NULL)
	{
		interface_ = new Interface();
	}	
	return interface_;
}

void Interface::FreeInterface()
{
	if(interface_ != NULL)
	{
		delete interface_;
		interface_ = NULL;
	}
}

void Interface::Action_pass()
{
    printf("+--------------------------+\n");
	printf("|                          |\n");
	printf("|        用户登录界面      |\n");
	printf("|                          |\n");
    printf("+--------------------------+\n");
	printf("|                          |\n");
	printf("|        1. 登录           |\n");
	printf("|        2. 注册           |\n");
	printf("|        3. 退出           |\n");
	printf("|                          |\n");
    printf("+--------------------------+\n");
}

void Interface::Action(char * name)
{
    printf("**************************************\n");
	printf("*                                    *\n");
	printf("*             多功能聊天室           *\n");
	printf("*                                    *\n");
    printf("**************************************\n");
	printf("*  1.在线用户      ｜   2.私聊       *\n");
	printf("*------------------------------------*\n");
	printf("*  3.群发消息      ｜   4.快捷消息   *\n");
	printf("*------------------------------------*\n");
	printf("*  5.发送表情      ｜   6.修改昵称   *\n");
	printf("*------------------------------------*\n");
	printf("*  7.修改密码      ｜   8.查看帮助   *\n");
	printf("*------------------------------------*\n");
	printf("*  9.发送文件      ｜  10.退出登录   *\n");
	printf("*------------------------------------*\n");
	printf("*  11.退出聊天室   ｜ 12.查看聊天记录*\n");
    printf("**************************************\n");
	printf("＊  当前用户:%s\n",name);
	printf("＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊\n");
}

void Interface::Action2(char * name)
{
    printf("**************************************\n");
	printf("*                                    *\n");
	printf("*             多功能聊天室           *\n");
	printf("*                                    *\n");
    printf("**************************************\n");
	printf("*  1.在线用户      ｜   2.私聊       *\n");
	printf("*------------------------------------*\n");
	printf("*  3.群发消息      ｜   4.快捷消息   *\n");
	printf("*------------------------------------*\n");
	printf("*  5.发送表情      ｜   6.修改昵称   *\n");
	printf("*------------------------------------*\n");
	printf("*  7.修改密码      ｜   8.查看帮助   *\n");
	printf("*------------------------------------*\n");
	printf("*  9.发送文件      ｜  10.退出登录   *\n");
	printf("*------------------------------------*\n");
	printf("*  11.退出聊天室   ｜ 12.查看聊天记录*\n");
    printf("**************************************\n");
	printf("*  13.踢出用户     ｜  14.禁言       *\n");
	printf("*------------------------------------*\n");
	printf("*  15.解除禁言                       *\n");
    printf("**************************************\n");
	printf("＊  当前用户:%s\n",name);
	printf("＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊\n");
}
