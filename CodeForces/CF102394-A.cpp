//
// Created by Ильдар Ялалов on 14.01.2020.
//
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>

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

#ifdef zxc
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

bool debug = 0;
const int MAXN = 3000 + 100;
const int LOG = 21;
const int mod = 1e8 + 7;
const int MX = (1e7 + 100);
typedef long long li;

vector<pii> g[MAXN];
int dis[MAXN];

bool ok(int n) {
    fill(dis, dis + n + 1, inf_int);
    dis[0] = 0;

    for (int iter = 0;; ++iter) {
        bool flag = true;
        for (int v = 0; v <= n; ++v) {
            for (auto[to, len] : g[v]) {
                if (dis[to] > dis[v] + len) {
                    dis[to] = dis[v] + len;
                    flag = false;
                }
            }
        }
        if (flag)
            return true;
        if (iter > n + 2)
            return false;
    }

}

void solve() {
    int n, m1, m2;
    cin >> n >> m1 >> m2;

    vector<tuple<int, int, int> > t1, t2;

    int mx = 0;
    for (int i = 1; i <= m1; ++i) {
        int l, r, x;
        cin >> l >> r >> x;
        t1.emplace_back(l, r, x);
        mx = max(mx, x);
    }
    for (int i = 1; i <= m2; ++i) {
        int l, r, x;
        cin >> l >> r >> x;
        t2.emplace_back(l, r, x);
        mx = max(mx, x);
    }
    int l = mx, r = n;
    debug(l,r);

    int ans = -1;
    auto clear = [](int n) {
        for (int i = 0; i <= n; ++i) {
            g[i].clear();
        }
    };
    auto add_edges = [&](int val) -> bool {
        for (int i = 0; i < n; ++i) {
            g[i].pb({i + 1, +1});
            g[i + 1].pb({i, 0});
        }

        for (auto[l, r, x] : t1) {
            g[r].emplace_back(l - 1, -x);
        }
        for (auto[l, r, x]:t2) {
            g[l - 1].emplace_back(r, val - x);
        }

        g[0].emplace_back(n, val);
        g[n].emplace_back(0, -val);
    };


    while (l <= r) {
        int mid = (l + r) >> 1;

        clear(n);

        add_edges(mid);
        debug(mid);
        for(int i = 0; i <= n;++i){
            debug(i, g[i]);
        }

        if (ok(n)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    assert(ans != -1);
    cout << ans << "\n";
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
    cin >> t;
    while (t--)
        solve();

    debug(1.0 * clock() / CLOCKS_PER_SEC);
}