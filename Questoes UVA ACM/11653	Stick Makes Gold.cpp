#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define Fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,a) Fr(i,0,a)
#define Q 150000
typedef long long ll;

struct No{
	int a, b, t, prio;
	
	No(){}
	No(int aa, int bb, int tt, int pp){
		a = aa;
		b = bb;
		t = tt;
		prio = pp;
	}
	
	bool operator<(const No& x) const{
		int pos = max(a,b), pos2 = max(x.a, x.b);
		if(pos != pos2) return pos < pos2;
		return prio < x.prio;
	}
};

vector<No> nos;
int n, m;

void get(ll a, int grau, ll pol[]){
	rep(i, 4) pol[i] = 0;
	
	if(grau == 1){ //p.a
		pol[0] += -a;
		pol[1] += 1;
	}else if(grau == 2){ //quad
		pol[0] += a*a;
		pol[1] += -2*a;
		pol[2] += 1;
	}else{
		pol[0] += -a*a*a;
		pol[1] += 3*a*a;
		pol[2] += -3*a;
		pol[3] += 1;
	}
}
int querys[Q];

int main(){
	int t;
	scanf("%d", &t);
	
	rep(caso, t){
		printf( "Case %d:\n", caso + 1);
		nos.clear();
		
		scanf("%d%d", &n, &m);
		rep(i, m){
			int a, b, t;
			scanf("%d%d%d", &t, &a, &b);
			nos.push_back(No(a, -10, t, 0));
			nos.push_back(No(a, b, t, 2));
		}
		
		int q;
		scanf("%d", &q);
		
		rep(i, q){
			scanf("%d", querys + i);
		}
		
		sort(nos.begin(), nos.end());
		ll pol[] = {0,0,0,0}, r[] = {0,0,0,0}, total = 0;
		int atQ = 0, prt = 0;
		rep(i, n+1){
			ll a = i;

			while(prt < nos.size() && nos[prt].a == i && nos[prt].prio == 0){
				get(nos[prt].a, nos[prt].t, r);
				rep(j,4) pol[j] += r[j];
				++prt;
			}
			
			total += pol[3] * a*a*a + pol[2]*a*a + pol[1] * a + pol[0];

			while(atQ < q && querys[atQ] == i){
				printf( "%llu\n", total);
				++atQ;
			}

			while(prt < nos.size() && nos[prt].b == i && nos[prt].prio == 2){
				get(nos[prt].a, nos[prt].t, r);
				rep(j,4) pol[j] -= r[j];
				++prt;
			}
		}
		
	}
}



