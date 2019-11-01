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

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

ll gcd(ll a, ll b) {
  if (a < b) { swap(a, b); }
  if (b == 0) { return a; }
  return gcd(b, a % b);
}

void solve() {
  ll a, b;
  cin >> a >> b;
  if ((a == 1) || (b == 1)) {
    cout << "Finite" << endl;
    return;
  }

  // Here, a > 1 and b > 1.
  // We want to check the prime ness of a and b
  ll g = gcd(a, b);
  if (g > 1) { // there are numbers which is not represetatable.
    cout << "Infinite" << endl;
    return;
  } else { // g == 1
    cout << "Finite" << endl;
    return;
  }
}

int main(int argc, char** argv) {
  ll t;
  cin >> t;
  rep(i, t) {
    solve();
  }
}
