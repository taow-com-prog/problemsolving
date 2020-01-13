//
// generate random string from 0-1 and subtract two with the same modulo N.
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

class FourDistinctDigits {
public:

    string find(long long N, int D, int B) {
        mt19937 mt(228);

        map<ll, vector<int> > mp;
        while (true) {
            vector<int> a;
            for (int i = 0; i < D; ++i) {
                a.pb(mt() & 1);
            }
            ll val = 0;
            for (int v : a) {
                assert(v == 0 || v == 1);
                val = (val * B + v) % N;
            }
            if (mp.count(val)) {
                vector<int> x = mp[val];
                vector<int> y = a;
                if (x == y)
                    continue;
                if (x < y)
                    swap(x, y);
                vector<int> res(D);
                debug(x);
                debug(y);
                for (int i = D - 1; i >= 0; --i) {
                    if (x[i] < y[i]) {
                        x[i - 1]--;
                        x[i] += B;
                    }
                    res[i] = x[i] - y[i];
                }




                reverse(all(res));
                while (res.size() > 0 && res.back() == 0) {
                    res.pop_back();
                }
                assert(res.size() != 0);
                reverse(all(res));
                while (res.size() < D) {
                    res.push_back(0);
                }

                ll flag = 0;
                for(int v : res){
                    flag = (flag * B + v)%N;
                }
                debug(res);
                debug(flag);

                string ans = "";
                for (int v : res) {
                    if (v <= 9) {
                        ans.pb('0' + v);
                    } else if (v <= 35) {
                        ans.pb('A' + v - 10);
                    } else {
                        ans.pb('a' + v - 36);
                    }
                }
                return ans;
            }
            mp[val] = a;
        }
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
    FourDistinctDigits myclass;
    cout << myclass.find(a, b, c) << endl;

}