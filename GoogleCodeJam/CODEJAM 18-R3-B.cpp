/*
    first solution in the editorial.
    Adj ^ j
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

mt19937 mt(228);



int parent[MAXN];
void make_set(int n){
    for(int i=1;i<=n;++i){
        parent[i] = i;
    }
}
int get(int v){
    if(v == parent[v])
        return v;
    return parent[v] = get(parent[v]);
}
void union_set(int a,int b){
    a = get(a);
    b = get(b);
    if(a != b){
        parent[b] = a;
    }
}
vector<pii> generate_edges(int n) {
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;
    vector<int> v4;

    for (int i = 1; i <= n; ++i) {
        v1.pb(i);
        v2.pb(i);
        v3.pb(i);
        v4.pb(i);
    }
    shuffle(all(v1), mt);
    shuffle(all(v2), mt);
    shuffle(all(v3), mt);
    shuffle(all(v4), mt);


    for (int i = 0; i < n; ++i) {
        if (v1[i] == v2[i] || v3[i] == v4[i]) {
            return generate_edges(n);
        }
    }

    map<pii,int> mp;
    vector<pii> res;
    for (int i = 0; i < n; ++i) {
        mp[{v1[i], v2[i]}]++;
        mp[{v2[i], v1[i]}]++;
        mp[{v3[i], v4[i]}]++;
        mp[{v4[i], v3[i]}]++;

        res.pb({v1[i], v2[i]});
        res.pb({v3[i], v4[i]});
    }
    for(auto x:mp){
        if(x.se != 1){
            return generate_edges(n);
        }
    }

    make_set(n);
    for(auto x:res){
        union_set(x.fi,x.se);
    }
    for(int i=1;i<=n;++i){
        if(get(i) != get(1))
            return generate_edges(n);
    }

    sort(all(res));

    return res;
}

typedef vector<vector<ll> > matrix;


matrix multiply(const matrix& A,const matrix& B) {
    int n = sz(A);

    matrix res(n, vector<ll>(n));
    for (int i = 0; i < n; ++i) {
        for (int e = 0; e < n; ++e) {
            for (int j = 0; j < n; ++j) {
                res[i][e] += A[i][j] * B[j][e];
            }
        }
    }
    return res;
}

pair<int, map<vector<ll>, int> > get(int n, vector<pii> &edges) {


    matrix A(n, vector<ll>(n));
    for (auto x:edges) {
        A[x.fi-1][x.se-1] = 1;
        A[x.se-1][x.fi-1] = 1;
    }
    matrix P(n, vector<ll>(n));
    for (int i = 0; i < n; ++i) {
        P[i][i] = 1;
    }

    for (int j = 1; j <= 10; ++j) {
        P = multiply(P, A);

        bool flag = true;
        map<vector<ll>, int> mp;
        for (int i = 0; i < n; ++i) {
            vector<ll> cur = P[i];
            sort(all(cur));
            if (mp.count(cur)) {
                flag = false;
                break;
            } else {
                mp[cur] = i;
            }
        }
        if (flag) {
            return {j, mp};
        }
    }
    map<vector<ll>, int> mp;
    return {-1, mp};
}

void solve() {
    int l, r;
    cin >> l;
    if(l == -1)
        exit(0);
    cin >> r;
    int n = l;
    cout <<n << endl;

    int it = 1;
    while (it++) {
        vector<pii> edges = generate_edges(n);
        cerr <<"graph generated "<< endl;
        auto res = get(n, edges);
        cerr << "res "<<res.fi << endl;
        if (res.fi == -1)
            continue;
        for (auto x:edges) {
            cout << x.fi << " " << x.se << endl;
        }

        cin >> n;
        if(n == -1){
            exit(0);
        }
        vector<pii> edges1;
        for (int i = 1; i <= 2 * n; ++i) {
            int a, b;
            cin >> a >> b;
            edges1.pb({a, b});
        }
        auto res2 = get(n, edges1);
        if(res.fi != res2.fi)
            exit(0);
        for (int i = 0; i < n; ++i) {
            if(i > 0)
                cout <<" ";
            for (const auto &x:res.se) {
                if(x.se == i){
                    cout << res2.se[x.fi]+1;
                }
            }
        }
        cout << endl;


        break;
    }

}

signed main() {
#ifdef zxc
   // debug = 1;
   // freopen("../input.txt", "r", stdin);
    //freopen("../output.txt", "w", stdout);
#else

#endif //zxc
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.setf(ios::fixed);
    cout.precision(20);

    int t = 1;
    cin >> t;
    while (t--)
        solve();
    if (debug)
        cerr << endl << "time : " << (1.0 * clock() / CLOCKS_PER_SEC) << endl;
}