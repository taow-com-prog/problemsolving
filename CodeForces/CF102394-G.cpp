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


const int all_bits = (1 << 60) - 1;

struct Vector {
    ll one, two;

    Vector() {
        one = two = 0;
    }

    Vector(ll One, ll Two) {
        one = One;
        two = Two;
    }

    Vector operator+(const Vector &a) const {
        Vector res;
        ll zero = all_bits ^one ^two;
        ll a_zero = all_bits ^a.one ^a.two;
        res.one = (zero & a.one) | (one & a_zero) | (two & a.two);
        res.two = (zero & a.two) | (one & a.one) | (two & a_zero);
        return res;
    }

    Vector minus() const {
        Vector res(two, one);
        return res;
    }

    Vector operator-(const Vector &a) const {
        return *this + a.minus();
    }

    inline int get(int pos) {
        if ((one >> pos)&1)
            return 1;
        if ((two >> pos)&1)
            return 2;
        return 0;
    }
};

ll ans = 0;

Vector v[64];
ll val[64];

void update(Vector a, ll cost) {
    for (int i = 0; i < 60; ++i) {
        if (a.get(i) == 0)
            continue;
        if (v[i].get(i) == 0) {
            v[i] = a;
            val[i] = cost;
            ans += cost;
            return;
        }
        if (cost > val[i]) {
            ans = ans + cost - val[i];
            swap(val[i], cost);
            swap(v[i], a);
        }
        if (v[i].get(i) == a.get(i)) {
            a = a - v[i];
        } else {
            a = a + v[i];
        }
    }
}


void solve() {
    int n;
    cin >> n;
    ll last = 0;
    for (int i = 1; i <= n; ++i) {
        ll a, b;
        cin >> a >> b;
        a ^= last;
        b ^= last;
        Vector cur(a, 0);
        update(cur, b);
        last = ans;
        cout << ans << "\n";
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