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

  ll n1, n2, n3;
  cin >> n1 >> n2 >> n3;
  ll n = n1 + n2 + n3;
  vector<int> who(n, -1);
  rep(iter, n1) {
    int a;
    cin >> a;
    --a;
    who[a] = 0;
  }
  rep(iter, n2) {
    int a;
    cin >> a;
    --a;
    who[a] = 1;
  }
  rep(iter, n3) {
    int a;
    cin >> a;
    --a;
    who[a] = 2;
  }
  // printvec(who);

  vector<int> prefix_sums[3];
  rep(p, 3) {
    prefix_sums[p].assign(n + 1, 0);
    rep(i, n) {
      prefix_sums[p][i+1] = prefix_sums[p][i] + (who[i] == p ? 1 : 0);
    }
  }

  vector<int> dp[4]; // 3 + 1 = 4
  dp[3].assign(n + 1, INF);
  dp[3][n] = 0;

  for (int p = 2; p >= 0; --p) {
    dp[p].assign(n + 1, INF);
    dp[p][n] = 0;
    int minimum = INF;

    for (int i = n; i >= 0; --i) {
      chmin(minimum, i - prefix_sums[p][i] + dp[p + 1][i]);
      if (i < n) {
        dp[p][i] = minimum - i + prefix_sums[p][i];
      }
    }
  }

  cout << dp[0][0] << endl;
}
