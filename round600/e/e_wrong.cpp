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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, m;
  cin >> n >> m;
  vector<P> lights;
  rep(i, n) {
    ll x, s;
    cin >> x >> s;
    lights.emplace_back(x, s);
  }
  sort(all(lights));
  rep(i, n) {
    ll x = lights[i].fr;
    ll s = lights[i].sc;
    cout << "(x, s)" << "("<<x<<", "<<s<<")" << endl;
  }

  // Now, lights are sorted in increasing order.
  vector<ll> dist(n+1); // dist[i] .. the distance between lights[i], lights[i-1]. dist[0] is between the boundary.
  dist[0] = max(0LL, lights[0].fr - lights[0].sc);
  for (int i = 1; i < n; ++i) {
    dist[i] = max(0LL, (lights[i].fr - lights[i-1].fr) - (lights[i].sc + lights[i-1].sc));
  }
  dist[n] = max(0LL, (m - lights[n-1].fr) - lights[n-1].sc);
  cout << "dist: "; printvec(dist);

  // Now, we decide coins from left.
  ll ans = 0;
  if (dist[0] > 0) {
    rep(i, n) {
      if (dist[i] > 0) {
        ans += dist[i]; // Use dist[i] conins
        dist[i+1] = max(0LL, dist[i+1] - dist[i]);
      }
    }
    if (dist[n] > 0) {
      ans += dist[n];
    }
  } else {
    for (int i = n; i >= 1; --i) {
      if (dist[i] > 0) {
        ans += dist[i]; // Use dist[i] conins
        dist[i-1] = max(0LL, dist[i-1] - dist[i]);
      }
    }
    if (dist[0] > 0) {
      ans += dist[0];
    }
  }

  cout << ans << endl;
}
