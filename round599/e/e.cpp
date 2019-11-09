// https://codeforces.com/contest/1242/submission/64387078

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
  ll k;
  cin >> k;
  vector< vector<ll> > a(k);
  vector<ll> sm(k);
  ll s = 0;
  map<ll, P> hs; // The map from v -> (i,j)
  vector< vector<P> > pr(k); // The next pair of (i,j)

  vector< vector<P> > way((1<<k)+10);
  vector<bool> mask((1<<k)+10);
  vector<bool> dp((1<<k)+10);
  vector<ll> pre((1<<k)+10);
  vector<P> sol(k);

  rep(i, k) {
    ll n;
    cin >> n;
    a[i].resize(n);
    pr[i].resize(n);
    rep(j, n) {
      cin >> a[i][j];
      s += a[i][j];
      sm[i] += a[i][j];
      hs[a[i][j]] = mp(i,j);
    }
  }
  if (s%k!=0) {
    cout << "No" << endl;
    return 0;
  }
  ll z = s/k;
  rep(i, k) {
    rep(j, a[i].size()) {
      pr[i][j] = hs.count(z-(sm[i]-a[i][j])) ? hs[z-(sm[i]-a[i][j])] : mp(-1LL, -1LL);
    }
  }
  bool found = false;
  rep(i, k) {
    if (found) { break; }

    rep(j, a[i].size()) {
      P fz = mp(i,j);
      vector<P> cyc;
      set<ll> ds;
      ll msk=0;
      while (true) {
        cyc.pb(fz);
        ds.insert(fz.fr);
        msk |= 1<<fz.fr;
        fz=pr[fz.fr][fz.sc];
        if (fz==mp(-1LL,-1LL)) { break; }
        if (ds.count(fz.fr)) { // cycle.
          if (fz!=mp(i,j)) { fz = mp(-1,-1); } // Other j
          break;
        }
      }
      if (fz==mp(-1LL,-1LL)) { continue; } // bad
      way[msk]=cyc;
      mask[msk]=1;
    }
  }
  dp[0]=1;
  for (ll S = 1; S < 1<<k; ++S) {
    ll nS=S;
    while (nS) {
      if (mask[nS]&&dp[S^nS]) {
        dp[S]=1;
        pre[S]=nS;
        break;
      }
      nS=(nS-1)&S;
    }
  }
  if (!dp[(1<<k)-1]) {
    cout << "No" << endl;
    return 0;
  }
  ll S=(1<<k)-1;
  while (S) {
    vector<P> c = way[pre[S]];
    rep(i, c.size()) {
      sol[c[i].fr] = mp(a[c[i].fr][c[i].sc], c[(i+c.size()-1)%c.size()].fr);
    }
    S^=pre[S];
  }

  cout << "Yes" << endl;
  rep(i, k) {
    cout << sol[i].fr << " " << sol[i].sc+1 << endl;
  }
}
