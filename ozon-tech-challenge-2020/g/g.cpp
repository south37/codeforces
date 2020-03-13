// ref. https://codeforces.com/blog/entry/74459

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

const int MAX_A = 1 << 18;

class UnionFind {
public:
  UnionFind(int n) : par(n, -1), rnk(n, 0), cnt(n, 1) {}

  bool same(int x, int y) {
    return root(x) == root(y);
  }
  void unite(int x, int y) {
    x = root(x); y = root(y);
    if (x == y) return;

    if (rnk[x] < rnk[y]) { swap(x, y); }
    par[y] = x;
    cnt[x] += cnt[y];
    if (rnk[x] == rnk[y]) { ++rnk[x]; }
  }
  int root(int x) {
    if (par[x] < 0) {
      return x;
    } else {
      return par[x] = root(par[x]);
    }
  }
  int count(int x) {
    return cnt[root(x)];
  }

private:
  vector<int> par;
  vector<int> rnk;
  vector<int> cnt; // The number of vertices in each connected components.
};

// int main(int argc, char** argv) {
//   ll N, M;
//   cin >> N >> M;
//   UnionFind tree(N);
//   rep(i, M) {
//     ll p, a, b;
//     cin >> p >> a >> b;
//     if (p == 0) { // Connect
//       tree.unite(a, b);
//     } else { // Judge
//       if (tree.same(a, b)) {
//         cout << "Yes" << endl;
//         cout << "size: " << tree.size() << endl;
//         cout << "count(" << a << "): " << tree.count(a) << endl;
//         cout << "count(" << b << "): " << tree.count(b) << endl;
//       } else {
//         cout << "No" << endl;
//         cout << "size: " << tree.size() << endl;
//         cout << "count(" << a << "): " << tree.count(a) << endl;
//         cout << "count(" << b << "): " << tree.count(b) << endl;
//       }
//     }
//   }
// }

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  int n;
  cin >> n;

  ll ans = 0;
  vector<int> cnt(MAX_A); // the count of each a values
  rep(i, n) {
    int a;
    cin >> a;
    ++cnt[a];
    ans -= a;
  }
  ++cnt[0];
  UnionFind uf(MAX_A);

  for (int sum = MAX_A-1; sum >= 0; --sum) {
    // We check the (i, j) pair in which i&j == 0 && i|j == sum
    // cf. https://codeforces.com/blog/entry/45223
    for (int i = sum; i > 0; i = (i-1)&sum) {
      int j = sum ^ i;
      if (cnt[i] > 0 && cnt[j] > 0) { // edge exists
        if (uf.same(i, j)) { // alreacy connected
          continue;
        } else {
          // contrib .. the number of edges between cnt[i] and cnt[j].
          int contrib = -1;
          contrib += (uf.count(i) == 1) ? cnt[i] : 1; // if already connected, we add only one edge
          contrib += (uf.count(j) == 1) ? cnt[j] : 1;
          uf.unite(i, j);
          ans += 1ll * sum * contrib;
        }
      }
    }
  }

  cout << ans << endl;
}
