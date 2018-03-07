#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef long double ld;
const ll mod=1e9+7;

const int N=1<<18;

int st[2*N];

void setmax(int a, int b, int v){
	a+=N;
	b+=N;
	while (a<=b){
		if (a%2){
			st[a]=max(st[a], v);
			a++;
		}
		if (!(b%2)){
			st[b]=max(st[b], v);
			b--;
		}
		a/=2;
		b/=2;
	}
}

int getv(int i){
	int v=0;
	for (i+=N;i;i/=2){
		v=max(v, st[i]);
	}
	return v;
}

vector<int> co[N];
int u[N];
pair<int, int> iv[N];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,q;
	cin>>n>>q;
	for (int i=0;i<q;i++){
		int a,b,c;
		cin>>a>>b>>c;
		if (u[c]){
			iv[c].F=max(iv[c].F, a);
			iv[c].S=min(iv[c].S, b);
		}
		else{
			u[c]=1;
			iv[c]={a, b};
		}
		setmax(a, b, c);
	}
	for (int i=1;i<=n;i++){
		co[getv(i)].push_back(i);
	}
	ll v=1;
	ll fp=co[0].size();
	for (int i=1;i<=n;i++){
		if (u[i]){
			ll op=0;
			for (int p:co[i]){
				if (p>=iv[i].F&&p<=iv[i].S) op++;
			}
			v*=op;
			v%=mod;
			fp+=(int)co[i].size()-1;
		}
		else{
			v*=(ll)fp;
			v%=mod;
			fp--;
		}
	}
	cout<<v<<endl;
}
