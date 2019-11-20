// base. https://pastebin.com/6FeZb3XH

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

struct Antenna {
  int left, right;
};

// [1, .. m] is the road.
// We have n anttennas. Each antenna has [x-s, x+s] area.
// Its width is 2s+1. We want to cover all area.

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  int n, m;
  cin >> n >> m;
  vector<Antenna> a(n);
  rep(i, n) {
    int x, s;
    cin >> x >> s;
    a[i].left = max(0, x - s); // NOTE: We include 0.
    a[i].right = min(x + s, m);
  }

  // minCost[i] .. the minimum cost to reach m (to cover [x, m]).
  // minCost[m] = 0. If there is no light, then minCost[x] = m-x;
  vector<int> minCost(m+1);
  minCost[m] = 0;

  // We decide minCost from right. When we consider about the minCost[pos], then
  // minCost[x] where x > po are already calculated.
  for (int pos = m-1; pos >= 0; --pos) {
    minCost[pos] = m - pos; // The default cost.

    rep(j, n) { // Loop antenna
      int left = a[j].left, right = a[j].right;
      if (left <= pos+1 && pos+1 <= right) { // pos+1 is initialy covered
        minCost[pos] = minCost[pos+1];
        break;
      }

      if (pos < left) {
        int accessCost = left - pos - 1; // The distance between pos, left.
        int nextPos = min(m, right + accessCost);
        chmin(minCost[pos], accessCost + minCost[nextPos]);
      }
    }
  }

  cout << minCost[0] << endl;
}
