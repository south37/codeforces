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

// Segment Tree
template <typename T>
class SegTree {
public:
  SegTree(ll _n) {
    n = 1;
    while (n < _n) { n *= 2; }
    dat = vector<T>(2 * n - 1, 0);
  }

  // void update(ll k, T a) {
  //   k += n - 1;
  //   dat[k] = a;
  //   while (k > 0) {
  //     k = (k - 1) / 2;
  //     dat[k] = dat[k * 2 + 1] + dat[k * 2 + 2];
  //   }
  // }

  void add(ll k, T a) {
    k += n - 1;
    dat[k] += a;
    while (k > 0) {
      k = (k - 1) / 2;
      dat[k] = dat[k * 2 + 1] + dat[k * 2 + 2];
    }
  }

  // Calculate the sum of [a, b)
  T query(ll a, ll b) {
    return _query(a, b, 0, 0, n);
  }

  // Calculate the sum of [a, b)
  // k is the index (dat[k]). This is matched to [l, r)
  T _query(ll a, ll b, ll k, ll l, ll r) {
    // The intersection of [a, b) and [r, l) is blank.
    if (r <= a || b <= l) { return 0; }

    if (a <= l && r <= b) {  // [r, l) is completely included in [a, b)
      return dat[k];
    } else {
      ll vl = _query(a, b, k * 2 + 1, l, (l + r) / 2);
      ll vr = _query(a, b, k * 2 + 2, (l + r) / 2, r);
      return vl + vr;
    }
  }

private:
  ll n; // The size of source data. The power of 2.
  vector<T> dat; // The data. The size if 2*n-1. The last n elements(dat[n..2*n-2]) are leaves(source data). The first n-1 elements are nodes.
};

// int main(int argc, char** argv) {
//   ll arr[] = { 1, 3, 2, 7, 9, 11 };
//   ll n = 6;
//
//   SegTree<ll> st(n);
//   rep(i, n) {
//     st.add(i, arr[i]);
//   }
//
//   cout << st.query(1, 5) << endl; // 21
//   cout << st.query(0, 4) << endl; // 13
//   cout << st.query(3, 5) << endl; // 16
//
//   st.add(4, 10);
//   cout << st.query(3, 5) << endl; // 26
// }


void solve() {
  ll n;
  cin >> n;
  vector<ll> a(n);
  rep(i, n) {
    cin >> a[i];
  }

  // Now, a[i] is defined.
  // h[i] = max_j(cnts[j] >= cnts[i]).
  // we use SegmentTree to store all occurences. But we ignore a[i] >= N.

  SegTree<ll> st(n + 5);

  // set<ll> st;
  ll h_index = 1; // The initial vaue. h_index is increasing.
  rep(i, n) {
    // We use i + 1 as the step for h-index.
    if (a[i] <= n) {
      st.add(a[i], 1);
    } else { // a[i] > n
      st.add(n, 1); // We treat larger number as n.
    }

    // Here, st.query(h_index, n+1) is the occurences of a[i] laerger than h_index.
    while(st.query(h_index, n+1) >= h_index) {
      ++h_index;
    }
    // Now, h_index is larger than valid value.
    cout << h_index - 1 << " ";
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll t;
  cin >> t;
  rep(i, t) {
    cout << "Case #"<<i+1<<": ";
    solve();
    cout << endl;
  }
}
