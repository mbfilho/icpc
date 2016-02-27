#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <iostream>
using namespace std;
typedef long long ll;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
#define ft first
#define N 250100
typedef unsigned long long hash;
#define BASE 37
#define S 1000000
char A[N], B[N];
int ta, tb;

set<hash> mk;

int valid[S], step;
vector<hash> mapa[S];

void clear(int v){
	if(valid[v] != step) valid[v] = step, mapa[v].clear();
}
void put(hash val){
	int ind = val % S;
	clear(ind);
	mapa[ind].pb(val);
}
bool contains(hash val){
	int ind = val % S;
	if(valid[ind] != step) return false;

	return find(mapa[ind].begin(), mapa[ind].end(), val) != mapa[ind].end();
}

int test(int size){
	++step;

	hash pot = 1;
	rep(i, size -1) pot *= BASE;
	hash ha = 0, hb = 0;
	rep(i, size) ha = ha * BASE + A[i] - 'a', hb = hb * BASE + B[i] - 'a';
	put(ha);

	fr(i, size, ta){
		ha = ha - (A[i-size] - 'a') * pot;
		ha = ha * BASE + A[i] - 'a';
		put(ha);
	}

	// for (std::set<hash>::iterator i = mk.begin(); i != mk.end(); ++i)
	// {
	// 	cout << *i << endl;
	// }

	if(contains(hb)) return 0;

	// cout << "*" << hb << endl;
	fr(i, size, tb){
		hb = hb - (B[i-size] - 'a') * pot;
		hb = hb * BASE + B[i] - 'a';
		if(contains(hb)) return i - size + 1;
	}

	return -1;
}




int main(){
	ios::sync_with_stdio(false);

	cin >> A >> B;
	ta = strlen(A), tb = strlen(B);
	int ini = 1, fim = min(ta, tb), ind = -1;

	// cout << test(2) << endl;
	// return 0;

	while(ini <= fim){
		int mid = (ini+fim)>>1;
		int tmp = test(mid);
		if(~tmp) ind = tmp, ini = mid + 1;
		else fim = mid - 1;
	}

	if(~ind) B[ind+ini-1] = 0, cout << B+ind << endl << ini-1 << endl;
	else cout << "0" << endl;
}
