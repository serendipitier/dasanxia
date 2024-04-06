#include <stdio.h>
int main(){
	int i=12345678;
	int *p =&i;
	char *p1;
	p1 = (char*)p;
	
	if (p1 == "1") printf("学号20181312的笔记本电脑是大端");
	else printf("学号20181312的笔记本电脑是小端");
}

