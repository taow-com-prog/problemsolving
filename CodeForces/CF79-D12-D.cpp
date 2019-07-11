/*
	AS in editorial.
*/

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
const int MAXN = 1e4 + 100;
const int LOG = 25;
const int mod = 1e9 + 7;
const int MX = 5e5 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;
 
bool used[MAXN];
 
int a[MAXN];
 
int dis[MAXN];
int d[50][50];
int n, k, l;
 
void bfs(int st) {
    fill(dis, dis + MAXN, inf_int);
    dis[st] = 0;
    queue<int> q;
    q.push(st);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
 
        for (int i = 1; i <= l; ++i) {
            int to = v + a[i];
            if (to >= 0 && to <= n)
                if (dis[to] > dis[v] + 1) {
                    dis[to] = dis[v] + 1;
                    q.push(to);
                }
        }
        for (int i = 1; i <= l; ++i) {
            int to = v - a[i];
            if (to >= 0 && to <= n)
                if (dis[to] > dis[v] + 1) {
                    dis[to] = dis[v] + 1;
                    q.push(to);
                }
        }
 
    }
}
 
int dp[1 << 20];
 
void solve() {
 
    cin >> n >> k >> l;
    for (int i = 1; i <= k; ++i) {
        int x;
        cin >> x;
        used[x] = 1;
    }
    vector<int> spec;
    for (int i = 0; i <= n; ++i) {
        if (used[i] != used[i + 1])
            spec.pb(i);
    }
    for (int i = 1; i <= l; ++i) {
        cin >> a[i];
    }
 
 
    k = sz(spec);
    dout <<"K "<<k<<endl;
 
    for (int i = 0; i < k; ++i) {
        bfs(spec[i]);
        for (int j = 0; j < k; ++j) {
            d[i][j] = dis[spec[j]];
        }
        assert(d[i][i] == 0);
    }
    for (int i = 0; i < (1 << k); ++i)
        dp[i] = inf_int;
    dp[0] = 0;
    for (int mask = 0; mask < (1 << k); ++mask) {
        for (int v = 0; v < k; ++v) {
            if (!(mask & (1 << v)))
                for (int to = 0; to < k; ++to) {
                    if(v == to)
                        continue;
                    if (!(mask & (1 << to))) {
                        dp[mask|(1<<v)|(1<<to)] = min(dp[mask|(1<<v)|(1<<to)],dp[mask] + d[v][to]);
                    }
                }
        }
    }
    int all = (1<<k) -1;
    if(dp[all] >= inf_int) {
        cout << -1;
        return;
    }
    cout << dp[all];
 
 
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