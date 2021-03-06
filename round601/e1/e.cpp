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

const ll INF = 1e18;
const ll MOD = 1000000007;  // 1e9 + 7

vector<ll> v; // The indices of a[i] where a[i] == 1

ll cost(ll p) {
  // cout << "p: " << p << endl;

  ll res = 0;
  for (ll i = 0; i < v.size(); i += p) {
    ll median = v[i + (p-1)/2];
    // cout << "median: " << median << endl;
    rep(j, p) {
      // cout << "i+j: " << i+j << endl;
      // cout << "v[i+j]: " << v[i+j] << endl;
      res += abs(v[i+j] - median);
    }
  }
  // cout << "res: " << res << endl;
  return res;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> a(n);
  rep(i, n) {
    cin >> a[i];
    if (a[i] == 1) {
      v.push_back(i);
    }
  }

  if (v.size() == 0) {
    cout << -1 << endl;
    return 0;
  }
  if (v.size() == 1) {
    cout << -1 << endl;
    return 0;
  }

  // cout << "v.size(): " << v.size() << endl;
  // cout << "v: "; printvec(v);

  ll i = 2;
  ll tmp = v.size();
  set<ll> pf; // prime factors of v.size().
  while (i * i <= tmp) {
    while (tmp % i == 0) {
      pf.insert(i);
      tmp /= i;
    }
    ++i;
  }
  if (tmp > 1) { // We consider
    pf.insert(tmp);
  }

  ll ans = INF;
  // Check all cost of pf.
  for (auto x : pf) {
    chmin(ans, cost(x));
  }

  cout << ans << endl;
}
