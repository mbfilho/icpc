#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
#define mp make_pair
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define N 700

char ma[N][N];
char out[N][N];
int n, m, a, b;


int main(){
	while(cin >> n >> m && (n|m)){
		rep(i, N) rep(j, N) out[i][j] = 'Y';
		
		rep(i, n) cin >> ma[i];
		cin >> a >> b;
		a /= n, b /= m;
				
		int x = 0;
		rep(i, n){	
			rep(k, a){
				int y = 0;
				rep(j, m){
					rep(h, b){
						out[x][y++] = ma[i][j];
					}					
				}
				out[x][y] = 0;
				++x;
			}
			
		}
		rep(i, x) cout << out[i] << endl;
		cout << endl;
	}
}
