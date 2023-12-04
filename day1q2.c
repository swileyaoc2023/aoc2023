#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
int F=0;
#define FL __FILE__,__LINE__
#define PD printf("."); fflush(stdout)
#define tz(x) if(x){F+=1;printf("\n%s:%d:5:Fail: %s is %d not zero.",FL,#x,x);}else PD;
#define tde(x,y) if(x!=y){F+=1;printf("\n%s:%d:6:Fail: %s is %d not %d.",FL,#x,x,y);}else PD;
#define tse(x,y) if(strcmp(x,y)){F+=1;printf("\n%s:%d:6:Fail: %s %s not %s",FL,#x,x,y);}else PD;

char *todigits(char *s) {
	char *match[] = {"zero","one","two","three","four","five","six","seven","eight","nine"};
	int counters[] = {0,0,0,0,0,0,0,0,0,0};
	static char out[LINE_MAX/3];
	for(int i=0;i<10;i++)counters[i]=0;
	for(int i=0;i<LINE_MAX/3;i++)out[i]=0;
	if(s==NULL) return out;
	for(int i=0;s[i]!='\0';i++){
		for(int j=0;j<10;j++){
			if(match[j][counters[j]]==s[i]){
				counters[j]++;
				if(counters[j]==strlen(match[j])){
					counters[j]=0;
					out[strlen(out)]='0'+j;
					out[strlen(out)+1]='\0';
				}
			}else{
				counters[j]=s[i]==match[j][0]?1:0;
			}
		}
		if(isdigit(s[i])){
			out[strlen(out)]=s[i];
			out[strlen(out)+1]='\0';
		}
	}

	return out;
}
int ston(char *s) {
	if(s==NULL) return 0;
	if(strlen(s)<1) return 0;
	//printf("%s\n",s);
	int a=*(strpbrk(s,"0123456789"))-'0';
	int b=a;
	char *p=s;
	for(p=strpbrk(p,"0123456789");p!=NULL&&*p!='\0';p++) {
		if(isdigit(*p)) b=(*p)-'0';
	}
	return a * 10 + b;
}
void test(void) {
	tse(todigits("two1nine"),"219");
	tse(todigits("123456789"),"123456789");
	tse(todigits("onetwothreefourfivesixseveneightnine"),"123456789");
	tse(todigits("1a1twoneightwo3bcdeight"),"11218238");
	tz(ston(todigits(strdup("12")))-12);
	tz(ston(todigits(strdup("132")))-12);
	tz(ston(todigits(strdup("1332")))-12);
	tz(ston(todigits(strdup("1332")))-12);
	tz(ston(todigits(strdup("two1nine")))-29);
	tz(ston(todigits(strdup("eightwo")))-82);
	tz(ston(todigits(strdup("twone")))-21);
	tz(ston(todigits(strdup("1twone")))-11);
	tz(ston(todigits(strdup("eightwothree")))-83);
	tz(ston(todigits(strdup("abcone2threexyz")))-13);
	tz(ston(todigits(strdup("xtwone3four")))-24);
	tz(ston(todigits(strdup("4nineeightseven2")))-42);
	tz(ston(todigits(strdup("zoneight234")))-14);
	tz(ston(todigits(strdup("7pqrstsixteen")))-76);
	tz(ston(todigits(strdup("a12")))-12);
	tz(ston(todigits(strdup("a12b")))-12);
	tz(ston(todigits(strdup("a1c2b")))-12);
	tz(ston(todigits(strdup("a7c7b")))-77);
	tz(ston(todigits(strdup("a77c7b")))-77);
	tz(ston(todigits(strdup("a777c7b")))-77);
	tz(ston(todigits(strdup("7")))-77);
	tz(ston(todigits(strdup("7aaaaaaaaaa")))-77);
	tz(ston(todigits(strdup("aaaaaaaa7aaaaaaaaaa")))-77);
	tz(ston(todigits(strdup("aaaaaaaa7")))-77);
	tz(ston(todigits(strdup("six8frsx")))-68);
	tz(ston(todigits(strdup("zlmlk1")))-11);
	tz(ston(todigits(strdup("qkrsvjclp23")))-23);
	tz(ston(todigits(strdup("six8dbfrsxp\n")))-68);
	tz(ston(todigits(strdup("rvrnrdrninenine3zq6jqsr\n")))-96);
	tz(ston(todigits(strdup("bcmqn9onecnrzhsrsgzggzhtskjeightbz6khfhccktwonenrj")))-91);
	tz(ston(todigits(strdup("tthree5lrgtbxxvonezfmdpseven2")))-32);

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
		int cur=ston(todigits(buf));
		sum=sum+cur;
		//printf("%d %d,%s",cur,sum,buf);
		printf("%d %s",cur,buf);
	}
	printf("%d\n",sum);
}
int main() {
	test();
	challenge();
	return 0;
}

