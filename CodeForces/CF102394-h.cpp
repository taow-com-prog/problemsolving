//
// Created by Ильдар Ялалов on 14.01.2020.
//
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <random>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int inf_int = 1e9 + 100;
const ll inf_ll = 1e18;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef double dbl;
#define pb push_back
#define eb emplace_back
const double pi = 3.1415926535898;
#define dout if(debug) cout
#define fi first
#define se second
#define sp setprecision
#define sz(a) (int(a.size()))
#define mp make_pair
#define all(a) a.begin(),a.end()


template<class T1, class T2>
std::ostream &operator<<(std::ostream &out, const std::pair<T1, T2> &rhs) {
    out << "( " << rhs.first << " , " << rhs.second << " )";
    return out;
}

//<editor-fold desc="tourist code">

template<typename A, typename B>
string to_string(pair<A, B> p);

template<typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template<typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(const string &s) {
    return '"' + s + '"';
}

string to_string(const char *s) {
    return to_string((string) s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < static_cast<int>(v.size()); i++) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v[i]);
    }
    res += "}";
    return res;
}

template<size_t N>
string to_string(bitset<N> v) {
    string res = "";
    for (size_t i = 0; i < N; i++) {
        res += static_cast<char>('0' + v[i]);
    }
    return res;
}

template<typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

template<typename A>
string to_string(vector<vector<A>> v) {
    bool first = true;
    string res = "\n{";
    for (const auto &x : v) {
        if (!first) {
            res += ",\n ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}\n";
    return res;
}

template<typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template<typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template<typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " +
           to_string(get<3>(p)) + ")";
}

void debug_out() { cerr << endl; }

template<typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}
//</editor-fold>

//<editor-fold desc="ifdef">
#ifdef zxc
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif
//</editor-fold>

bool debug = 0;
const int MAXN = 200000 + 100;
const int LOG = 21;
const int mod = 1e8 + 7;
const int MX = (1e7 + 100);
typedef long long li;


int c[MAXN], f[MAXN], w[MAXN];
ll res[MAXN];
ll val[MAXN];

priority_queue<pair<ll, int> > q;

inline void upd(int v, ll new_val) {
    if (val[v] > new_val) {
        val[v] = new_val;
        q.push({-val[v] - c[v], v});
    }
}

struct Graph1 {
    int n;
    vector<int> g[MAXN];

    inline void add_edge(int a, int b) {
        g[a].pb(b);
        g[b].pb(a);
    }

    int spec[64];
    int n_spec = 0;
    vector<int> order[64];
    vector<int> dis[64];
    int pos[64];

    inline void add_spec(int v) {
        n_spec++;
        spec[n_spec] = v;
    }

    void clear() {
        memset(pos, 0, sizeof pos);
    }

    void bfs() {
        for (int st = 1; st <= n_spec; ++st) {
            int v0 = spec[st];
            order[st].pb(v0);
            dis[st].resize(n + 1, inf_int);
            dis[st][v0] = 0;
            int top = 0;
            while (top < sz(order[st])) {
                int v = order[st][top++];
                for (int to : g[v]) {
                    if (dis[st][to] > dis[st][v] + 1) {
                        dis[st][to] = dis[st][v] + 1;
                        order[st].push_back(to);
                    }
                }
            }
            debug(st, v0, dis[st], order[st]);
        }
    }

    void push_val(int v) {
        ll cost = val[v] + c[v];
        for (int j = 1; j <= n_spec; ++j) {
            int d = f[v] - dis[j][v];
            debug("!!" , v, j, d);
            for (; pos[j] < sz(order[j]); ++pos[j]) {
                int to = order[j][pos[j]];
                if (dis[j][to] > d) {
                    break;
                }
                upd(to, cost);
            }
        }
    }
} graph1;

struct Graph2 {
    int n;
    vector<int> g[MAXN];

    inline void add_edge(int a, int b) {
        g[a].pb(b);
        g[b].pb(a);
    }

    int lvl[MAXN];
    int parent[MAXN];

    int dfs(int v, int p, int &center, int size) {
        int sum = 1;
        for (int to:g[v]) {
            if (lvl[to])
                continue;
            if (to == p)
                continue;
            sum += dfs(to, v, center, size);
        }
        if (center == -1 && (p == -1 || 2 * sum >= size)) {
            center = v;
        }
        return sum;
    }

    vector<int> order[MAXN];
    vector<int> dis[MAXN];

    int dis_par[LOG][MAXN];
    int pos[MAXN];

    void clear() {
        memset(pos, 0, sizeof pos);
    }

    int used[MAXN];
    int timer;
    void add_dfs(int v, int p, int d, vector<int> &order, vector<int> &dis) {
        ++timer;
        order.pb(v);
        dis.pb(0);
        int top = 0;
        used[v] = timer;
        while(top < sz(order)){
            int d = dis[top];
            int v = order[top++];
            for(int to : g[v]){
                if(lvl[to])
                    continue;
                if(used[to]!=timer){
                    used[to] = timer;
                    order.pb(to);
                    dis.pb(d+1);
                }
            }
        }
    }

    void build(int start, int size, int level, int par) {
        int center = -1;
        dfs(start, -1, center, size);
        lvl[center] = level;
        parent[center] = par;

        add_dfs(center, -1, 0, order[center], dis[center]);

        debug(center,lvl[center], order[center], dis[center]);
        for (int i = 0; i < sz(order[center]); ++i) {
            int to = order[center][i];
            int d = dis[center][i];
            dis_par[level][to] = d;
        }
        for (int to: g[center]) {
            if (lvl[to])
                continue;
            build(to, size / 2, level + 1, center);
        }
    }

    void push_val(int v) {
        ll cost = val[v] + c[v];
        int p = v;
        while (p) {
            int level = lvl[p];
            int d = f[v] - dis_par[level][v];

            debug(v, p, d);

            for (; pos[p] < sz(order[p]); ++pos[p]) {
                int to = order[p][pos[p]];
                int len = dis[p][pos[p]];
                debug("push2" , to,len);
                if (len > d)
                    break;
                upd(to, cost);
            }
            p = parent[p];
        }
    }
} graph2;


namespace DSU {
    int parent[MAXN];

    mt19937 mt(228);

    void init(int n) {
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }

    int get_parent(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = get_parent(parent[v]);
    }

    bool union_set(int a, int b) {
        a = get_parent(a);
        b = get_parent(b);
        if (a != b) {
            if (mt() & 1)
                swap(a, b);
            parent[a] = b;
            return true;
        }
        return false;
    }
};


void calc(int n) {
    for (int i = 1; i <= n; ++i) {
        val[i] = inf_ll;
    }
    graph1.clear();
    graph2.clear();

    val[1] = 0;
    q.push({val[1], 1});

    while (!q.empty()) {
        int v = q.top().se;
        q.pop();
        graph1.push_val(v);
        graph2.push_val(v);
    }

    for (int i = 1; i <= n; ++i) {
        res[i] = min(res[i], val[i]);
    }
}

void solve() {
    int n, m, t;
    cin >> n >> m >> t;
    graph1.n = graph2.n = n;
    DSU::init(n);
    for (int i = 1; i <= n; ++i) {
        cin >> f[i] >> c[i] >> w[i];
    }
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        graph1.add_edge(a, b);
        if (DSU::union_set(a, b)) {
            graph2.add_edge(a, b);
        } else {
            graph1.add_spec(a);
        }
    }
    for (int i = 1; i <= n; ++i) {
        res[i] = inf_ll;
    }
    graph1.bfs();
    graph2.build(1, n, 1, 0);

    calc(n);
    for (int i = 1; i <= n; ++i) {
        c[i] = c[i] + (t - 1) * w[i];
    }
    calc(n);
    for (int i = 1; i <= n; ++i) {
        cout << res[i] << "\n";
    }
}

signed main() {
#ifdef zxc
    freopen("../input.txt", "r", stdin);
    // freopen("../output.txt", "w", stdout);
#else
#endif //zxc
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.setf(ios::fixed);
    cout.precision(15);

    int t = 1;
    while (t--)
        solve();

    debug(1.0 * clock() / CLOCKS_PER_SEC);
}