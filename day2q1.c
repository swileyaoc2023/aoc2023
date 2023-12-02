#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
int F=0;
#define tz(x) if(x){F+=1;printf("\n%s is %d in %s:%d",#x,x,__FILE__,__LINE__);}else printf("."); fflush(stdout);

const char *fieldn(int n,const char *s) {
	for(;n>0&&s!=NULL&&*s!='\0';n--){
		s=index(s,' ');
		if(s==NULL) return s;
		if(*s==' ')s+=1;
	}
	return s;
}
int lenfn(int n, const char *s) {
	if(s==NULL|| *s=='\0') return 0;
	const char *a=fieldn(n,s);
	if(a==NULL|| *a=='\0') return 0;
	const char *b=fieldn(n+1,s);
	if(b==NULL)return strlen(a);
	return b-a-1;//XXX Breaks if fields have more than one delimiting char separating them.
}
int checkbins(const char *s,const char *names,const int max[]) {
	for(int tup=0;fieldn(tup*2,s)!=NULL&&fieldn(tup*2+1,s)!=NULL;tup++){
		int count=atoi(fieldn(tup*2,s));
		int colorindex=0;
		for(int i=0;fieldn(i,names)!=NULL;i++){
			if(!strncmp(fieldn((tup*2)+1,s),fieldn(i,names),lenfn(i,names))){
				colorindex=i;
				break;
			}
		}
		if(count>max[colorindex]){
			return count-max[colorindex];
		}
	}
	return 0;
}
int idifinvalid(const char *s) {
	int id=atoi(fieldn(1,s));
	if(checkbins(fieldn(2,s),"red green blue",(int[]){12,13,14}))
		return id;
	return 0;
}

void test(void) {
	const char *numbers="zero one two three four five six seven eight nine";
	const char *countdown="nine eight seven six four five three two one zero";
	tz(atoi(fieldn(0,numbers)));
	tz(atoi(fieldn(1,numbers))-atoi(fieldn(9,numbers)));
	tz(atoi(fieldn(5,numbers))-0);
	tz(lenfn(0,numbers)-4);
	tz(lenfn(1,numbers)-3);
	tz(lenfn(9,numbers)-4);
	tz(checkbins("3 aa 4 bb 4 cc","aa bb cc",(int[]){3,4,5}));
	tz(checkbins("3 aa 4 bb 5 cc","aa bb cc",(int[]){3,4,5}));
	tz(checkbins("3 aa 4 bb 6 cc","aa bb cc",(int[]){3,4,5})-1);
	tz(idifinvalid("Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green")-0);
	tz(idifinvalid("Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red")-3);
	tz(idifinvalid("Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green")-0);
	puts("");
	if(!F) return;
	printf("%d fails\n",F);
	exit(1);
}
void challenge(void) {
	char buf[LINE_MAX];
	FILE *f = fopen("input.day2","r");
	if(f==NULL) {printf("Please Download input.day2\n");exit(1);}
	int sum=0;
	while(fgets(buf,LINE_MAX,f)) {
		puts(buf);
	}
}
int main() {
	test();
	challenge();
	return 0;
}

