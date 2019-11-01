//second win if full matching exists
// otherwise first win and he should start at vertex which didn't inside all maximal matching. Find max matching, then delete vertex v, 
// from maximal matching u-v, run finding augmenting part from u. If u found, then it is not inside all max matchings.

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
#define eb emplace_back
const double pi = 3.1415926535898;
#define dout if(debug) cout
#define fi first
#define se second
#define sp setprecision
#define sz(a) (int(a.size()))
#define mp make_pair
#define all(a) a.begin(),a.end()
bool debug = 0;
const int LOG = 21;
const int mod = 1e9 + 7;
const int MX = 1e6;
typedef long long li;

template<class T1, class T2>
std::ostream &operator<<(std::ostream &out, const std::pair<T1, T2> &rhs) {
    out << "( " << rhs.first << " , " << rhs.second << " )";
    return out;
}

const int MAXN = 2 * 2020 + 1;
// 1-based Vertex index
int vis[MAXN], par[MAXN], orig[MAXN], match[MAXN], aux[MAXN], t, N;
vector<int> conn[MAXN];
queue<int> Q;

inline void addEdge(int u, int v) {
    conn[u].push_back(v);
    conn[v].push_back(u);
}

inline void init(int n) {
    N = n;
    t = 0;
    for (int i = 0; i <= n; ++i) {
        conn[i].clear();
        match[i] = aux[i] = par[i] = 0;
    }
}

inline void augment(int u, int v) {
    int pv = v, nv;
    do {
        pv = par[v];
        nv = match[pv];
        match[v] = pv;
        match[pv] = v;
        v = nv;
    } while (u != pv);
}

inline int lca(int v, int w) {
    ++t;
    while (true) {
        if (v) {
            if (aux[v] == t) return v;
            aux[v] = t;
            v = orig[par[match[v]]];
        }
        swap(v, w);
    }
}

inline void blossom(int v, int w, int a) {
    while (orig[v] != a) {
        par[v] = w;
        w = match[v];
        if (vis[w] == 1) Q.push(w), vis[w] = 0;
        orig[v] = orig[w] = a;
        v = par[w];
    }
}

bool bfs(int u) {
    fill(vis + 1, vis + 1 + N, -1);
    iota(orig + 1, orig + N + 1, 1);
    while (!Q.empty())
        Q.pop();

    Q.push(u);
    vis[u] = 0;
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        for (int x: conn[v]) {
            if (vis[x] == -1) {
                par[x] = v;
                vis[x] = 1;
                if (!match[x]) return augment(u, x), true;
                Q.push(match[x]);
                vis[match[x]] = 0;
            } else if (vis[x] == 0 && orig[v] != orig[x]) {
                int a = lca(orig[v], orig[x]);
                blossom(x, v, a);
                blossom(v, x, a);
            }
        }
    }
    return false;
}

bool just_try(int u, int spec) {

    fill(vis + 1, vis + 1 + N, -1);
    iota(orig + 1, orig + N + 1, 1);

    vis[spec] = 1;

    while (!Q.empty())
        Q.pop();


    Q.push(u);
    vis[u] = 0;
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        for (int x: conn[v]) {
            if (vis[x] == -1) {
                par[x] = v;
                vis[x] = 1;
                if (!match[x]) return true;
                Q.push(match[x]);
                vis[match[x]] = 0;
            } else if (vis[x] == 0 && orig[v] != orig[x]) {
                int a = lca(orig[v], orig[x]);
                blossom(x, v, a);
                blossom(v, x, a);
            }
        }
    }
    return false;
}

int Match() {
    int ans = 0;
// find random matching (not necessary, constant improvement)
    vector<int> V(N - 1);
    iota(V.begin(), V.end(), 1);
    //  shuffle(V.begin(), V.end(), mt19937(0x94949));



    for (auto x: V)
        if (!match[x]) {
            for (auto y: conn[x])
                if (!match[y]) {
                    match[x] = y, match[y] = x;
                    ++ans;
                    break;
                }
        }
    for (int i = 1; i <= N; ++i) if (!match[i] && bfs(i)) ++ans;
    return ans;
}

void solve() {
    int n;
    cin >> n;
    int m;
    cin >> m;
    init(n);
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        addEdge(a, b);
       // addEdge(b, a);
    }
    int val = Match();

    if (val * 2 == n) {
        cout << 0 << "\n";
    } else {

        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (match[i] == 0) {
                ans++;
            } else {
                int to = match[i];

                match[to] = match[i] = 0;
                if (just_try(to, i)) {
                    ans++;
                }
                match[i] = to;
                match[to] = i;

            }
        }
        cout << ans << "\n";
    }


}

signed main() {
#ifdef zxc
    debug = 0;
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
    cin >> t;
    for (int j = 1; j <= t; ++j) {
        solve();
    }
    if (debug) {
        cerr << endl;
        cerr << endl << "time : " << (1.0 * clock() / CLOCKS_PER_SEC) << endl;
    }

}