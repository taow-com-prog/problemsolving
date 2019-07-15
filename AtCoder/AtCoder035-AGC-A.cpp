#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
 
#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int inf_int = 1e9 + 100;
const ll inf_ll = 1e18;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef long double dbl;
#define pb push_back
const double pi = 3.1415926535898;
#define dout if(debug) cout
#define fi first
#define se second
#define sp setprecision
#define sz(a) (int(a.size()))
#define all(a) a.begin(),a.end()
bool debug = 0;
const int MAXN = 4100 + 100;
const int LOG = 22;
const int mod = 1e9 + 7;
const int MX = 1e6 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;
 
 
void solve() {
    int n;
    cin >> n;
    map<int,int> mp;
    int last = -1;
    for(int i=1;i<=n;++i){
        int x;
        cin >> x;
        last = x;
        mp[x]++;
    }
    if(mp.count(0)==1 && mp[0] == n){
        cout <<"Yes";
        return;
    }
    if(sz(mp) != 3){
        if(sz(mp) == 2 && n%3==0 && mp[0] == n/3){
            cout <<"Yes";
            return;
        }
        
        cout <<"No";
        return;
    }
    int val = mp[last];
    vector<int> v;
    for(auto x:mp){
        if(x.se != val){
            cout <<"No";
            return;
        }
        v.pb(x.fi);
    }
    if(n%3 != 0){
        cout <<"No";
        return;
    }
 
    sort(all(v));
    for(int val:v){
        dout << val<<" ";
    }
    dout << endl;
 
 
    do{
        bool flag = true;
        for(int i = 0;i < 3;++i){
            if((v[i] ^ v[(i+2)%3]) != (v[(i+1)%3])){
                flag = false;
                break;
            }
        }
        if(flag){
            cout <<"Yes";
            return;
        }
    }while(next_permutation(all(v)));
    cout <<"No";
    return;
}
 
signed main() {
#ifdef zxc
    debug = 1;
    freopen("../input.txt", "r", stdin);
  //  freopen("../output.txt", "w", stdout);
#else
 
#endif //zxc
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.setf(ios::fixed);
    cout.precision(20);
 
    int t = 1;
    while (t--)
        solve();
 
    if (debug)
        cerr << endl << "time : " << (1.0 * clock() / CLOCKS_PER_SEC) << endl;
}