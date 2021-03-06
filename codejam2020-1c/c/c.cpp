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

void solve() {
  ll n, d;
  cin >> n >> d;
  vector<ll> a(n);
  rep(i,n) {
    cin >> a[i];
  }
  sort(all(a), greater<ll>()); // decreasing order
  ll ans=d;
  for (ll q=1; q<=d; ++q) {
    vector<ll> b=a;
    for (auto&v:b) { v*=q; }
    vector<P> ls; // pair of <v/x, x> where v = values in b.
    // Here, try all cut cases.
    for (auto v:b) {
      for (ll x=1; x <= min(v,d); ++x) { // x .. count of cut. e.g. 3 -> (1,3). required operation is x-1.
        if (v%x==0) {
          ls.emplace_back(v/x,x);
        }
      }
    }
    sort(all(ls)); // increasing order.
    for (int i=0;i<ls.size();) {
      ll cnt=0, j=i, ok=0; // ok is "the effective count of equal division".
      // Here, calculate the count with "same first" values.
      while (j<ls.size() && ls[i].first == ls[j].first) {
        cnt += ls[j].second;
        if (cnt <= d) { ++ok; }
        ++j;
      }
      // Here, j == ls.size() or ls[j].first != ls[i].first
      ll v = ls[i].first;

      ll s=0; // available count by v.
      for (auto w:b) {
        ll u=w/v; // available cut.
        if (u == 0) { break; } // too small.
        s += u;
        if (s >= d) { break; }
      }
      if (s >= d) {
        chmin(ans, d-ok);
      }
      i=j;
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
