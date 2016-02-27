#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)

#define N 110

int resp[N];
int n;

int main(){
	scanf("%d", &n);
	
	rep(i, n){
		resp[i] = 0;
		rep(j, n){
			int tmp;
			scanf("%d", &tmp);
			if(i!=j) resp[i] |= tmp;
		}
	}
	
	rep(i, n){
		if(i) printf(" ");
		printf("%d", resp[i]);
	}
	printf("\n");
}

