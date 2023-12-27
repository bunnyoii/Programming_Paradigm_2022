#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>

using namespace std;

const int min_num = (int)-1e9;
const int max_num = (int)1e9;
const int max_length = (int)1e5;
/*************************************************
����һ����������nums��
�������һֵ�������г����������Σ�����true;
���������ÿ��ֵ������һ�Σ�����false ��
**************************************************/

/* ����һ���ṹ���Ž������ */
template <typename datatype>
class find_duplicate_elements
{
private:
    vector<datatype> nums;           //�����Ӱ����ʱ�䰲��
    datatype inum;
public:
    //���캯��
    find_duplicate_elements() {
        inum = 0;
    }
    //��������ǩ
    bool input_nums();
    //��������ǩ
    bool appear_twice_least();
};

/***************************************************************************
  �������ƣ�input_nums����
  �����������
  ��   �ܣ���������
  �� �� ֵ��true/false
 ***************************************************************************/
template <typename datatype>
bool find_duplicate_elements<datatype>::input_nums()
{
    /* ����һ���ַ����洢���� */
    string input_line;
    /* ��ȡ���� */
    getline(cin, input_line);
    istringstream iss(input_line);
    while (true) {
        /* ��ʼ���Ա��жϷǷ����� */
        iss >> inum;
        nums.push_back(inum);
        if (iss.fail() || inum < min_num || inum > max_num) {//�Ƿ�����/����������
            cout << "�������ݷǷ������������루��ͷ���룩\n";
            iss.str("");
            iss.clear();
            iss.ignore(65536, '\n');
            nums.clear();
            return false;
        }
        if (iss.eof() || nums.size() >= max_length) {
            break;
        }
    }
    return true;
}

/***************************************************************************
  �������ƣ�appear_twice_least����
  �����������
  ��   �ܣ��ж��������Ƿ����ظ�Ԫ��
  �� �� ֵ��true��������һ��Ԫ���ظ������λ�����
           false������Ԫ�ؾ����ظ�
 ***************************************************************************/
template <typename datatype>
bool find_duplicate_elements<datatype>::appear_twice_least()
{
    //����һ��unordered_set�������ڱ��
    unordered_set<datatype> sort_num;
    //�����Ƚ�ǰһ���Ľ���ʱ��ͺ�һ���Ŀ�ʼʱ��
    for (int x : nums) {
        if (sort_num.find(x) != sort_num.end())
            return true;
        sort_num.insert(x);
    }
    return false;
}
/***************************************************************************
  �������ƣ�main����
  �����������
  �� �� ֵ��0
 ***************************************************************************/
int main()
{
    find_duplicate_elements<int> appear_twice_arbitrarily;
    cout << "��������������:\n";
    while (!appear_twice_arbitrarily.input_nums())
        continue;
    if (appear_twice_arbitrarily.appear_twice_least())
        cout << "true\n";
    else
        cout << "false\n";
    return 0;
}