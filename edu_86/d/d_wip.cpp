#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <string.h>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

#define COUT(x) cout << #x << " = " << (x) << " (L" << __LINE__ << ")" << endl

template<class T> void printvec(const vector<T>& v) {
  for (auto x : v) { cout << x << " "; }
  cout << endl;
}
template<class T> void printtree(const vector< vector<T> >& tree) {
  for (long long i = 0; i < tree.size(); ++i) {
    cout << i + 1 << ": "; printvec(tree[i]);
  }
}
template<class T, class U> void printmap(const map<T, U>& mp) {
  for (auto x : mp) { cout << x.first << "=>" << x.second << endl; }
}

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

#define rep(i, n) for(ll i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()
#define fr first
#define sc second
#define mp make_pair
#define pb push_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

void solve() {
  ll n, k;
  cin >> n >> k;
  vector<ll> m(n);
  vector<ll> c(k+1);
  reverse(all(c));

  rep(i, n) {
    cin >> m[i];
  }
  rep(j, k) {
    cin >> c[j+1];
  }

  vector<ll> cnt(k+1);
  rep(i, n) {
    ++cnt[m[i]];
  }
  // Here, cnt is calculated
  set<P> st;
  rep(j, k+1) {
    if (cnt[j] > 0) {
      st.insert({ j, cnt[j] });
    }
  }

  ll ans = 0;
  while (!st.empty()) {
    ++ans;
    // add in greedy way
    ll cnt = 0;
    while (true) {
      ll id = upper_bound(all(c), cnt) - c.begin();
      if (id == n) { // not found
        break;
      }
      // Here, c[i] >= cnt
      ll v = n - id; // smallest value

      auto p = st.lower_bound({ v, -1 }); // smallest value in s
      if (p == st.begin() && p->first != v) { //
        break;
      }
      if (p == st.end()) { // v is large
        p = prev(st.end());
      }
      if (p->second == 1) { // should be erased
        st.erase(p);
      } else {
        --(*p).second;
      }
      ++cnt;
    }
  }
  cout << ans << endl;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll t;
  cin >> t;
  rep(i, t) {
    cout << "Case #" << (i+1) << ": ";
    solve();
  }
}
