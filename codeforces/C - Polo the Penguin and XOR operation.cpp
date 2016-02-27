#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 1000100
int t[3*N][2], cont;
int adj[3*N][2];

int n;
void init(int no){
	t[no][0] = t[no][1] = 0;
}

void add(int num){
	int at = 0;
	for(int x = 1 << 20; x; x >>= 1){
		int ind = (num & x) != 0;
		++t[at][ind];
		if(t[at][ind] == 1){
			init(cont);
			adj[at][ind] = cont++;
		}
		at = adj[at][ind];
	}
}

void remove(int num){
	int at = 0;
	for(int x = 1 << 20; x; x >>= 1){
		int ind = (num & x) != 0;
		--t[at][ind];
		at = adj[at][ind];
	}
}

int maxi(int num){
	int res = 0, at = 0;
	for(int x = 1 << 20; x; x >>= 1){
		int ind = (num & x) != 0;
		
		if(t[at][ind^1]) ind ^= 1;
			
		res |= x * (ind);
		at = adj[at][ind];
	}
	
	return res;
}

int perm[N];
bool foi[N];

int main(){
	scanf("%d", &n);
	init(0);
	cont = 1;
	cout.sync_with_stdio(false);
	for(int i = n; i >= 0; --i) add(i);
	
	long long soma = 0;
	for(int  i = n; i >= 0; --i){
		if(foi[i]) continue;
		int r = maxi(i);
		foi[i] = foi[r] = true;		
		remove(i), remove(r);
		
		soma += 2 * (r ^ i);
		perm[r] = i;
		perm[i] = r;
	}
	cout << soma << endl;
/*	rep(i, n+1){
		if(i) cout << " ";
		cout << perm[i];
	}*/
	cout << endl;
}

