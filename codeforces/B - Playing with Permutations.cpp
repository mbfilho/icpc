#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define mp make_pair
#define N 200
typedef pair<int,int> pii;
typedef long long ll;

int mask[N], tar[N];
int n;

void frente(int* at, int* resp){
	int tmp[N];
	rep(i, n)
		tmp[i] = at[mask[i]];
	rep(i, n)
		resp[i] = tmp[i];
}

void tras(int* at, int* resp){
	int tmp[N];
	rep(i, n)
		tmp[mask[i]] = at[i];
	rep(i, n)
		resp[i] = tmp[i];
}

bool cmp(int* p){
	rep(i, n) if(p[i] != tar[i]) return false;
	return true;
}


int k;
int at[N];
bool avalia(int x, bool foiBack){
	bool achou = false;
	
	if(x == k) achou = true;
	else {
		int delta = k - x;
		if((delta % 2) == 0){
			if(x!=1) achou = true;
			else{
				rep(i,n) at[i] = i;
				if(!foiBack)
					tras(at, at);
				else
					frente(at, at);
				if(!cmp(at)) achou = true;
			}
		}
	}
	
	return achou;
}

int main(){
	ios::sync_with_stdio(false);
	cin >> n >> k;
	rep(i, n) cin >> mask[i], --mask[i];
	rep(i, n) cin >> tar[i], --tar[i];
	rep(i,n) at[i] = i;
	
	if(cmp(at)){
		printf("NO\n");
		return 0;
	}
	
	int x = 0;
	fr(i, 1, k+1){
		++x;
		frente(at, at);
		if(cmp(at)) break;
	}
	bool achou = false;
	if(cmp(at))
		achou = avalia(x,false);
	
	x = 0;
	rep(i,n) at[i] = i;
	fr(i, 1, k+1){
		++x;
		tras(at,at);
		if(cmp(at)) break;
	}
	
	if(cmp(at))
		achou |= avalia(x, true);
	
	if(achou) printf("YES\n");
	else printf("NO\n");
	
}



