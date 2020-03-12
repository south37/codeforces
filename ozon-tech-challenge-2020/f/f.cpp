#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
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

void add_prime(set<ll>& pf, ll num) {
  for (ll i = 2; i*i <= num; ++i) {
    if (num % i == 0) {
      while (num % i == 0) {
        num /= i;
      }
      pf.insert(i);
    }
  }
  if (num > 1) {
    pf.insert(num);
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> a(n);
  vector<ll> per; // the random number container
  rep(i, n) {
    cin >> a[i];
    per.push_back(i);
  }

  // shuffle per
  mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
  shuffle(all(per), mt);

  set<ll> pf; // prime factors
  rep(i, min(100ll, n)) {
    ll aa = a[per[i]];
    add_prime(pf, aa);
    add_prime(pf, aa+1);
    if (aa > 1) {
      add_prime(pf, aa-1);
    }
  }

  // Debug
  while (!pf.empty()) {
    cout << *pf.begin() << endl;
    pf.erase(pf.begin());
  }
}
