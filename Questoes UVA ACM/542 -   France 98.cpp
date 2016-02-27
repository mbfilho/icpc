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
double ma[20][20];
string reve[20];
int n = 16;
double p[20];


double win(int s, int t, int ind){
	int aux = ind - s, tam = t - s + 1;
	double tmp = 0;

	if(aux >= tam / 2){
		fr(i, s, s+tam/2){
			tmp += p[i] * ma[ind][i];
		}
	}else{
		fr(i, s+tam/2, t+1){
			tmp += p[i] * ma[ind][i];
		}
	}
	return tmp;
}

int main(){
	rep(i, 16) cin >> reve[i];
	
	rep(i, n) rep(j, n) cin >> ma[i][j], ma[i][j] /= 100.0, p[i] = 1.0;
	
	int tam = 2;
	while(tam <= 16){
		double tmp[20];
		rep(j, n) tmp[j] = p[j];
		for(int i = 0; i + tam <= n; i += tam){
			fr(j, i, i + tam){
				tmp[j] *= win(i, i + tam-1, j);
			}
			
		}
		rep(j, n) p[j] = tmp[j];
		tam *= 2;
	}
	
	rep(i, n)
		printf("%-10s p=%.2lf%%\n", reve[i].c_str(), 100.0*p[i]);
}


