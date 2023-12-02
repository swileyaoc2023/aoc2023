#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
int F=0;
#define tz(x) if(x){F+=1;printf("\n%s is %d in %s:%d",#x,x,__FILE__,__LINE__);}else printf(".");

char *smush(char *s) {//To avoid memory allocation we encode the NDFA directly
	char *match[] = {"zero","one","two","three","four","five","six","seven","eight","nine"};
	int counters[] = {0,0,0,0,0,0,0,0,0};
	memset(counters,0,sizeof(int)*10);
	for(int i=0;i<strlen(s);i++){
		for(int matcher=0;matcher<10;matcher++){
			if(match[matcher][counters[matcher]]==s[i]){
				//printf("\n%c",s[i]);for(int j=0;j<10;j++)printf("%d ",counters[j]);
				counters[matcher]+=1;
				if(counters[matcher]==strlen(match[matcher])){
					int back=i-(strlen(match[matcher])-1);
					int start=i;
					int len=strlen(s+i)+2;
					len=strlen(s+i);
					memmove(s+back,s+start,len);
					s[back+len]=0;
					s[i-strlen(match[matcher])+1]=matcher+'0';
					i=start-strlen(match[matcher]);
					memset(counters,0,sizeof(int)*10);
					//printf("\n%s %d\n",s,i);
					//for(int j=0;j<i;j++)printf(" ");
					//printf("^\n");
				}
			} else {
				counters[matcher]=0;
			}
		}
	}
	return s;
}
int ston(char *s) {
	if(s==NULL) return 0;
	if(strlen(s)<1) return 0;
	int a=*(strpbrk(s,"0123456789"))-'0';
	int b=a;
	char *p=s;
	for(p=strpbrk(p,"0123456789");p!=NULL&&*p!='\0';p++) {
		if(isdigit(*p)) b=(*p)-'0';
	}
	return a * 10 + b;
}
void test(void) {
	tz(ston(smush(strdup("12")))-12);
	tz(ston(smush(strdup("rxzsnjhcnkthree8eight")))-38);
	tz(ston(smush(strdup("132")))-12);
	tz(ston(smush(strdup("two1nine"))-29));
	tz(ston(smush(strdup("1332")))-12);
	tz(ston(smush(strdup("eightwothree")))-83);
	tz(ston(smush(strdup("fivetczxxvjrrqfive1sevennvj6one3")))-53);
	tz(ston(smush(strdup("abcone2threexyz")))-13);
	tz(ston(smush(strdup("vqjvxtc79mvdnktdsxcqc1sevenone")))-71);
	puts("");
	if(!F) return;
	printf("%d fails\n",F);
	exit(1);
}
void challenge(void) {
	char buf[LINE_MAX];
	FILE *f = fopen("input.day1","r");
	//FILE *f = fopen("input","r");
	if(f==NULL) {printf("Please Download input.day1\n");exit(1);}
	int sum=0;
	while(fgets(buf,LINE_MAX,f)) {
		puts(buf);
		int cur=ston(smush(buf));
		sum=sum+cur;
		printf("%d %d,%s",cur,sum,buf);
	}
}
int main() {
	test();
	challenge();
	return 0;
}

