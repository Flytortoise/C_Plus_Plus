#include "Data.h"
#include <stdio.h>
#include <string.h>
using namespace std;

Online_data* Online_data::data = NULL;

Online_data::Online_data()
{

}

Online_data::~Online_data()
{
	
}

Online_data* Online_data::GetData()
{
	if(data == NULL)
	{
		data = new Online_data();		
	}

	return data;
}

void Online_data::FreeData()
{
	if(data != NULL)
	{
		delete data;
		data = NULL;
	}
}
/*
Online_data::Online_data(const Online_data &t)
{
	action = t.action;
    sock = t.sock;
	flag = t.flag;
	chat_flag = t.chat_flag;
	send_flag = t.send_flag;
	off_line = t.off_line;
	printf("%s\n",t.id);
	strcpy(id,t.id);
	strcpy(name,t.name);
	strcpy(password,t.password);
	strcpy(buffer,t.buffer);
	strcpy(send,t.send);
	strcpy(Sel,t.Sel);

}*/

