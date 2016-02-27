#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)


char buf[10000];
char tmp[10000];
char op[10];

int main(){
	while(scanf("%s %s", op, buf) == 2 && (strcmp(op, "0") || strcmp(buf, "0"))){
		int prt = 0;
		for(int i = 0; buf[i]; ++i){
			if(buf[i] != op[0])
				tmp[prt++] = buf[i];
		}
		tmp[prt] = 0;
		
		int x = 0;
		while(x < prt && tmp[x] == '0') ++x;
		if(x < prt && tmp[x] != '0')
			printf("%s\n", tmp + x);
		else 
			printf("0\n");
	}
}

