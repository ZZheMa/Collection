#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

// 51. N-Queens

// ʹ��std::vector<std::vector<int>> chessboard������������б�������λ��Ϊ1��û�б�������λ��Ϊ0��

// ���ʺ�ŵ�(x,y)���ұ�������еĹ���λ�á�
void MarkAttackPosition(int x, int y, std::vector<std::vector<int>>& chessboard) {
  // (x,y)�������������б�Խǰ˸��㣬�����x��ƫ��������X,Y��= N(dx,dy) + (x,y)
  static const int N = 8;
  static const int dx[N] = { -1, 1, 0, 0, -1, -1, 1, 1 };
  static const int dy[N] = { 0, 0, -1, 1, -1, 1, -1, 1 };

  const int kChessboardLen = chessboard.size();

  for (int i = 0; i < kChessboardLen; i++) {
    for (int j = 0; j < N; j++) {
      int temp_x = x + i * dx[j];
      int temp_y = y + i * dy[j];

      if (temp_x < 0 || temp_y < 0 || temp_x >= kChessboardLen || temp_y >= kChessboardLen) {
        continue;
      }

      chessboard[temp_x][temp_y] = 1;
    }
  }
}

// ���ݷ���������ʵ������һ���������һ��״̬���Ĺ��̣�ֻ����������Ǳ���ǰԤ�Ƚ����ģ����������ڱ����Ĺ����С�
// ���Խ�������Ĺؼ������ҵ��������Ȼ����Ŀת��Ϊ�������Ĺ��̡�

// i �����У�j�����С�һ��һ�е�ȥ��ֵ�����ȷ����ڵ�һ�У�Ȼ�����γ��Է���ÿһ�У�����һ�������к��������һ�С�����չ����һ������
void PlaceQueen(int i, int n,
                std::vector<std::vector<int>>& chessboard,
                std::vector<std::string>& subset,
                std::vector<std::vector<std::string>>& subsets) {
  if (i >= n) {
    subsets.push_back(subset);
    return;
  }

  for (int j = 0; j < n; ++j) {
    if (chessboard[i][j] == 1) {
      continue;
    }

    // ���Է���(i, j)��
    MarkAttackPosition(i, j, chessboard);
    subset[i][j] = 'Q';

    std::vector<std::vector<int>> backup_chessboard = chessboard;

    PlaceQueen(i + 1, n, chessboard, subset, subsets);

    // �����������Է���(i, j+1)���λ�ã�����Ҫ�ָ���֮ǰ��״̬��
    subset[i][j] = '.';
    chessboard = backup_chessboard;
  }
}

std::vector<std::vector<std::string>> solveNQueens(int n) {
  std::vector<std::vector<std::string>> subsets;
  std::vector<std::string> subset(n, std::string(n, '.'));
  std::vector<std::vector<int>> chessboard(n, std::vector<int>(n, 0));

  PlaceQueen(0, n, chessboard, subset, subsets);

  return subsets;
}

void PrintChessboard(const std::vector<std::vector<int>>& chessboard) {
  for (const auto& line : chessboard) {
    for (auto i : line) {
      std::cout << i;
    }
    std::cout << std::endl;
  }
}

void PrintSubsets(const std::vector<std::vector<std::string>>& subsets) {
  for (const auto& subset : subsets) {
    for (const auto& line : subset) {
      std::cout << line << std::endl;
    }

    std::cout << "------------------------" << std::endl;
  }
}

int main() {
  PrintSubsets(solveNQueens(8));

  return 0;
}
