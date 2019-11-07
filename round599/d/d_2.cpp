// https://codeforces.com/contest/1243/submission/64391286

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <set>

using namespace std;

typedef long long   ll;
typedef long double ld;

#define all(x)  (x).begin(), (x).end()
#define sz(x)   (x).size()
#define pb      push_back
#define mp      make_pair
#define fr      first
#define sc      second

const int N = 100 * 1000 + 5;

int n, m;
set<pair<int, int>> st;
vector<int> gp[N];
int vals[N];
int harevanner[N];

void input() {
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        gp[u].pb(v);
        gp[v].pb(u);
        if (min(u, v) == 0) {
            harevanner[max(u, v)] = 1;
        }
    }
}

void solve() {
    vals[0] = -1;
    for(int i = 1; i < n; i++) {
        st.emplace(harevanner[i], i);
        vals[i] = harevanner[i];
    }
    int current = 1, ans = 0;
    while(!st.empty()) {
        auto elem = *st.begin();
        st.erase(st.begin());
        if (elem.fr == current) {
            ans++;
        }
        int u = elem.sc;
        vals[u] = -1;
        for(int v : gp[u]) {
            if (vals[v] == -1) continue;
            auto it = st.find(mp(vals[v], v));
            vals[v]++;
            st.erase(it);
            st.emplace(vals[v], v);
        }
        current++;
    }
    cout << ans << endl;
}

int main() {
    int testcases = 1;
    // scanf("%d", &testcases);
    while(testcases--) {
        input();
        solve();
    }
    return 0;
}
