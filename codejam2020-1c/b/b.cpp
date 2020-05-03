// ref. https://codingcompetitions.withgoogle.com/codejam/submissions/000000000019fef4/bWFyb29u

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

const ll N = 1e4;

void solve() {
  map<char,ll> cnt;
  set<char> app;
  {
    // consume u
    ll u; cin >> u;
  }
  rep(i,N) {
    ll tmp;cin>>tmp;
    string s;cin>>s;
    ++cnt[s[0]];
    for (char c:s) { app.insert(c); }
  }
  assert(cnt.size()==9);
  assert(app.size()==10);

  string ans(10,'?');
  vector<pair<ll,char>> w; // count=>char
  for (auto& p:cnt) { w.emplace_back(p.second,p.first); }
  sort(all(w)); // decreasing order.
  // Here, lower value is frequent.
  rep(i,9) { ans[9-i]=w[i].second; }
  for (char c:app) {
    if (cnt.count(c)==0) {
      ans[0]=c;
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
