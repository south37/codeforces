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

const ll V = 5000000; // V > pow(2, 15) * n ~ 33,000 * 100 ~ 3,300,000
// const ll V = 100000;

vector<ll> lst(V); // Contains the information of sequences. last value of Trie-tree is a key, information is a value.
map<ll, ll> nxt[V]; // Trie-tree.
ll t = 1; // The counter. incremented in get_nxt.

ll n;

ll get_nxt(ll v, ll x) {
  if (!nxt[v].count(x)) {
    nxt[v][x] = t++;
  }
  // cout << "v: " << v << endl;
  // cout << "x: " << x << endl;
  // cout << "nxt[v][x]: " << nxt[v][x] << endl;
  return nxt[v][x];
}

void add(const vector<ll>& diff, ll x) {
  ll v = 0;
  for (auto i : diff) {
    v = get_nxt(v, i);
  }
  lst[v] = x;
}

// Return the diff of each elements with x in arr.
vector<ll> get_diff(const vector<ll>& arr, ll x) {
  vector<ll> cnt(n);
  rep(i, n) {
    cnt[i] = __builtin_popcountll(arr[i] ^ x); // The number of 1 bits.
  }
  vector<ll> diff(n-1);
  rep(i, n-1) {
    diff[i] = cnt[i+1]-cnt[0];
  }
  return diff;
}

ll try_find(const vector<ll>& diff) {
  ll v = 0;
  // Check the existence of diff in nxt. nxt contains the information of sequences.
  for (auto i : diff) {
    if (!nxt[v].count(i)) {
      return -1;
    }
    v = nxt[v][i];
  }
  return lst[v];
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> n;
  vector<ll> a(n);
  rep(i, n) {
    cin >> a[i];
  }
  // printvec(a);
  vector<ll> a1(n);
  vector<ll> a2(n);
  rep(i, n) {
    a1[i] = (a[i] >> 15); // The left 15 bit.
    a2[i] = a[i] ^ (a1[i] << 15); // The right 15 bit.
  }
  // printvec(a1);
  // printvec(a2);

  rep(i, 1<<15) {
    vector<ll> d = get_diff(a1, i);
    // cout << "i: " << i << endl;
    // printvec(d);
    // cout << "t: " << t << endl;
    // cout << "lst[t]: " << lst[t] << endl;
    add(d, i);
  }

  rep(i, 1<<15) {
    vector<ll> d = get_diff(a2, i);
    rep(j, n-1) {
      d[j] *= -1;
    }
    // cout << "i: " << i << endl;
    // printvec(d);

    ll x = try_find(d);
    // cout << "x: " << x << endl;
    // cout << "lst: "; printvec(lst);
    if (x != -1) {
      ll res = (x << 15) ^ i;
      cout << res << endl;
      return 0;
    }
  }

  cout << -1 << endl;
  return 0;
}
