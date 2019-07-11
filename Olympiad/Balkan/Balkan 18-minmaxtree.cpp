/*
    Using binary lifting, pushed value to edges.
    Then build matching for edges and values, run DINIC. 
*/

//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
 
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
const int MAXN = 2e5 + 100;
const int LOG = 22;
const int mod = 1e9 + 7;
const int MX = 1e6 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;
 
vector<int> g[MAXN];
int up[MAXN][LOG];
int mn[MAXN][LOG];
int mx[MAXN][LOG];
int h[MAXN];
 
void dfs(int v, int p) {
    up[v][0] = p;
    for (int i = 1; i < LOG; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int to:g[v]) {
        if (to == p)
            continue;
        h[to] = h[v] + 1;
        dfs(to, v);
    }
}
 
int lca(int a, int b) {
    if (h[a] > h[b])
        swap(a, b);
    int dif = h[b] - h[a];
    for (int i = 0; i < LOG; ++i) {
        if (dif & (1 << i))
            b = up[b][i];
    }
    assert(h[a] == h[b]);
    if (a == b)
        return a;
    for (int i = LOG - 1; i >= 0; --i) {
        if (up[a][i] != up[b][i]) {
            a = up[a][i];
            b = up[b][i];
        }
    }
    return up[a][0];
 
}
 
void set_mn(int a, int lc, int val) {
    int dif = h[a] - h[lc];
    for (int i = 0; i < LOG; ++i) {
        if (dif & (1 << i)) {
            mn[a][i] = max(mn[a][i], val);
            a = up[a][i];
        }
    }
}
 
void set_mx(int a, int lc, int val) {
    int dif = h[a] - h[lc];
    for (int i = 0; i < LOG; ++i) {
        if (dif & (1 << i)) {
            mx[a][i] = min(mx[a][i], val);
            a = up[a][i];
        }
    }
}
 
 
struct edge {
    int a, b, c, flow;
};
 
struct Flow {
    vector<int> g[MAXN];
    vector<edge> e;
 
    inline int add_edge(int a, int b, int c) {
        edge e1 = {a, b, c, 0};
        edge e2 = {b, a, 0, 0};
        int id = sz(e);
        g[a].pb(id);
        e.pb(e1);
        g[b].pb(id + 1);
        e.pb(e2);
        return id;
    }
 
    int s, t, n;
    int ptr[MAXN], dis[MAXN], q[MAXN];
 
    void init(int S, int T, int N) {
        s = S;
        t = T;
        n = N;
    }
 
 
    bool bfs() {
        fill(dis, dis + n, inf_int);
        dis[s] = 0;
        int qh = 0, qt = 1;
        q[0] = s;
        while (qh < qt) {
            int v = q[qh++];
            for (int id:g[v]) {
                edge &r = e[id];
                int to = r.b;
                if (r.c > r.flow && dis[to] > dis[v] + 1) {
                    dis[to] = dis[v] + 1;
                    q[qt++] = to;
                }
            }
        }
        return dis[t] != inf_int;
    }
 
 
    int dfs(int v, int flow) {
        if (v == t)
            return flow;
        for (; ptr[v] < sz(g[v]); ++ptr[v]) {
            int id = g[v][ptr[v]];
            edge &r = e[id];
            if (r.c > r.flow && dis[r.b] == dis[v] + 1) {
                int pushed = dfs(r.b, min(flow, r.c - r.flow));
                if (pushed) {
                    e[id].flow += pushed;
                    e[id ^ 1].flow -= pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }
 
    void delete_all() {
        e.clear();
        for (int i = 0; i < n; ++i) {
            g[i].clear();
        }
    }
 
    void clear() {
        int m = sz(e);
        for (int i = 0; i < m; ++i) {
            e[i].flow = 0;
        }
    }
 
 
    int flow() {
        int res = 0;
        while (bfs()) {
            fill(ptr, ptr + n, 0);
            while (int pushed = dfs(s, inf_int)) {
                res += pushed;
            }
        }
        return res;
    }
 
} flow;
 
int id[MAXN][2];
 
void solve() {
    int n;
    cin >> n;
    for (int i = 2; i <= n; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].pb(y);
        g[y].pb(x);
    }
    dfs(1, 1);
    for (int i = 1; i <= n; ++i) {
        for (int e = 0; e < LOG; ++e) {
            mn[i][e] = -inf_int;
            mx[i][e] = inf_int;
        }
    }
 
    int k;
    cin >> k;
    map<int, int> mp;
    for (int i = 1; i <= k; ++i) {
        char t;
        cin >> t;
        int a, b, c;
        cin >> a >> b >> c;
        int lc = lca(a, b);
        if (t == 'M') {
            set_mx(a, lc, c);
            set_mx(b, lc, c);
        } else {
            set_mn(a, lc, c);
            set_mn(b, lc, c);
        }
        assert(mp.count(c) == 0);
        mp[c] = i;
    }
 
 
    for (int e = LOG - 1; e >= 1; --e) {
        for (int i = 1; i <= n; ++i) {
            mx[i][e - 1] = min(mx[i][e - 1], mx[i][e]);
            mx[up[i][e - 1]][e - 1] = min(mx[up[i][e - 1]][e - 1], mx[i][e]);
        }
    }
 
    for (int e = LOG - 1; e >= 1; --e) {
        for (int i = 1; i <= n; ++i) {
            mn[i][e - 1] = max(mn[i][e - 1], mn[i][e]);
            mn[up[i][e - 1]][e - 1] = max(mn[up[i][e - 1]][e - 1], mn[i][e]);
        }
    }
 
    int s = 0, t = n + k + 2;
    for (int i = 1; i <= k; ++i) {
        flow.add_edge(s, i, 1);
    }
    for (int i = 2; i <= n; ++i) {
        if (mx[i][0] != inf_int) {
            int v = mp[mx[i][0]];
            id[i][0] = flow.add_edge(v, k + i, 1);
        }
        if (mn[i][0] != -inf_int) {
            int v = mp[mn[i][0]];
            id[i][1] = flow.add_edge(v, k + i, 1);
        }
        dout << i <<" "<<id[i][0]<<" "<<id[i][1] << endl;
        flow.add_edge(k + i, t, 1);
    }
    flow.init(s,t,t+1);
    int val = flow.flow();
    dout <<"val "<<val<<endl;
 
    for(int i=2;i<=n;++i){
        int j = id[i][0];
        int val = -1;
        if(j > 0 && flow.e[j].flow == 1){
            dout <<"here "<<"mx"<<" "<<mx[i][0]<<endl;
            val = mx[i][0];
        } else{
            val = mn[i][0];
        }
 
        cout << i <<" "<<up[i][0]<<" "<<val<<"\n";
    }
 
}
 
signed main() {
#ifdef zxc
    debug = 1;
    freopen("../input.txt", "r", stdin);
    //freopen("../output.txt", "w", stdout);
#else
    //freopen("roboherd.in", "r", stdin);
    //freopen("roboherd.out", "w", stdout);
 
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