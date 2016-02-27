#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <string>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
typedef long double ld;
#define mp make_pair
#define ft first
#define sd second
#define pb push_back
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define conj sdkjfhsdkhjf
#define N 100100
#define T (2*N)
int esq[T], dir[T], cont;
ll maior[T], op[T];
int a[N], n;

int build(int no, int x, int y){
	op[no] = -1;
	
	if(x != y){
		int mid = (x+y)/2;
		esq[no] = build(cont++, x, mid);
		dir[no] = build(cont++, mid+1, y);
		maior[no] = max(maior[esq[no]], maior[dir[no]]);
	}else
		maior[no] = a[x], esq[no] = dir[no] = -1;
		
	return no;
}

void fix(int no){
	if(~op[no]){
		maior[no] = op[no];
		if(~esq[no]) op[esq[no]] = op[dir[no]] = op[no];
		op[no] = -1;
	}
}


int ini, fim;
ll query(int no, int x, int y){
	fix(no);
	if(x > fim || y < ini) return -1;
	
	if(ini <= x && fim >= y){
		return maior[no];
	}else{
		int mid = (x+y)/2;
		return max(query(esq[no], x, mid), query(dir[no], mid+1, y));
	}
}

ll valor;
void setar(int no, int x, int y){
	fix(no);
	if(x > fim || y < ini) return;
	
	if(ini <= x && fim >= y){
		op[no] = valor;
		fix(no);
	}else{
		int mid = (x+y)/2;
		setar(esq[no], x, mid);
		setar(dir[no], mid+1, y);
		
		maior[no] = max(maior[esq[no]], maior[dir[no]]);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin >> n;
	rep(i, n) cin >> a[i];
	cont = 0;
	build(cont++, 0, n-1);
	
	int q;
	cin >> q;
	while(q--){
		ll w, h;
		cin >> w >> h;
		ini = 0, fim = w-1;
		ll high = query(0, 0, n-1);
		cout << high << endl;
		valor = high + h;
		setar(0, 0, n-1);
	}
}

