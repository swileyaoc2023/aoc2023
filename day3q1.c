#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
//Test helpers
int F=0;
#define FL __FILE__,__LINE__
#define PD printf("."); fflush(stdout)
#define tz(x) if(x){F+=1;printf("\n%s:%d:5:Fail: %s is %d not zero.",FL,#x,x);}else PD;
#define tde(x,y) if(x!=y){F+=1;printf("\n%s:%d:6:Fail: %s is %d not %d.",FL,#x,x,y);}else PD;
#define tse(x,y) if(strcmp(x,y)){F+=1;printf("\n%s:%d:6:Fail: %s is %s not %s",FL,#x,x,y);}else PD;
#define FORCASES(cases,i) for(int i=0;i<(sizeof(cases)/sizeof(char *));i++)
//End test helpers
char *input="input.day3";
#define MAX_LABEL 3*4
#define MAX_OBS LINE_MAX

typedef struct ob_struct {
	int x;
	int y;
	char label[MAX_LABEL];
	int type;
} ob;
ob obs[MAX_OBS];
#define FOROBS(i) for(int i=0;i<MAX_OBS;i++)
#define FORCOB(x,i) FOROBS(i) if(obs[i].type>0&&obs[i].x)
#define FORLOB(i) FOROBS(i) if(obs[i].type>0)
void initobs(void){FOROBS(i) memset(&obs[i],0,sizeof(ob));}
int nextfreeob(void){FOROBS(i) if(obs[i].type==0)return i;return -1;}
int newob(int x, int y, char a,int type) {
	int i=nextfreeob();
	obs[i].x=x;
	obs[i].y=y;
	obs[i].label[0]=a;
	obs[i].label[1]='\0';
	obs[i].type=type;
	return i;
}
void ky(int miny){ FORCOB(y<miny,i) memset(&obs[i],0,sizeof(ob)); }
int isadj(int o, int s) {
	if(abs(obs[o].y - obs[s].y) > 1) return 0;
	int xoa=obs[o].x;
	int xob=xoa+strlen(obs[o].label)-1;
	int xsa=obs[s].x;
	int xsb=xsa+strlen(obs[s].label)-1;
	if(xoa >= xsa-1 && xoa <= xsb+1) return 1;
	if(xob >= xsa-1 && xob <= xsb+1) return 1;
	return 0;
}
int sumnonislands() {
	int sum=0;
	FORCOB(type==2,i) {
		int ncount=0;
		FORCOB(type==1,j){
			if(isadj(i,j)){
				printf("Adj");
				obs[i].type=3;
				ncount++;break;}else { printf("not adj");}
		}
		if(ncount)sum+=atoi(obs[i].label);
	}
	return sum;
}

void addobs(const char *s, int y) {
	int state=0;
	int curob=-1;
	for(int i=0;i<strlen(s);i++){
		if(s[i] == '.'|| s[i] == '\n' || s[i] == '\0'){
			state=0;
			continue;
		}
		if(isdigit(s[i])){
			if(!state){
				curob=newob(i,y,s[i],2);
				state=1;
			}else{
				obs[curob].label[strlen(obs[curob].label)]=s[i];
				obs[curob].label[strlen(obs[curob].label)+1]='\0';
			}
		}else{
			state=0;
			newob(i,y,s[i],1);
		}
	}
}
int obbylabel(char *s){FORLOB(i){if(strcmp(obs[i].label,s))return i;}return -1;}

char *lineof(int liney,int w) {
	static char line[LINE_MAX];
	int maxx=0;
	int lastx=0;
	FORCOB(y==liney,i){
		if(obs[i].x+strlen(obs[i].label)>maxx){
			maxx=obs[i].x+strlen(obs[i].label);
			memset(line+lastx,'.',maxx-lastx);
			lastx=maxx;
		}
		strcpy(line+obs[i].x,obs[i].label);
	}
	if(w>maxx){
		maxx=w;
		memset(line+lastx,'.',maxx-lastx);
		lastx=maxx;
	}
	line[maxx+1]='\0';
	return line;
}
int total(const char *line, int a, int *y) {
	const int maxage=3;
	if(*y>maxage){
		ky(*y-maxage);
	}
	addobs(line,*y);
	a=a+sumnonislands();
	*y+=1;
	return a;
}
void test(void) {
	char *examples[] ={
		"467..114..",
		"...*......",
		"..35..633.",
		"......#...",
		"617*......",
		".....+.58.",
		"..592.....",
		"......755.",
		"...$.*....",
		".664.598..",
	};
	int totals[] ={
		0,
		467,
		502,
		1135,
		1752,
		1752,
		2344,
		2344,
		3099,
		4361,
	};
	tse("..592.....","..592.....");
	printf("\nUnit tests:\n");
	initobs();
	tde(newob(2, 1, 'a',1),0);
	tde(nextfreeob(),1);
	tde(obs[0].x,2);
	tde(obs[0].y,1);
	tde(obs[0].label[0],'a');
	tde(obs[0].label[1],'\0');
	tde(obs[0].type,1);
	tde(newob(3, 1, 'a',1),1);
	tde(obs[1].x,3);
	tde(newob(2, 2, 'a',1),2);
	tde(obs[2].y,2);
	tde(newob(3, 2, 'a',1),3);
	tde(newob(4, 2, 'a',1),4);
	tde(newob(2, 4, 'a',1),5);
	tz(isadj(0,4));
	tz(isadj(0,5));
	tde(isadj(0,1),1);
	tde(isadj(0,2),1);
	tde(isadj(0,3),1);
	initobs();
	addobs("+123+",0);
	tse(lineof(0,5),"+123+");
	tse(obs[0].label,"+");
	tse(obs[1].label,"123");
	tse(obs[2].label,"+");
	tde(sumnonislands(0),123);
	initobs();
	addobs("..35..633.",1);
	addobs("......#...",2);
	tde(sumnonislands(1),633);
	printf("\nIntegration tests:\n");
	initobs();
	int sum,y=0;
	FORCASES(examples,i){
		sum=total(examples[i],sum,&y);
		tse(lineof(y-1,strlen(examples[i])),examples[i]);
		tde(sum,totals[i]);
	}
	if(!F) return;
	printf("\n%d fails\n",F);
	exit(1);
}
void challenge(void) {
	char buf[LINE_MAX];
	FILE *f = fopen(input,"r");
	//FILE *f = fopen("input","r");
	if(f==NULL) {printf("Please Download %s\n",input);exit(1);}
	int sum=0;
	int y=0;
	while(fgets(buf,LINE_MAX,f)) {
		buf[strlen(buf)-1]='\0';
		sum=total(buf,sum,&y);
	}
	printf("%d\n",sum);
}
int main() {
	test();
	challenge();
	return 0;
}

