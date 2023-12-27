#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

const int min_num = (int)-1e9;
const int max_num = (int)1e9;
const int max_length = (int)1e5;
/*************************************************
����һ����������nums����������indexDiff��valueDiff��
�ҳ��Ƿ���������������±�(i��i):
i != j
abs (i - j)<= indexDiff
abs (nums [ i] - nums[j])<= valueDiff
������ڣ�����true;���򣬷���false��
**************************************************/

/* ����һ���ṹ���Ž������ */
template <typename datatype>
class find_duplicate_elements
{
private:
    vector<datatype> nums;           //�����Ӱ����ʱ�䰲��
    datatype inum;
    datatype indexDiff;
    datatype valueDiff;
public:
    //���캯��
    find_duplicate_elements() {
        inum = 0;
        indexDiff = 0;
        valueDiff = 0;
    }
    //��������ǩ
    bool input_nums();
    void input_int();
    //��������ǩ
    bool contains_nearby_almost_duplicate();
};

/***************************************************************************
  �������ƣ�input_nums����
  �����������
  ��   �ܣ��������������
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
  �������ƣ�input_int����
  �����������
  ��   �ܣ�������������
  �� �� ֵ����
 ***************************************************************************/
template <typename datatype>
void find_duplicate_elements<datatype>::input_int()
{
    while (1) {
        cin >> indexDiff >> valueDiff;
        if (cin.fail() || indexDiff < 1 || indexDiff > max_length || valueDiff < 0 || valueDiff > max_num) {
            cin.clear();
            cin.ignore(65536, '\n');
            cout << "����������������������\n";
        }
        else {
            if (cin.get() == '\n')
                break;
        }
    }
}
/***************************************************************************
  �������ƣ�contains_nearby_almost_duplicate����
  �����������
  ��   �ܣ��ڸ���������ж��������Ƿ��о���ֵ��Ϊ����ֵ��������
  �� �� ֵ��true/false
 ***************************************************************************/
template <typename datatype>
bool find_duplicate_elements<datatype>::contains_nearby_almost_duplicate()
{
    for (unsigned int i = 0; i < nums.size(); i++) {
        for (unsigned int j = i + 1; j < i + indexDiff + 1 && j < nums.size(); j++) {
            if (abs(nums[i] - nums[j]) <= valueDiff)
                return true;
        }
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
    cout << "�������±��indexDiff����ֵ��valueDiff:\n";
    appear_twice_arbitrarily.input_int();
    if (appear_twice_arbitrarily.contains_nearby_almost_duplicate())
        cout << "true\n";
    else
        cout << "false\n";
    return 0;
}