#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
int k[100];
bool mk[110000];

int main(){
	ios_base::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	rep(i, m) cin >> k[i];
	
	memset(mk, false, sizeof mk);
	mk[0] = true;
	
	fr(i, 1, n+1){
		rep(j, m){
			if(i - k[j] >= 0 && !mk[i - k[j]]){
				mk[i] = true;
				break;
			}
		}
	}

	
	if(mk[n]) cout << "1\n";
	else cout << "2\n";
}

