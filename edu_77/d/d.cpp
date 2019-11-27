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

ll m, n, k, t;
vector<ll> a;
vector<triple> rld; // (r, l, d);

bool cond(ll min_a) {
  ll cost = n + 1; // The default cost.

  ll prev_l = -1;
  ll prev_r = -1;

  // cout << "min_a: " << min_a << endl;

  rep(i, k) {
    ll r, l, d;
    tie(r, l, d) = rld[i];

    if (d <= min_a) { continue; } // consider only min_a < d case.

    // Here, we consider the rld[i].
    if (prev_l == -1) {
      prev_l = l;
      prev_r = r;
      continue;
    } else { // Here, we compare.
      ll diff1 = (r-l+1) + (prev_r-prev_l+1);
      ll diff2 = max(prev_r, r) - min(prev_l, l) + 1;
      // cout << "r: " << r << endl;
      // cout << "l: " << l << endl;
      // cout << "prev_r: " << prev_r << endl;
      // cout << "prev_l: " << prev_l << endl;
      // cout << "(r-l+1) + (prev_r-prev_l+1): " << (r-l+1) + (prev_r-prev_l+1) << endl;
      // cout << "max(prev_r, r) - min(prev_l, l)+1" << max(prev_r, r) - min(prev_l, l)+1 << endl;

      if (diff1 <= diff2) { // divide is ok.
        cost += 2*(prev_r-prev_l+1); // Add the cost.
        prev_r = r;
        prev_l = l;
        continue;
      } else {
        prev_r = max(prev_r, r);
        prev_l = min(prev_l, l);
        continue;
      }
    }
  }
  cost += 2*(prev_r - prev_l+1);
  // cout << "cost: " << cost << endl;
  // cout << "t: " << t << endl;
  // cout << endl;
  // cout << "(cost <= t): " << (cost <= t) << endl;

  return (cost <= t);
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> m >> n >> k >> t;

  a.resize(m);
  rep(i, m) {
    cin >> a[i];
  }
  sort(all(a)); // Now, a is increasing order.

  // cout << "a: "; printvec(a);

  rep(i, k) {
    ll l, r, d;
    cin >> l >> r >> d;
    rld.emplace_back(r, l, d);
  }
  sort(all(rld));

  // We find min a by binary search.
  ll max_a = a[a.size()-1];
  ll min_a = a[0];

  if (!cond(max_a)) { // fail with max soldier
    cout << 0 << endl;
    return 0;
  }

  ll r = max_a;
  ll l = 0;
  // (l, r]
  // [ng, ng, ... , ok, ok]
  while (r - l > 1) {
    ll m = (r+l)/2;
    if (cond(m)) { // ok
      r = m;
    } else {
      l = m;
    }
  }

  // cout << "r: " << r << endl;
  // cout << "l: " << l << endl;

  // Now, l is the maximum cond.
  ll ans = 0;
  rep(i, m) {
    // cout << "a[i]: " << a[i] << endl;
    if (a[i] >= r) {
      ++ans;
    }
  }

  cout << ans << endl;
}
