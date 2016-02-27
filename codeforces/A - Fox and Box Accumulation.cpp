#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)

//Algoritmo estranho
int piles[200], tmp[200], n;

bool pode(int qtd){
	int ind = 0;
	memset(tmp, 0x7f, sizeof tmp);
	
	while(ind < n){
		bool dm = true;
		
		rep(i, qtd){
			if(ind >= n) return true;
			
			if(tmp[i]){
				tmp[i] = min(tmp[i] - 1, piles[ind]);
				++ind;
				dm = false;
			}
		}
		
		if(dm) return false;
	}
	
	return true;
}

int main(){
	ios::sync_with_stdio(false);
	
	cin >> n;
	rep(i, n) cin >> piles[i];
	sort(piles, piles + n), reverse(piles, piles + n);
		
	int ini = 1, fim = n;
	while(ini <= fim){
		int mid = (ini+fim)>>1;
		
		if(pode(mid)) fim = mid - 1;
		else ini = mid + 1;
	}
	
	cout << fim + 1 << endl;
}
