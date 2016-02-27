#include <cstdio>
#include <cstring>

using namespace std;
typedef long long ll;
#define Fr(i,a,b) for(int i=a;i<b;++i)
#define rep(i,n) Fr(i,0,n)
#define MOD 1000007
int marc[43][1<<7][2][3][4][5][6];
int pd[43][1<<7][2][3][4][5][6];
int n, pot[7][45];
int cas;
int faz(int no, int mask, int d, int t, int q, int c, int s){
//	printf( "%d %d %d %d %d %d %d\n", no, mask, d, t, q, c, s);
	int& ref = pd[no][mask][d][t][q][c][s];
	if(marc[no][mask][d][t][q][c][s] == cas) return ref;
	marc[no][mask][d][t][q][c][s] = cas;
	if(no == n){
		int aux[] = {d, t, q, c, s};
		rep(i, 5){
			if(((1<<i) & mask) && aux[i]){ 
				return ref = 0;
			}
		}
		return ref = 1;
	}
	ref = 0;
	
	Fr(i, 1, 7){
		int nmask = mask;
		if(i >=2)
			nmask |= (1 << (i-2));
		ref = (ref + faz(no+1, nmask, (d + i*pot[2][no]) % 2, (t + i*pot[3][no]) % 3, (q + i*pot[4][no]) % 4, (c + i*pot[5][no]) % 5, (s+i*pot[6][no]) % 6)) % MOD;
	}
	
	return ref;
}

int main(){
	Fr(i, 1, 7) pot[i][0] = 1;
	Fr(i, 1, 7){
		Fr(j, 1, 45) pot[i][j] = (10 * pot[i][j-1]) % i;
	}
	
	int t;
	scanf("%d", &t);
	
	memset(marc, 0, sizeof marc);
	cas = 0;
	while(t--){
		++cas;
		scanf("%d", &n);
		
		int resp = faz(0, 0, 0, 0, 0, 0, 0);
		printf( "%d\n", resp);
	}
}


