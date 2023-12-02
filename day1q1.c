#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
int F=0;
#define tz(x) if(x){F+=1;printf("\n%s is %d on %s:%d",#x,x,__FILE__,__LINE__);}else printf(".");

int ston(char *s) {
	if(s==NULL) return 0;
	int a=*(strpbrk(s,"0123456789"))-'0';
	int b=a;
	char *p=s;
	for(p=strpbrk(p,"0123456789");p!=NULL&&*p!='\0';p++) {
		if(isdigit(*p)) b=(*p)-'0';
	}
	return a * 10 + b;
}
void test(void) {
	tz(ston(strdup("12"))-12);
	tz(ston(strdup("132"))-12);
	tz(ston(strdup("1332"))-12);
	tz(ston(strdup("a12"))-12);
	tz(ston(strdup("a12b"))-12);
	tz(ston(strdup("a1c2b"))-12);
	tz(ston(strdup("a7c7b"))-77);
	tz(ston(strdup("a77c7b"))-77);
	tz(ston(strdup("a777c7b"))-77);
	tz(ston(strdup("7"))-77);
	tz(ston(strdup("7aaaaaaaaaa"))-77);
	tz(ston(strdup("aaaaaaaa7aaaaaaaaaa"))-77);
	tz(ston(strdup("aaaaaaaa7"))-77);
	tz(ston(strdup("six8frsx"))-88);
	tz(ston(strdup("zlmlk1"))-11);
	tz(ston(strdup("qkrsvjclp23"))-23);
	tz(ston(strdup("six8dbfrsxp\n"))-88);
	tz(ston(strdup("rvrnrdrninenine3zq6jqsr\n"))-36);
	tz(ston(strdup("34"))-34);
	tz(ston(strdup("56"))-56);
	tz(ston(strdup("78"))-78);
	tz(ston(strdup("90"))-90);
	puts("");
	if(!F) return;
	printf("%d fails\n",F);
	exit(1);
}
void challenge(void) {
	char buf[LINE_MAX];
	FILE *f = fopen("input.day1","r");
	if(f==NULL) {printf("Please Download input.day1\n");exit(1);}
	int sum=0;
	while(fgets(buf,LINE_MAX,f)) {
		printf("%d %d,%s",ston(buf),sum+=ston(buf),buf);
	}
}
int main() {
	test();
	challenge();
	return 0;
}

