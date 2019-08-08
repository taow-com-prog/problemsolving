
/*
    As in editorial n*m + n * m * sqrt(n+m);
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


int a[1025][1025];
int h[1025];


int l[MAXN], r[MAXN];
int rr[MAXN];

int cnt[2000];

int dp[1500][1500];


vector<int> q[2000];

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int e = 1; e <= m; ++e) {
            char x;
            cin >> x;
            if(x =='1')
                a[i][e] = 1;
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int e = 1; e <= m; ++e) {
            h[e]++;
            h[e] *= a[i][e];
        }
        dout <<"H "<<endl;
        for(int e=1;e<=m;++e){
            dout <<h[e]<<" ";
        }
        dout << endl;

        stack<int> st;
        st.push(0);
        for (int e = 1; e <= m; ++e) {
            while (st.top() && h[st.top()] > h[e]) {
                st.pop();
            }
            l[e] = st.top();
            st.push(e);
        }
        dout <<"L "<<endl;
        for(int e=1;e<=m;++e){
            dout << l[e]<<" ";
        }
        dout << endl;

        while (!st.empty())
            st.pop();
        st.push(m + 1);

        int mxh = 0;
        for (int e = 1; e <= m; ++e)
            mxh = max(mxh, h[e]);
        for (int e = m; e >= 1; --e) {
            while (st.top() <= m && h[st.top()] > h[e]) {
                st.pop();
            }
            r[e] = st.top();
            st.push(e);
        }

        for (int e = m; e >= 1; --e) {
            if (r[e] == m + 1 || h[r[e]] < h[e]) {
                rr[e] = r[e];
                continue;
            }
            rr[e] = rr[r[e]];
        }

        for(int e=1;e<=m;++e){
            dout <<r[e]<<" ";
        }
        dout << endl;
        for(int e=1;e<=m;++e){
            dout <<rr[e]<<" ";
        }
        dout << endl;

        for (int e = 0; e <= mxh; ++e) {
            q[e].clear();
        }
        for (int e = 1; e <= m; ++e) {
            cnt[e] = 0;
        }
        for (int e = 1; e <= m; ++e) {
            q[h[e]].push_back(e);

        }
        set<int> sz;
        sz.insert(m);
        cnt[m] = 1;

        auto add = [&](int len) -> void {
            if (len < 0)
                return;
            cnt[len]++;
            if (sz.count(len) == 0)
                sz.insert(len);
        };

        auto rem = [&](int len) -> void {
            if (len < 0)
                return;
            cnt[len]--;
            if (cnt[len] == 0)
                sz.erase(len);
        };


        for (int e = 0; e < mxh; ++e) {
            dout << " e "<< e << endl;
            for (int v : q[e]) {
                if (l[v] != 0 && h[l[v]] == h[v]) {
                    //nothing
                    dout <<"add : "<< r[v] - v - 1<<endl;
                    add(r[v] - v - 1);
                } else {
                    dout <<"add1 " << v - l[v] - 1<< endl;
                    dout <<"add2 "<<r[v] - v - 1<<endl;
                    dout <<"rem "<<rr[v] - l[v] - 1<<endl;
                    add(v - l[v] - 1);
                    add(r[v] - v - 1);
                    rem(rr[v] - l[v] - 1);
                }
            }

            for (int v : sz) {
                dp[e + 1][v] += cnt[v];
            }
        }
    }

    for (int i = 1; i <= max(n, m); ++i) {
        for (int j = max(n,m); j >=1; --j) {
            dp[i][j - 1] += 2 * dp[i][j];
            if (j - 2 >= 0)
                dp[i][j - 2] -= dp[i][j];
        }
    }

    for(int i=1;i<=n;++i){
        for(int e=1;e<=m;++e){
            cout << dp[i][e]<<" ";
        }
        cout <<"\n";
    }
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