// base. https://codeforces.com/blog/entry/71434

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

  int ans = 0;
  int bestp = 0; // The maximum case of cnt[l][0]-cnt[l][1]
  rep(i, n) {
    if (who[i] != 2) { ++ans; }
  }
  vector<int> cntl(3); // The numbers in l
  vector<int> cntr(3); // The numbers in r
  rep(i, n) {
    ++cntr[who[i]];
  }

  // We want to minimize the cnt[l][1] + cnt[l][2] + cnt[m][0] + cnt[m][2] + cnt[r][0] + cnt[r][1].
  // It is same with the maximisze cnt[l][0] - cnt[l][1] in each r.
  // At first, len(r) is n. we check all case of r.

  rep(i, n) {
    // Set i to l and remove from r.
    ++cntl[who[i]];
    --cntr[who[i]];

    chmax(bestp, cntl[0] - cntl[1]); // When bestp is maximized, the i is the boundary of l and m.
    int curans = cntr[0] + cntr[1] + cntl[2] + cntl[0] - bestp;
    chmin(ans, curans);
  }

  cout << ans << endl;
}
