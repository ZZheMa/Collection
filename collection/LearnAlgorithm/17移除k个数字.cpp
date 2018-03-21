#include <iostream>
#include <string>
#include <list>
#include <cassert>

// 402. Remove K Digits

// ̰��˼�롣�����λ��ʼ��һ����һ������ѹջ��ֻҪ��λ�����ȴθ�λ����С��
// ��ô��˵����ǰ������С�������λ�����ȴθ�λ�Ĵ���ô����λ�Ĵ�����Ƴ�����
// ����ʹ����С��
std::string removeKdigits(const std::string& num, int k) {
  std::list<char> min_number;

  if (num.empty()) {
    return "0";
  }

  for (char digit : num) {
    // ������ջ����Ԫ��(Ҳ���ǵ�ǰ��λ����)�ͽ�Ҫѹջ�������бȽϡ�
    // �ӵ�һλ�Ϳ�ʼ�����Ƚϣ��������յ�ÿһλ�Ľ�����Ƿ��������ġ�
    while (!min_number.empty() && k > 0) {
      // ���ջ�е�������λ���������ڽ�Ҫ��ջ��������ô��λ������ջ��
      // ʼ�ձ��ָ�λ����ʹ��С�ľͿ����ˡ�
      if (min_number.back() > digit) {
        min_number.pop_back();
        --k;
      } else {
        break;
      }
    }

    if (min_number.empty() && digit == '0') {
      continue;
    }

    min_number.push_back(digit);
  }

  while (k > 0 && !min_number.empty()) {
    min_number.pop_back();
    --k;
  }

  std::string min_number_str;
  for (char min_digit : min_number) {
    min_number_str.push_back(min_digit);
  }

  if (min_number.empty()) {
    return "0";
  }

  return min_number_str;
}

int main() {
  std::cout << removeKdigits("54321", 1) << std::endl;
  std::cout << removeKdigits("12345", 1) << std::endl;
  std::cout << removeKdigits("16543", 1) << std::endl;
  std::cout << removeKdigits("1", 1) << std::endl;

  std::cout << removeKdigits("54321", 2) << std::endl;
  std::cout << removeKdigits("12345", 2) << std::endl;
  std::cout << removeKdigits("16543", 2) << std::endl;

  std::cout << removeKdigits("165436", 3) << std::endl;

  std::cout << removeKdigits("10001", 1) << std::endl;
  std::cout << removeKdigits("10001", 3) << std::endl;
  std::cout << removeKdigits("10000", 3) << std::endl;

  return 0;
}
