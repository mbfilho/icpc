#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
typedef pair<int,int> pii;
#define mp make_pair
#define no first
#define qtd second
typedef vector<int> chain;
#define pb push_back
#define N 4000

int ma[N][N];

int num;

void makeComp(chain& cha){
	if(cha.empty()){
		cha.pb(num);
		num += 4;
	}else{
		cha.pb(num-1);
		num += 3;
	}	
}

chain makeChain(int order){
	chain cha;
	rep(i, order) makeComp(cha);
	
	return cha;
}

void add(int u, int v){
	ma[u][v] = ma[v][u] = 1;
}

void makeLine(int ini, int which, int largest){
	int last = ini + (which - 1) * 3;
	
	fr(i, which, largest+1){
		add(last, num);
		add(num, num+1);
		last = num + 1; 
		num += 2;
	}
	
	add(last, 2);
}

void faz(int k){
	memset(ma, false, sizeof ma);
	num = 3;

	if(k == 1) return add(1,2), void();
	
	chain largest;
	
	for(int i = 31; i > 0; --i){
		if((1<<i) & k){
			largest = makeChain(i);
			break;
		}
	}
	
	int last = 1;
	rep(j, largest.size()){
		int a = largest[j];
		if(last != a) add(last, a);
			
		add(a, a+1), add(a, a+2), add(a+1, a+3), add(a+2, a+3);
				
		last = a + 3;
	}
	add(last, 2);
	
	for(int i = largest.size() - 1; i > 0; --i){
		if((1<<i) & k){
			makeLine(3, i+1, largest.size());
		}	
	}		
	
	if(k&1){
		makeLine(3, 1, largest.size());
	}
	
}

int main(){
	int k;
	cin >> k;

	faz(k);

	cout << num-1 << endl;

	fr(i, 1, num){
		fr(j, 1, num) cout << (ma[i][j] ? "Y" : "N");
		cout << endl;
	}
}
