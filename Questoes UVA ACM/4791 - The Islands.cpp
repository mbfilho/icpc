#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
#define mp make_pair
#define X first
#define Y second
#define N 120
typedef pair<double,double> Ponto;
const int IDA = 1 << 20;

int b[2], n;
double pd[N][N];
int pred[N][N];
Ponto pts[N];
bool marc[N];

Ponto operator-(const Ponto& a, const Ponto& b){
	return Ponto(a.X - b.X, a.Y - b.Y);
}

double operator!(const Ponto& a){
	return sqrt(a.X * a.X + a.Y * a.Y);
}

double dist(int i, int j){
	return !(pts[i] - pts[j]);
}

void faz(){
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j ) pd[i][j] = 1e50;
	}
	memset(marc, false, sizeof marc);
	pd[0][0] = 0;
	
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			int k = max(i, j) + 1;
			if(i == n - 1 || j == n - 1) k = n - 1;
			
			if(k != b[1] && pd[k][j] > pd[i][j] + dist(i,k)){
				pd[k][j] = pd[i][j] + dist(i, k);
				pred[k][j] = IDA | i;
			}
			if(k != b[0] && pd[i][k] > pd[i][j] + dist(j, k)){
				pd[i][k] = pd[i][j] + dist(j, k);
				pred[i][k] = j;
			}
		}
	}
}

void print(int i, int j, vector<int>& resp){
	if(!i) resp.push_back(0);
	else{
		if(pred[i][j] & IDA){
			print(pred[i][j] xor IDA, j, resp);
			resp.push_back(i);
			marc[i] = true;
		}else if(j)
			print(i, pred[i][j], resp);
	}
}

int main(){
	int caso = 0;
	while(scanf("%d %d %d", &n, &b[0], &b[1]) != EOF && (n|b[0]|b[1])){
		for(int i = 0; i < n; ++i) scanf("%lf %lf", &pts[i].X, &pts[i].Y);
		vector<int> resp;
		faz();
		double custo = pd[n-1][n-1];
		
		swap(b[0], b[1]);
		faz();
		print(n-1,n-1,resp);
		
		printf( "Case %d: %.2lf\n", ++caso, pd[n-1][n-1]);
		if(pd[n-1][n-1] - custo > 1e-7 || resp[1] != 1){
			resp.clear();
			swap(b[0], b[1]);
			faz();
			print(n-1,n-1,resp);
		}
		
		printf("%d", 0);
		for(int i = 1; i < resp.size(); ++i)
			printf(" %d", resp[i]);
		marc[0] = false;
		
		for(int i = n - 1; ~i; --i){
			if(!marc[i]) printf(" %d", i);
		}
		printf( "\n" );
	}
}
