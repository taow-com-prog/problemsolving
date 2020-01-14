// AS in editorial

//
// Created by Ильдар Ялалов on 14.01.2020.
//
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
typedef unsigned int uint;
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
const int MAXN = 1000 + 100;
const int LOG = 21;
const int mod = 1e9 + 7;
const int MX = (1e7 + 100) * 1.5;
typedef long long li;


template<uint MD>
struct ModInt {
    using M = ModInt;
    uint v;

    ModInt() : v{0} {}

    ModInt(ll _v) : v{normS(_v % MD + MD)} {}

    explicit operator bool() const { return v != 0; }

    static uint normS(uint x) { return (x < MD) ? x : x - MD; };

    static M make(uint x) {
        M m;
        m.v = x;
        return m;
    }

    static M inv(const M &x) { return x.pow(MD - 2); }

    M operator+(const M &r) const { return make(normS(v + r.v)); }

    M operator-(const M &r) const { return make(normS(v + MD - r.v)); }

    M operator*(const M &r) const { return make(ull(v) * r.v % MD); }

    M operator/(const M &r) const { return *this * inv(r); }

    M &operator+=(const M &r) { return *this = *this + r; }

    M &operator-=(const M &r) { return *this = *this - r; }

    M &operator*=(const M &r) { return *this = *this * r; }

    M &operator/=(const M &r) { return *this = *this / r; }

    M pow(ll n) const {
        M x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
};

using Mint = ModInt<mod>;

using P = pair<Mint, Mint>; // 0101, all

P solve(vector<int> &a) {
    int n = sz(a);
    int mn = *min_element(all(a));

    int cnt = 0;
    vector<int> nxt;

    Mint total = 1;
    Mint spec = 1;
    for (int &v:a) {
        v -= mn;
    }
    for (int i = 0; i < n; ++i) {
        if (a[i] == 0) {
            if (!nxt.empty()) {
                auto res = solve(nxt);
                total *= res.first + res.second;
                spec *= res.first;
            }
            nxt.clear();
            cnt++;
        } else {
            nxt.pb(a[i]);
        }
    }
    if (!nxt.empty()) {
        auto res = solve(nxt);
        total *= (res.first + res.second);
        spec *= res.first;
    }

    total = total * (Mint(2).pow(cnt));

    total = total + spec * (Mint(2).pow(mn) - 2);
    spec = spec * (Mint(2).pow(mn));
    return {spec, total};
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cout << solve(a).second.v << "\n";
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
