#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define S 5010
#define N S
#define B 47
typedef unsigned long long H;

char buf[S];
int tam;

H hash[2][S], pot[S];

H get(int i, int j, int k){
	if(!k)
		return hash[k][j] - hash[k][i-1] * pot[j-i+1];
	else
		return hash[k][i] - hash[k][j+1] * pot[j-i+1];
	
}

void calc(int k){
	if(!k){
		hash[k][0] = 0;
		rep(i, tam)
			hash[k][i+1] = hash[k][i] * B + buf[i] - 'a' + 1;
	}else{
		hash[k][tam+1] = 0;
		for(int i = tam; i > 0; --i)
			hash[k][i] = buf[i-1] - 'a' + 1 + hash[k][i+1] * B;
	}
}

int mk[N][N], sum[N][N];

int get(int i, int j){
	return sum[j][j] - sum[i][j] - sum[j][i] + sum[i][i];
}

int main(){
	pot[0] = 1;
	fr(i, 1, S) pot[i] = B * pot[i-1];
	
	scanf("%s", buf);
	tam = strlen(buf);
	calc(0);
	calc(1);
	rep(i, tam){
		fr(j, i, tam){
			if(get(i+1, j+1, 0) == get(i+1, j+1, 1)){
				++mk[i+1][j+1];
			}
		}
	}
	
	fr(i, 1, tam+1){
		fr(j, 1, tam+1)
			sum[i][j] = mk[i][j] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
	}
	
	int q;
	scanf("%d", &q);
	while(q--){
		int i, j;
		scanf("%d%d", &i, &j);
		printf("%d\n", get(i-1,j));
	}
	
}




