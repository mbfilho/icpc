#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define LG 21
#define N 100100

int cnt[N][LG];
int a[N];
int n;
int pot[LG];

void pre(){
	rep(i, LG) pot[i] = 1 << i;
	
	fr(i, 1, n+1){
		rep(j, LG) cnt[i][j] = cnt[i-1][j];
		
		int j = 0, tmp = a[i];
		
		while(tmp){
			if(tmp & 1) ++cnt[i][j];
			++j;
			tmp >>= 1;
		}
	}	
}



int count(int i, int j){
	int resp = 0;
	rep(k, LG){
		if(cnt[j][k] != cnt[i-1][k]){
			resp |= pot[k];
		}
	}
	
	return resp;
}

int conj[1<<21];

int faz(){
	int c = 0;
	
	fr(i, 1, n+1){
		int end = i, mask = a[i];
		
		while(end <= n){
			if(!conj[mask]) ++c;
			conj[mask]++;
			
			int ini = end, fim = n, best = -1, nmask;
			
			while(ini <= fim){
				int mid = (ini+fim)/2, eval = count(i, mid);
				if(eval == mask){
					ini = 1 + mid;		
				}else{
					best = mid;
					nmask = eval;
					fim = mid - 1;	
				}
			}
			if(~best){
				end = best;
				mask = nmask;
			}else end = n + 1;
		}
	}
	
	return c;
}

int main(){
	scanf("%d", &n);
	fr(i, 1, n+1) scanf("%d", a + i);
	pre();
	printf("%d\n", faz());	
}

