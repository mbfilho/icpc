#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)

int prt;
char buf[10000];


double expr(){
	int lidos;
	if(buf[prt] == '('){
		++prt;
		double p, e1, e2;
		sscanf(buf+prt, "%lf", &p);
		while(buf[prt] != ' ') ++prt;
		++prt;
		
		e1 = expr();
		++prt;
		
		e2 = expr();
		if(buf[prt] != ')') throw 1;
		++prt;
		return p *(e1 + e2) + (1-p) * (e1 - e2);
	}else{
		double v;
		sscanf(buf+prt, "%lf%n", &v, &lidos);
		prt += lidos;
		return v;
	}
}


int main(){
	while(gets(buf) && strcmp(buf, "()")){
		prt = 0;
		printf("%.2lf\n", expr());
	}
}

