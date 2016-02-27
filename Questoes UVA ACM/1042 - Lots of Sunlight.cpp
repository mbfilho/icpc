#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define inc kjshdfkjsd
#define pb push_back
#define N 300
#define oo 10000000


int d[N], sum[N], w, h, n, size[N];

int soma(int lo, int hi){
	return sum[hi-1] - sum[lo-1];
}

double menores(int b, int ap){
	double resp = 0;
	
	fr(i, 1, b){
		if(size[i] >= ap){
			double height = (size[i] - ap + 1) * h, width = soma(i, b) + (b-i-1)*w;
			double teta = atan(height/width);
			resp = max(resp, teta);
		}
	}
	
	return resp;
}

double maiores(int b, int ap){
	double resp = 0;
	
	fr(i, b+1, n+1){
		if(size[i] >= ap){
			double height = (size[i]-ap+1)*h, width = soma(b, i) + (i-b-1)*w;
			double teta = atan(height/width);
			resp = max(resp, teta);
		}
	}
	return resp;
}

double ini = 5 * 3600 + 37 * 60, fim = 18 * 3600 + 17 * 60, PI = acos(-1);

double converte(double angle){
	return (angle / PI) * (fim-ini);
}

void print(double segs){
	int tempo = (int) segs;
	int h = tempo / 3600;
	tempo %= 3600;
	int m = tempo / 60;
	tempo %= 60;
	
	printf("%02d:%02d:%02d", h, m, tempo);
}

int main(){
	int caso = 0;
	
	while(scanf("%d", &n) == 1 && n){
		scanf("%d%d", &w, &h);
		
		sum[0] = 0;
		fr(i, 1, n+1){
			scanf("%d", size + i);
			if(i != n) scanf("%d", d + i);
			sum[i] = sum[i-1] + d[i];
		}
		printf("Apartment Complex: %d\n\n", ++caso);
		char q[100];
		while(scanf("%s", q) == 1 && strcmp(q, "0")){
			int x;
			sscanf(q, "%d", &x);
			printf("Apartment %d: ", x);
			int b = x % 100, ap = x / 100;
			if(b <= 0 || b > n || ap <= 0 || ap > size[b]) printf("Does not exist\n");
			else{
				double st = converte(menores(b, ap)), end = converte(maiores(b, ap));
				print(st + ini);
				printf(" - ");
				print(fim - end);
				printf("\n");
			}
			printf("\n");
		}
	}
}







