/*
	parallel binary search and euler tour on tree
*/

#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef unsigned long long ull;
int inf_int=1e9;
ll inf_ll=1e18;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define pb push_back
const double pi=3.1415926535898;
#define dout if(debug) cout
#define fi first
#define se second
#define sp setprecision
#define sz size()
 
bool debug=0;
const int MAXN=5e5+100000;
int mod=1e9+9;
 
int n,m;
vector<int> g[MAXN];
int tin[MAXN],tout[MAXN],timer;
ll h[MAXN];
void dfs(int v,int p=0)
{
    assert(tin[v]==0);
    tin[v]=++timer;
    for(int to:g[v])
    {
        h[to]=h[v]+1;
        dfs(to,v);
    }
    tout[v]=timer;
}
vector<int> owning[MAXN];
ll need[MAXN];
struct FenTree
{
    ll t[MAXN];
    int n;
    void init(int n)
    {
        this->n=n;
        for(int i=0;i<=n;++i)
        {
            t[i]=0;
        }
    }
    void add(int l,int r,ll val)
    {
        for(;l<n;l=(l|(l+1)))
            t[l]+=val;
        ++r;
        for(;r<n;r=(r|(r+1)))
            t[r]-=val;
    }
    ll get(int r)
    {
        ll res=0;
        for(;r>=0;r=(r&(r+1))-1)
            res+=t[r];
        return res;
    }
 
};
ll F[MAXN],X[MAXN],D[MAXN];
 
FenTree t1,t2,t3;
int cur;
int ans[MAXN];
void par_bin(int L,int R,vector<int> owners)
{
    if(L>R || owners.empty())
        return;
    int mid=(L+R)>>1;
    while(cur<mid)
    {
        ++cur;
        int v=F[cur];
        t1.add(tin[v],tout[v],X[cur]);
        t2.add(tin[v],tout[v],D[cur]);
        t3.add(tin[v],tout[v],D[cur]*h[v]);
    }
    while(cur>mid)
    {
        int v=F[cur];
        t1.add(tin[v],tout[v],-X[cur]);
        t2.add(tin[v],tout[v],-D[cur]);
        t3.add(tin[v],tout[v],-D[cur]*h[v]);
        --cur;
    }
    vector<int> left,right;
    for(int man:owners)
    {
        ll sum=0;
        for(int v:owning[man])
        {
            int to=tin[v];
            sum+=t1.get(to);
            sum+=t2.get(to)*h[v]-t3.get(to);
            if(sum>=need[man])
                break;
        }
        if(sum>=need[man])
        {
            ans[man]=mid;
            left.pb(man);
        }
        else
        {
            right.pb(man);
        }
    }
 
    owners.clear();
    par_bin(L,mid-1,left);
    par_bin(mid+1,R,right);
}
void solve()
{
    cin >> n>> m;
    for(int i=2;i<=n;++i)
    {
        int p;
        cin >> p;
        g[p].pb(i);
    }
    for(int i=1;i<=n;++i)
    {
        int x;
        cin >> x;
        owning[x].pb(i);
    }
    h[1]=1;
    dfs(1);
    for(int i=1;i<=m;++i)
    {
        cin >> need[i];
    }
    int q;
    cin >> q;
    for(int i=1;i<=q;++i)
    {
        cin >> F[i] >> X[i]>> D[i];
    }
    t1.init(n+10);
    t2.init(n+10);
    t3.init(n+10);
    vector<int> all;
    for(int i=1;i<=m;++i)
    {
        ans[i]=q+10;
        all.pb(i);
    }
    par_bin(1,q,all);
 
    for(int i=1;i<=m;++i)
    {
        if(ans[i]==q+10)
        {
            cout << "rekt\n";
        }
        else
        {
            cout << ans[i]<<"\n";
        }
    }
}
 
 
 
#define FILE "key"
int main()
{
        #ifdef zxc
            freopen("input.txt","r",stdin);
         //   freopen("output.txt","w",stdout);
        #endif // zxc
 
    //    freopen(FILE".in","r",stdin);
   //   freopen(FILE".out","w",stdout);
 
       if(!debug)
       {
            ios_base::sync_with_stdio(0);
            cin.tie(0);
            cout.tie(0);
       }
 
        int t=1;
         while(t--)
            solve();
        return 0;
}