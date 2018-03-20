#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <cassert>

// 455. Assign Cookies

// ̰���㷨����þֲ����Ž⡣
int findContentChildren(std::vector<int>& g, std::vector<int>& s) {
  // ��������������
  std::sort(g.begin(), g.end());
  std::sort(s.begin(), s.end());

  std::size_t greed_len = g.size();
  std::size_t cookie_len = s.size();
  std::size_t greed_pos = 0;
  std::size_t cookie_pos = 0;

  while (greed_pos < greed_len && cookie_pos < cookie_len) {
    // ÿ�����Ӷ���øոպ��������ǵ��ǹ���Ȼ�������ǹ����������������ĺ��ӡ�
    // �Ӷ�����ɴ��ǹ����˷ѡ�������ǹ���������С�ĺ��ӣ���ô��ֻʣ��С���ǹ���
    // ��С���ǹ����������������ĺ��ӡ�
    if (g[greed_pos] <= s[cookie_pos]) {
      ++greed_pos;
    }
    ++cookie_pos;
  }

  return greed_pos;
}

int main() {
  std::vector<int> g = { 2, 4, 5 };
  std::vector<int> s = { 1, 7, 2, 6, 3 };

  std::cout << findContentChildren(g, s) << std::endl;

  return 0;
}
