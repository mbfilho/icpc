#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <map>
using namespace std;
typedef pair<int,int> Ponto;
#define mp make_pair
#define X first
#define Y second

int n;
int soma;

int main(){
	soma = 0;
	scanf("%d", &n);
	
	for(int i = 0; i < n; ++i){
		int tmp;
		scanf("%d", &tmp);
		soma += tmp;
	}
	
	printf( "%lf\n", soma * (1.0/n));
}

