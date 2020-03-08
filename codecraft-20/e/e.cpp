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

  ll n, p, k;
  cin >> n >> p >> k;
  vector<P> a(n); // the pair of <audience score, index>
  rep(i, n) {
    cin >> a[i].first;
    a[i].second = i;
  }
  sort(all(a));
  reverse(all(a));

  // s[i][j] .. the score of i at position j
  vector<vector<ll>> s(n, vector<ll>(p));
  rep(i, n) {
    rep(j, p) {
      cin >> s[i][j];
    }
  }

  // dp[i][mask] .. maximum score of [0, i) with mask. initialized by -1.
  vector<vector<ll>> dp(n+1, vector<ll>(1<<p, -1));
  dp[0][0] = 0;

  rep(i, n) {
    ll x = a[i].second;

    rep(mask, 1<<p) {
      ll ct = 0; // The count of selected players
      rep(j, p) {
        if (mask & (1ll<<j)) { ++ct; }
      }

      // Try audience
      if (dp[i][mask] != -1) {
        ll z = i-ct; // The count of already selected audience

        if (z < k) { // z haven't reached to k
          dp[i+1][mask] = dp[i][mask] + a[i].first;
        } else {
          dp[i+1][mask] = dp[i][mask];
        }
      }

      // Trye player
      rep(j, p) {
        ll pre_mask = mask & (~(1ll<<j));
        if ((mask & (1ll<<j)) && dp[i][pre_mask] != -1) {
          dp[i+1][mask] = max(dp[i+1][mask], dp[i][pre_mask] + s[x][j]);
        }
      }
    }
  }

  cout << dp[n][(1<<p)-1] << endl;
  return 0;
}
