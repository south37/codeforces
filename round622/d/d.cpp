// ref. https://codeforces.com/contest/1313/submission/71672133

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
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, m, k;
  cin >> n >> m >> k;
  vector<vector<ll>> t(2*n, vector<ll>(3)); // vector of triple
  rep(i, n) {
    ll l, r;
    cin >> l >> r;
    t[2*i]   = {     l,  1, i };
    t[2*i+1] = { r + 1, -1, i };
  }
  sort(all(t));
  vector<ll> states(1<<k, 0);
  vector<ll> newstates(1<<k, 0);
  ll sz = 0; // the size of streams
  ll pi = t[0][2], ni; // pre index, next index
  ll pp = t[0][0], np; // pre pos, next pos
  vector<ll> streams; // effective stream of spells
  rep(i, 2*n) {
    ni = t[i][2];
    np = t[i][0];
    if (t[i][1] == -1) { // close
      --sz; // decrease streams
      ll gi = 0; // target index
      while (streams[gi] != ni) { ++gi; }
      // Here, streams[gi] == ni
      rep(b, 1<<sz) {
        ll exp1 = ((b>>gi)<<(gi+1)) + (b%(1<<gi)); // xxx0xxx. 0 is at gi.
        ll exp2 = exp1 + (1<<gi); // xxx1xxx. 1 is at gi.
        newstates[b] = max(
            states[exp1] + (__builtin_popcount(exp1)%2) * (np-pp),
            states[exp2] + (__builtin_popcount(exp2)%2) * (np-pp));
      }
      states = newstates;
      streams.erase(streams.begin() + gi);
    } else { // open
      streams.push_back(ni);
      rep(b, 1<<sz) {
        // Set same value to b and b+(1<<sz). They are used in closed.
        newstates[b        ] = states[b] + (__builtin_popcount(b)%2) * (np-pp);
        newstates[b+(1<<sz)] = states[b] + (__builtin_popcount(b)%2) * (np-pp);
      }
      states = newstates;
      ++sz;
    }
    // Update pi, pp
    pi = ni;
    pp = np;
  }
  // At last, all streams are closed, so state becomes 0.
  cout << states[0] << " ";
}
