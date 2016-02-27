#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define mp make_pair
#define TREE 300000
int esq[TREE], dir[TREE], size[TREE];
ll soma[TREE], triang[TREE], ops[TREE];
int cont;


void ajeita(int no){
	soma[no] += size[no] * ops[no];
	triang[no] += ((ops[no] + size[no] * ops[no]) * size[no]) / 2;

	if(~esq[no]){
		ops[esq[no]] += ops[no];
		ops[dir[no]] += ops[no];
	}
	ops[no] = 0;
}

void update(int no){
	soma[no] = soma[esq[no]] + soma[dir[no]];
	triang[no] = triang[esq[no]] + triang[dir[no]] + size[esq[no]] * soma[dir[no]];
}

int build(int no, int x, int y){
	size[no] = y - x + 1;
	ops[no] = 0;
	
	if(x == y){
		esq[no] = dir[no] = -1;
		soma[no] = triang[no] = 100;
	}else{
		int mid = (x+y)/2;
		esq[no] = build(cont++, x, mid);
		dir[no] = build(cont++, mid + 1, y);
		update(no);
	}
	
	return no;
}

void change(int no, int x, int y, int ini, int fim, int val){
	ajeita(no);
	if(ini > y || fim < x) return;
	
	if(ini <= x && fim >= y){
		ops[no] += val;
		ajeita(no);
	}else{
		int mid = (x+y)/2;
		change(esq[no], x, mid, ini, fim, val);
		change(dir[no], mid+1, y, ini, fim, val);
		update(no);
	}
}

int getTam(int x, int y, int ini, int fim){
	int size = min(fim, y) - max(x, ini);
	return max(size + 1, 0);
}

pair<ll,ll> getSum(int no, int x, int y, int ini, int fim){
	ajeita(no);
	if(ini > y || fim < x) return mp(0,0);
	
	if(ini <= x && fim >= y){
		return mp(triang[no], soma[no]);
	}else{
		int mid = (x+y)/2;
		pair<ll,ll> t[] = {getSum(esq[no], x, mid, ini, fim), getSum(dir[no], mid + 1, y, ini, fim)};
		
		ll tri = t[0].first + t[1].first + getTam(x, mid, ini, fim) * t[1].second;
		ll plano = t[0].second + t[1].second;
		
		return mp(tri, plano);
	}
}

int main(){
	int t;
	scanf("%d", &t);
	
	rep(cas, t){
		int n, q;
		scanf("%d%d", &n, &q);
		cont = 0;
		int root = build(cont++, 1, n);
		
		char buf[20];
		printf("Case %d:\n", cas + 1);
		while(q--){
			int i, j;
			scanf("%s%d%d", buf, &i, &j);
			if(buf[0] == 'q'){
				printf("%lld\n", getSum(root, 1, n, i, j).first);
			}else{
				int u;
				scanf("%d", &u);
				change(root, 1, n, i, j, u);
			}
		}
	}
}







