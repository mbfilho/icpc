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
#define mp make_pair
#define X first
#define Y second
#define pb push_back
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define each(it, m) for(__typeof(m.begin()) it = m.begin(); it != m.end(); ++it)
#define N 100100
#define T (2*N)
#define oo 2000000000
int input[N];
ll resp[N];
int n;

int esq[T], dir[T], menor[T];
int tree;

int build(int no, int x, int y){
	if(x != y){
		int mid = (x+y)/2;
		esq[no] = build(tree++, x, mid);
		dir[no] = build(tree++, mid+1, y);
		menor[no] = min(menor[esq[no]], menor[dir[no]]);
	}else esq[no] = dir[no] = -1, menor[no] = input[x];
	
	return no;
}

int query(int no, int x, int y, int ini, int fim){
	if(ini > y || fim < x) return oo;
	if(ini <= x && fim >= y){
		return menor[no];
	}else{
		int mid = (x+y)/2;
		int menor = query(esq[no], x, mid, ini, fim);
		menor = min(menor, query(dir[no], mid+1, y, ini, fim));
		
		return menor;
	}
}

int query(int x, int y){
	return query(0, 0, n-1, x, y);
}

int x;
int main(){
	ios::sync_with_stdio(false);
	cin >> n >> x;
	--x;
	int menor;
	rep(i, n){
		cin >> input[i];
		if(!i) menor = input[i];
		else menor = min(menor, input[i]);
	}
	tree = 0;
	build(tree++, 0, n-1);
	
	int ind = -1;
	rep(i, n){
		if(i != x){
			if(input[i] == menor){
				int tmp = oo;
				if(x > i) tmp = query(i+1, x);
				else{
					if(i+1 != n)
						tmp = query(i+1, n-1);
					tmp = min(tmp, query(0, x));		
				}
				
				if(tmp > input[i]){
					ind = i;
					break;
				}
			}
		}else{
			if(input[i] == menor){
				ind = i;
				break;
			}
		}
	}
	int k = input[ind], d = 0;
	rep(i, n) resp[i] = input[i] - k;
	if(ind < x){
		fr(i, ind+1, x+1) --resp[i];
		d = x - ind;
	}else if(ind > x){
		fr(i, ind+1, n) --resp[i];
		d = n - ind - 1;
		fr(i, 0, x+1) --resp[i];
		d += x+1;
	}
	resp[ind] = ll(k) * ll(n) + d;
	rep(i, n){
		if(i) cout << " ";
		cout << resp[i];
	}
	cout << endl;
}


