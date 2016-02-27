#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define pb push_back
#define ft first
#define sd second
#define mp make_pair
typedef long long ll;
typedef pair<int,int> pii;
#define N 1000100
#define LOGN 20
struct no{
	int tam, a, f;
	no():tam(0),a(0), f(0){}
	void init(int aa, int ff){
		a = aa, f = ff;
		tam = 0;
	}
};

no pd[N][LOGN];
char str[N];
int n;

void pre(){
	n = strlen(str);
	
	rep(i, n) pd[i][0].init(str[i] == '(', str[i] == ')');
	
	for(int t = 1; (1<<t) <= n; ++t){
		rep(i, n){
			int j = i + (1<<(t-1)), inc;
			if(j >= n) break;
			pd[i][t].tam = pd[i][t-1].tam + pd[j][t-1].tam;
			inc = min(pd[i][t-1].a, pd[j][t-1].f);
			pd[i][t].tam += inc;
			pd[i][t].a = pd[i][t-1].a + pd[j][t-1].a - inc;
			pd[i][t].f = pd[i][t-1].f + pd[j][t-1].f - inc;
		}
	}
}

#define A first
#define F second
int query(int i, int j){
	int tam = j - i + 1, ind = 0, resp = 0;
	vector<pii> tmp;
	while(tam){
		if(tam & 1){
			tmp.pb(mp(pd[i][ind].a, pd[i][ind].f));
			resp += pd[i][ind].tam;
			i += (1 << ind);
//			printf("> SIM %d\n", pd[i][ind].tam);
		}
		tam >>= 1;
		++ind;
	}
	
	rep(i, tmp.size()){
		fr(j, i+1, tmp.size()){
			int inc = min(tmp[i].A, tmp[j].F);
			tmp[i].A -= inc;
			tmp[j].F -= inc;
			resp += inc;
		}
	}
	return resp;
}


int main(){
	scanf("%s", str);
	pre();
	int q;
	scanf("%d", &q);
	while(q--){
		int a, b;
		scanf("%d %d", &a, &b);
		printf("%d\n", 2*query(a-1, b-1));
	}
}



