#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
#define N 700
#define B 37
#define Fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) Fr(i,0,n)
typedef unsigned long long hash;

int ran[N*N];
int height[N*N];
int novoVal[N*N];
char ma[N][N];
hash h[N][N];
hash str[N*N];
hash pot[N*N];
int n, m, prt;

int inc, len;
int array[N*N];
hash val[N*N];

bool cmp(const int & a, const int & b) {
	return (a+inc < len ? val[a+inc] : -1) < (b+inc < len ? val[b+inc] : -1);
}

void criarArraySufixo() {
	len = prt;
	for (int i = 0 ; i < len ; i++) {
		array[i] = i;
		val[i] = str[i];
	}
	
	inc = 0;
	sort(array, array+len, cmp);
	for (inc = 1 ; (inc>>1) < len ; inc<<=1) {
		int i,j;
		bool mudou = false;
		for (i = 0 ; i < len-1 ; i++) { // se tiver um cara no ultimo intervalo, ele é o ultimo já
			j = i+1;
			while (j < len && val[array[i]] == val[array[j]]) j++;
			if (j > i+1) {
				mudou = true;
				sort(array+i, array+j, cmp);
			}
			i = j-1;
		}
		if (!mudou) break;
		novoVal[array[0]] = 0;
		for (int i = 1 ; i < len ; i++) {
			novoVal[array[i]] = novoVal[array[i-1]];
			if (val[array[i]] > val[array[i-1]] || cmp(array[i-1],array[i])) novoVal[array[i]]++;
		}
		for (int i = 0 ; i < len ; i++) val[i] = novoVal[i];
	}
}

void criarArrayHeight() {
	for (int i = 0 ; i < len ; i++) ran[array[i]] = i;
	int h = 0;
	for (int i = 0 ; i < len ; i++) {
		if (ran[i] > 0) {
			int j = array[ran[i]-1];
			while (i+h < len && j+h < len && str[i+h] == str[j+h]) h++;
			height[ran[i]] = h;
			if (h > 0) h--;
		}
	}
}

int aux[N*N];
int size[N*N];

int calcSubstringDistintas(){
//	printf( "Array:");
//	rep(i, prt){
//		printf( "%d [%d] ", array[i], height[i]);
//	}
//	printf("\n");
	int total = 0;
	if(~aux[array[0]]) total = 1 + m - size[array[0]];
//	printf( "TOtl %d\n", total);
	for (int i = 1 ; i < prt; i++) {
		if(~aux[array[i]]){
			total += max(1 + (m - size[array[i]])-height[i] , 0);
//			printf( "%d %d %d\n", size[array[i]],aux[array[i]],height[i]);
		}
	}
	
	return total;
}



hash get(int col, int a, int b){
	hash ant = 0;
	if(a)
		ant = h[col][a-1];
	
	hash ha = h[col][b] - ant * pot[b-a+1];
	
	return ha;
}

int main(){
	int t;
	scanf("%d", &t);
	pot[0] = 1;
	Fr(i, 1, N*N)
		pot[i] = B * pot[i-1];
		
	rep(cas, t){
		scanf("%d%d", &n, &m);
		rep(i,n)
			scanf("%s", ma[i]);
		
		rep(j, m){
			rep(i, n){
				hash ant = 0;
				if(i)
					ant = h[j][i-1];
					
				h[j][i] = ant * B + ma[i][j] - 'A' + 1; 
			}
		}
		
		hash sep = 0;
		int resp = 0;
		rep(tam, n){
			sep = sep * B + '$';
			prt = 0;
			for(int i = 0; i + tam < n; ++i){
				for(int j = 0; j < m; ++j){
					size[prt] = j+1;
					str[prt++] = get(j, i, i + tam);
					aux[prt-1] = j;
				}
				str[prt++] = sep;
				aux[prt-1] = -1;
			}
			criarArraySufixo();
			criarArrayHeight();
			int tmp = calcSubstringDistintas();;
			resp += tmp;
			
//			printf( "Tam %d [%d]\n", tam, tmp);
//			rep(i, prt){
//				printf("%llu ", str[i]);
//			}
//			printf("\n");
		}
		
		printf( "Case #%d: %d\n", cas + 1, resp);
	}
}

