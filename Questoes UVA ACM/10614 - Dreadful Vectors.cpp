#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
typedef long long ll;
int tam;
char buf[1000000];

struct no{
	int vetor;
	ll a[3];
	ll value;
	
	no(){
		value = vetor = -1;
		rep(i,3) a[i] = -1;
	}
	
	no operator+(const no& o) const{
		if(vetor == -1 || o.vetor == -1) return no();
		
		if(vetor == 1 && o.vetor == 1){
			no vet;
			vet.vetor = 1;
			rep(i,3) vet.a[i] = a[i] + o.a[i];
			
			return vet;
		}else if(!vetor && !o.vetor){
			no vet;
			vet.vetor = 0;
			vet.value = value + o.value;
			return vet;
		}
		
		return no();
	}
	
	no operator-(const no& o) const{
		if(vetor == -1 || o.vetor == -1) return no();
		
		if(vetor == 1 && o.vetor == 1){
			no vet;
			vet.vetor = 1;
			rep(i,3) vet.a[i] = a[i] - o.a[i];
			
			return vet;
		}else if(!vetor && !o.vetor){
			no vet;
			vet.vetor = 0;
			vet.value = value - o.value;
			return vet;
		}
		
		return no();
	}
	
	no operator*(const no& o) const{
		if(vetor == -1 || o.vetor == -1) return no();
		if(vetor == 1 && o.vetor == 1){
			no vet;
			vet.vetor = 0;
			vet.value = 0;
			rep(i,3) vet.value += a[i] * o.a[i];
			return vet;
		}else if(!vetor && !o.vetor){
			no vet;
			vet.vetor = 0;
			vet.value = o.value * value;
			return vet;
		}else if(!vetor && o.vetor == 1){
			no vet;
			vet.vetor = 1;
			rep(i, 3) vet.a[i] = o.a[i] * value;
			return vet;
		}else if(vetor && !o.vetor){
			return o * (*this);
		}
		
		return no();
	}
	
	no operator^(const no& o) const{
		if(vetor == -1 || o.vetor == -1) return no();
		if(vetor == 1 && o.vetor == 1){
			no vet;
			vet.vetor = 1;
			vet.a[0] = a[1] * o.a[2] - a[2] * o.a[1];
			vet.a[1] = a[2] * o.a[0] - o.a[2] * a[0];
			vet.a[2] = a[0] * o.a[1] - o.a[0] * a[1];
			return vet;
		}
		
		return no();
	}
	
	bool operator==(const no& o)const{
		return vetor == o.vetor && o.vetor == -1;
	}
	
};

no nill;
no readVector(int ini, int fim);

no read(int ini, int fim){
	while(ini <= fim && buf[ini] == ' ') ++ini;
	while(ini <= fim && buf[fim] == ' ') --fim;
	if(ini > fim) return nill;
	
	bool tdNumber = true;
	ll num = 0;
	
	fr(i, ini, fim+1){
		if(buf[i] < '0' || buf[i] > '9'){
			tdNumber = false;
			break;
		}
		num = num * 10 + buf[i] - '0';
	}
	if(tdNumber){
		no vet;
		vet.vetor = 0;
		vet.value = num;
		return vet;
	}
	
	int c[] = {0,0};
	int op = -1, prt;
	
	for(int i = fim; i >= ini; --i){
//	fr(i, ini, fim+1){
		if(!c[0] && !c[1]){
			if(buf[i] == '+' || buf[i] == '-'){
				if(op == -1 || op == '*' || op == 'x'){
					op = buf[i];
					prt = i;
				}
			}else if(buf[i] == '*' || buf[i] == 'x'){
				if(op == -1){
					op = buf[i];
					prt = i;
				}
			}
		}
		
		if(buf[i] == '(') ++c[0];
		else if(buf[i] == ')') --c[0];
		else if(buf[i] == '[') ++c[1];
		else if(buf[i] == ']') -- c[1];
		
	}
	if(c[0] < 0 || c[1] < 0) return nill;
	
	if(~op){
//		printf( "> %c\n", op);
			
//		printf( "%d %d [%c %c] %d\n", ini, prt - 1, buf[ini], buf[prt-1], 3);
//		printf( "%d %d [%c %c] %d\n", prt+1, fim, buf[prt+1], buf[fim], 3);
	}
	if(~op){
		no args[] = {read(ini, prt-1), read(prt+1, fim)};		
		if(args[0] == nill || args[1] == nill) return nill;
//		printf( "%d %d [%c %c] %d\n", ini, prt - 1, buf[ini], buf[prt-1], args[0].vetor);
//		printf( "%d %d [%c %c] %d\n", prt+1, fim, buf[prt+1], buf[fim], args[1].vetor);
		if(op == '+')
			return args[0] + args[1];
		else if(op == '-'){
			no h = args[0] - args[1];
//			printf("#> %d %d %d\n", args[0].value, args[1].value, h.value);
			return h;
		}else if(op == '*'){
			no h = args[0] * args[1];
//			printf( "* %lld %lld %lld | %lld %lld %lld\n", args[0].a[0], args[0].a[1], args[0].a[2],
//				args[1].a[0], args[1].a[1], args[1].a[2]);
//			printf("*> %d\n", h.value);
			return h;
		}else if(op == 'x')
			no h = args[0] ^ args[1];
			return args[0] ^ args[1];

		return nill;
	}else{
		if(buf[ini] == '(' && buf[fim] == ')')
			return read(ini+1, fim-1);
		if(buf[ini] == '[' && buf[fim] == ']')
			return readVector(ini+1, fim-1);

		return nill;
	}
}

no readVector(int ini, int fim){
	if(ini == fim) return no();
	int i = ini;
	no vet;
	vet.vetor = 1;
	int v = 0;
	
	rep(k, 2){
		int c[] = {0,0};
		int vir = -1;
		
		while(i <= fim){
			if(buf[i] == '(') ++c[0];
			else if(buf[i] == ')') --c[0];
			else if(buf[i] == '[') ++c[1];
			else if(buf[i] == ']') --c[1];
			else if(!c[0] && !c[1] && buf[i] == ','){
				vir = i;
				break;
			}
			++i;
		}
		
		if(~vir){
			no tmp = read(ini, i-1);
			if(tmp.vetor) return no();
			vet.a[v++] = tmp.value;
			ini = i = i + 1;
		}else{
			return no();
		}
	}
	no tmp = read(ini, fim);
	if(tmp.vetor) return no();
	vet.a[2] = tmp.value;
	return vet;
}


char tmp[1000000];

int main(){
	while(gets(buf) && strcmp(buf, "#")){
		tam = strlen(buf);
//		printf("> %s\n", buf);
		no val = read(0, tam-1);
		if(val.vetor == 0)
			printf("%lld\n", val.value);
		else if(val.vetor == 1)
			printf("[%lld,%lld,%lld]\n", val.a[0], val.a[1], val.a[2]);
		else
			printf("Bang!\n");
	}
}




