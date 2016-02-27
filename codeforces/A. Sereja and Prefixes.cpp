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

struct no{
	int t, x, l, c;
	ll ini, tam;
	no(){}
	no(int xx):t(1), x(xx){}
	no(int ll, int cc):t(2), l(ll), c(cc){}
};
vector<no> ops;

int get(int lim, ll ind){
	int ini = 0, fim = lim, mid = -1;
	while(ini <= fim){
		mid = (ini+fim)>>1;
		if(ind >= ops[mid].ini && ind < ops[mid].ini + ops[mid].tam){
			break;
		}else if(ind < ops[mid].ini) fim = mid - 1;
		else ini = mid + 1;
	}
	
	if(mid==-1) throw 1;
	
	if(ops[mid].t == 1) return ops[mid].x;
	
	ll tmp = ind - ops[mid].ini;
	int aux = tmp % ops[mid].l;
	
	return get(mid - 1, aux + 1);
}



int main(){
	int m;
	scanf("%d", &m);
	ll at = 1;
	rep(i, m){
		no tmp;
		scanf("%d", &tmp.t);
		if(tmp.t == 1){
			scanf("%d", &tmp.x);
			tmp.tam = 1;
			tmp.ini = at;
		}else{
			scanf("%d %d", &tmp.l, &tmp.c);
			tmp.tam = tmp.l * ll(tmp.c);
			tmp.ini = at;
		}
		at += tmp.tam;
		ops.pb(tmp);
	}
	
	int n;
	scanf("%d", &n);
	while(n--){
		ll ind;
		cin >> ind;
		printf("%d", get(ops.size()-1, ind));
		if(n) printf(" ");
	}
	printf("\n");
}



