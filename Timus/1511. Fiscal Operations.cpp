#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define oo 10000000
#define N 2000

int pd[N][2];

int num[3][N];
int tam[3];

int faz(int no, int carry){
	int& best = pd[no][carry];
	if(~best) return best;
	best = oo;
	
	if(no < min(tam[1], tam[0])){
		rep(i, 10){
			if(no == tam[0]-1 && !i) continue;
			rep(j, 10){
				if(no == tam[1]-1 && !j) continue;
			
				int dig = (carry + i + j) ;
				int soma = abs(i - num[0][no]) + abs(j - num[1][no]) + abs( (dig%10) - num[2][no]);
				int ncarry = dig / 10;
				if(no == tam[2]-1 && !(dig%10)) continue;
				best = min(best, soma + faz(no+1, ncarry));
			}
		}
	}else{
		if(no == tam[2]){
			if(carry) return best = oo;
			return best = 0;
		}
		
		if(no == max(tam[0], tam[1])){
			if(tam[2] == 1 + max(tam[0], tam[1]) && carry){
				return best = abs(carry - num[2][max(tam[0], tam[1])]);
			}
			return best = oo;
		}else{
			int x = 0;
			if(tam[1] > tam[0]) x = 1;
			
			rep(i, 10){
				int dig = carry + i;
				int soma = abs(i - num[x][no]) + abs((dig%10) - num[2][no]);
				int ncarry = dig / 10;
				
				if(no == tam[2]-1 && !(dig%10)) continue;
				best = min(best, soma + faz(no+1, ncarry));
			}
		}
	}
	
	return best;
}

char buf[20000];

int main(){
	memset(pd, -1, sizeof pd);
	
	rep(i, 3){
		scanf("%s", buf);
		tam[i] = 0;
		for(int j = 0; buf[j]; ++j){
			num[i][j] = buf[j] - '0';
			++tam[i];
		}
		reverse(num[i], num[i] + tam[i]);
	}
	
	if(tam[2] < max(tam[0], tam[1]))
		printf("-1\n");
	else{
		int resp = faz(0,0);
	
		if(resp < oo)
			printf("%d\n", resp);
		else printf("-1\n");
	}
}







