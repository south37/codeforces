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
  ll n, m;
  cin >> n >> m;
  vector<P> a(n); // The pair of (cost, id)
  rep(i, n) {
    cin >> a[i].fr;
    a[i].sc = i;
  }
  sort(all(a));
  // Now, a is increasing order of cost.

  if (n == 2) { // If n = 2, we can not create
    cout << -1 << endl;
    return;
  }


  vector<pair<P,P>> ans;
  if (n == 3) {
    ans.emplace_back(a[0], a[1]);
    ans.emplace_back(a[1], a[2]);
    ans.emplace_back(a[2], a[0]);
  } else { //n >= 4
    // Now, n = 4. we use first 2 as all pairs.
    for (int i = 2; i < n; ++i) { // [2, n-1]
      ans.emplace_back(a[i], a[0]);
      ans.emplace_back(a[i], a[1]);
    }
  }

  if (ans.size() > m) {
    cout << -1 << endl;
    return;
  }

  // cout << "Debug" << endl;
  // cout << "ans.size(): " << ans.size() << endl;
  // cout << "m-ans.size(): " << m-ans.size() << endl;

  ll rest = m - ans.size();
  rep(iter, rest) {
    ans.emplace_back(a[0], a[1]);
  }

  // Now, ans contains all information
  ll sum = 0;
  vector<P> pairs;
  rep(i, ans.size()) {
    sum += ans[i].fr.fr;
    sum += ans[i].sc.fr;
    pairs.emplace_back(ans[i].fr.sc, ans[i].sc.sc);
  }

  cout << sum << endl;
  rep(i, pairs.size()) {
    cout << pairs[i].fr + 1 << " " << pairs[i].sc + 1 << endl;
  }
  return;
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
