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

void solve() {
  ll n;
  cin >> n;
  vector<ll> a(n, 0);
  rep(i, n) {
    cin >> a[i];
  }
  ll m;
  cin >> m;
  vector<ll> bst(n + 1, 0); // bst[i] .. The maximum power to to reach i distance.
  vector<ll> p(m);
  vector<ll> s(m);
  rep(i, m) {
    cin >> p[i] >> s[i];
    chmax(bst[s[i]], p[i]);
  }
  for (int i = n - 1; i >= 0; --i) {
    chmax(bst[i], bst[i + 1]);
  }

  ll pos = 0;
  ll res = 0;
  while (pos < n) {
    ++res;
    ll npos = pos; // The next position.
    ll mx = 0; // The maximum power of monsters.
    while (npos < n) {
      chmax(mx, a[npos]);
      if (mx > bst[npos - pos + 1]) { break; } // We can't beat a monster by bst[dist].
      ++npos;
    }
    // cout << "a[npos]: " << a[npos] << endl;
    // cout << "npos: " << npos << endl;
    // cout << "mx: " << mx << endl;
    // cout << "bst[npos - pos + 1]: " << bst[npos - pos + 1] << endl;
    // cout << "npos - pos + 1: " << npos - pos + 1 << endl;
    if (pos == npos) { // we can't beat any monster.
      cout << -1 << endl;
      return;
    }
    pos = npos;
  }

  cout << res << endl;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll t;
  cin >> t;
  rep(i, t) {
    solve();
  }
}
