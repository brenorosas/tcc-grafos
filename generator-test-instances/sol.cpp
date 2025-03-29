#include <bits/stdc++.h>
using namespace std;

signed main() {
  int n;
  cin >> n;

  int mat[105][105];
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> mat[i][j];

  int harry_row, ron_column;
  cin >> harry_row >> ron_column;

  assert(harry_row < n);
  assert(ron_column < n);

  int harry_points = 0;
  for (int j = 0; j < n; ++j)
    harry_points += mat[harry_row][j];

  int ron_points = 0;
  for (int i = 0; i < n; ++i)
    ron_points += mat[i][ron_column];

  if (ron_column < harry_row)
    ron_points -= mat[harry_row][ron_column];
  else
    harry_points -= mat[harry_row][ron_column];

  cout << "Harry " << harry_points << endl;
  cout << "Ron " << ron_points << endl;
}
