#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 1100
#define K 110
#define MOD 1000000007
int n, m, k;
int pd[N][1<<4][K], mk[N][1<<4][K], caso;

int A[N], primos[N], cont;

void pre(){
	memset(A, -1, sizeof A);
	cont = 0;
	fr(i, 2, N){
		if(A[i] == -1){
			A[i] = cont;
			primos[cont++] = i;
		}
		
		rep(j, A[i]+1){
			ll nt = ll(primos[j]) * i;
			if(nt >= N) break;
			A[nt] = j;
		}
	}
}

int pm[10], prt;
int moedas[N], mask[N], cm;

int main(){
	pre();
	
	while(scanf("%d%d%d", &n, &m, &k) == 3){
		++caso;
		{
			int tmp = m;
			prt = 0;
			while(tmp != 1){
				pm[prt] = primos[A[tmp]];
				do{
					tmp /= pm[prt];
				}while(tmp % pm[prt] == 0);
				++prt;
			}
		}
		
		cm = 0;
		fr(i, 1, n+1){
			if((m % i) == 0){
				moedas[cm] = i;
				mask[cm] = 0;
				rep(x, prt){
					if((m / i) % pm[x])
						mask[cm] |= (1<<x);
				}
				++cm;
			}
		}
		
		mk[0][0][0] = caso;
		pd[0][0][0] = 1;
		
		rep(sum, n+1){
			rep(msk, (1<<prt)){
				rep(kk, k+1){
					if(mk[sum][msk][kk] == caso){
						rep(i, cm){
							int nsum = sum + moedas[i], nmask = msk | mask[i];
							if(nsum <= n && kk < k){
								if(mk[nsum][nmask][kk+1] != caso) mk[nsum][nmask][kk+1] = caso, pd[nsum][nmask][kk+1] = 0;
								pd[nsum][nmask][kk+1] += pd[sum][msk][kk];
								pd[nsum][nmask][kk+1] %= MOD;
							}
						}
					}
				}
			}
		}
		
		if(mk[n][(1<<prt)-1][k] == caso) printf("%d\n", pd[n][(1<<prt)-1][k]);
		else printf("0\n");
	}
}

