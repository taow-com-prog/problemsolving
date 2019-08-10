
/*
    Like in editorial.
*/

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int inf_int = 1e9 + 100;
const ll inf_ll = 2e18;
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
const int MAXN = 2e5 + 100;
const int LOG = 25;
const int mod = 998244353;
const int MX = 1e6 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;

vector<int> g[MAXN];


int dfs(int v, int p) {
    vector<int> vals;
    for (int to:g[v]) {
        if (to == p)
            continue;
        int res = dfs(to, v);
        vals.pb(res);
    }
    if (sz(vals) == 0) {
        return 1;
    } else if (sz(vals) == 1) {
        return vals[0] + 1;
    } else {
        int val = 0;
        for (int v:vals) {
            val ^= v;
        }
        return val + 1;
    }
}

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    int res = dfs(1,1);
    if(res == 1){
        cout <<"Bob";
    } else{
        cout <<"Alice";
    }
}

signed main() {
#ifdef zxc
    debug = 1;
    freopen("../input.txt", "r", stdin);
    //freopen("../output.txt", "w", stdout);
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