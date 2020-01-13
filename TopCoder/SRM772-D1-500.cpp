/*
	Greedy add points by distance to all other points.
*/

//
// Created by Ильдар Ялалов on 28.10.2019.
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
const int MAXN = 1e6 + 100;
const int LOG = 20;
const int mod = 1e9 + 7;
const int MX = (1e7 + 100) * 1.5;
typedef long long li;

class MaxPoints {
public:

    ll get_all(vector<int> A) {
        ll res = 0;
        sort(all(A));
        ll sum = 0;
        for (int i = 0; i < sz(A); ++i) {
            res += (1ll * i * A[i] - sum);
            sum += A[i];
        }
        return res;
    }

    int findMaxPoints(int N, vector<int> XG, vector<int> YG, long long K, int seedX, int seedY) {
        vector<ll> A(N);
        A[0] = seedX;
        for (int i = 1; i < N; ++i) {
            A[i] = (A[i - 1] * 1103515245 + 12345) % 2147483648;
        }
        vector<int> X(N);
        for(int i = 0;i < sz(XG);++i){
            X[i] = XG[i];
        }
        for (int i = sz(XG); i < N; ++i) {
            X[i] = (A[i] % 2000001) - 1000000;
        }
        vector<ll> B(N);
        B[0] = seedY;
        for (int i = 1; i < N; ++i) {
            B[i] = (B[i - 1] * 1103515245 + 12345) % 2147483648;
        }
        vector<int> Y(N);
        for(int i = 0;i < sz(YG);++i){
            Y[i] = YG[i];
        }
        for (int i = sz(YG); i < N; ++i) {
            Y[i] = (B[i] % 2000001) - 1000000;
        }


        ll cur = -get_all(X) - get_all(Y);
      //  debug(X);
        //debug(Y);
       // debug(cur);
        if(cur > K)
            return -1;




        vector<ll> dist(N);
        vector<pii> XX;
        vector<pii> YY;
        for (int i = 0; i < N; ++i) {
            XX.pb({X[i], i});
            YY.pb({Y[i], i});
        }
        sort(all(XX));
        sort(all(YY));
        ll sumX = 0;
        ll sumY = 0;
        for (int i = 0; i < N; ++i) {
            int id = XX[i].se;
            dist[id] += (1ll * XX[i].fi * i - sumX);
            id = YY[i].se;
            dist[id] += (1ll * YY[i].fi * i - sumY);
            sumX += XX[i].fi;
            sumY += YY[i].fi;
        }
        //debug(dist);

        sumX = sumY = 0;
        for (int i = N - 1; i >= 0; --i) {
            int id = XX[i].se;
            ll cnt = N - i - 1;
            dist[id] += (sumX - cnt * XX[i].fi);
            id = YY[i].se;
            dist[id] += (sumY - cnt * YY[i].fi);
            sumX += XX[i].fi;
            sumY += YY[i].fi;
        }
       // debug(dist);

        vector<pair<ll, int> > order;
        for (int i = 0; i < N; ++i) {
            order.pb({dist[i], i});
        }
        sort(all(order));
        int ans = 0;
        for (auto x : order) {
            if (cur + x.fi <= K) {
                cur += x.fi;
                ans++;
            } else {
                break;
            }
        }
        return ans;
    }

};


signed main() {
#ifdef zxc
    freopen("../input.txt", "r", stdin);
    //    freopen("../output.txt", "w", stdout);
#else
#endif //zxc
    ll a, b, c;
    cin >> a >> b >> c;
    MaxPoints myclass;
    ll n = 100000;
    vector<int> XG = {};
    vector<int> YG = {};
    ll k = -3829423936963408;
    int seedX = 1225224201;
    int seedY = 441244497;
    cout << myclass.findMaxPoints(n, XG, YG, k, seedX, seedY) << endl;

}