#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
typedef pair<int,int> pii;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define mp make_pair

int top;
char str[2][600];
char ma[35][35];
int n, m;

int pd[600][600];
bool marc[600][600];
pii mapa[600];

int dist(char a, char b){
	pii pa = mapa[a], pb = mapa[b];
	return max(abs(pa.first - pb.first), abs(pa.second - pb.second));
}


int faz(int minha, int certa){
	if(minha < 0)
		return -(certa + 1) * top;	
	
	int& ref = pd[minha][certa];
	if(marc[minha][certa]) return ref;
	marc[minha][certa] = true;
		
	ref = faz(minha - 1, certa - 1) + top - dist(str[1][minha], str[0][certa]);
	
	if(certa > minha)
		ref = max(ref, faz(minha, certa - 1) - top);

	return ref;
}

int main(){
	char buf[10];
	while(gets(buf)){
		sscanf(buf, "%d", &n);
		
		rep(i, n){
			gets(ma[i]);
			for(int j = 0; ma[i][j]; ++j)
				mapa[ma[i][j]] = mp(i,j);
		}
		m = strlen(ma[0]);
		
		int size[2];
		rep(i, 2){
			gets(str[i]);
			size[i] = strlen(str[i]);
		}
		top = max(n,m);
		memset(marc, false, sizeof marc);
		printf("%d\n", faz(size[1]-1, size[0]-1));
	}
}


