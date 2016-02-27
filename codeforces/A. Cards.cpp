#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <iostream>
using namespace std;
typedef long long ll;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
#define ft first
#define sd second

int a, b;
ll quad(ll h){ return h * h;}

ll calc(int tot, int gps){
    ll qtd = tot / gps;
    ll resp = quad(qtd) * (gps - (tot % gps)) + quad(qtd + 1) * (tot % gps);
    return resp;
}

ll calc2(int tot, int gps){
    return  gps - 1 + quad(tot - gps + 1);
}

char out[1000000];

int main(){
    ios::sync_with_stdio(false);
    cin >> a >> b;
    ll ans = quad(a)-quad(b);
    int go = 1, gx = 1;

    fr(g, 1, a+1){
        if(g <= b && (calc2(a, g) - calc(b, g) > ans)) ans = calc2(a,g) - calc(b, g), go = gx = g;
        if(g+1<=b && (calc2(a, g) - calc(b, g+1) > ans)) ans = calc2(a, g) - calc(b, g+1), go = g, gx = g + 1;
    }
    // cout << go << ":" << calc2(a,go) << " " << gx << ":" << calc(b, gx) << endl;
//
    int prt = 0, qx = b / gx, incx = b % gx;
    while(a+b){
        for(int i = 0; i < qx && b; ++i) out[prt++] = 'x', --b;
        if(incx && b) out[prt++] = 'x', --b, --incx;
        if(go == 1){ --go; while(a > 0){out[prt++] = 'o', --a;} }
        else if(a > 0 && go) --go, out[prt++] = 'o', --a;
    }

    out[prt] = 0;
    cout << ans << endl;
    cout << out << endl;
}