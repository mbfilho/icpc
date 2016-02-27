#include <cstdio>
#include <algorithm>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)


int in[3], out[3];

int main(){
	while(1){
		bool sai = true;
		rep(i, 3){
			scanf("%d", in + i);
			if(in[i]) sai = false;
		}
		if(sai) break;
		
		sort(in, in + 3);
		
		if(in[0] == in[2]){//set
			if(in[0] == 13) printf("*\n");
			else{
				printf("%d %d %d\n", in[0] + 1, in[0] + 1, in[0] + 1);
			}
		}else if(in[0] == in[1] || in[1] == in[2]){//par
			int ig = in[1], dif;
			
			if(in[0] == in[1])	dif = in[2];
			else dif = in[0];
			
			if(dif != 13 && ((dif + 1) != ig || dif + 2 <= 13)){
				if(dif + 1 == ig) ++dif;
				
				out[0] = out[1] = ig;
				out[2] = dif + 1;
				sort(out, out + 3);
				printf("%d %d %d\n", out[0], out[1], out[2]);
			}else{
				if(ig != 13){
					out[0] = out[1] = ig + 1;
					out[2] = 1;
					sort(out, out + 3);
					printf("%d %d %d\n", out[0], out[1], out[2]);
				}else{
					printf("1 1 1\n");
				}
			}
				
		}else{
			printf("1 1 2\n");
		}
		
	}	
}



