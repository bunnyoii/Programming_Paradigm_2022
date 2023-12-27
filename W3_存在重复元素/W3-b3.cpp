#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

const int min_num = (int)-1e9;
const int max_num = (int)1e9;
const int max_length = (int)1e5;
/*************************************************
给你一个整数数组nums和两个整数indexDiff和valueDiff。
找出是否存在这样的两个下标(i，i):
i != j
abs (i - j)<= indexDiff
abs (nums [ i] - nums[j])<= valueDiff
如果存在，返回true;否则，返回false。
**************************************************/

/* 建立一个结构体存放解决方案 */
template <typename datatype>
class find_duplicate_elements
{
private:
    vector<datatype> nums;           //定义电影播放时间安排
    datatype inum;
    datatype indexDiff;
    datatype valueDiff;
public:
    //构造函数
    find_duplicate_elements() {
        inum = 0;
        indexDiff = 0;
        valueDiff = 0;
    }
    //见函数标签
    bool input_nums();
    void input_int();
    //见函数标签
    bool contains_nearby_almost_duplicate();
};

/***************************************************************************
  函数名称：input_nums函数
  输入参数：无
  功   能：处理数组的输入
  返 回 值：true/false
 ***************************************************************************/
template <typename datatype>
bool find_duplicate_elements<datatype>::input_nums()
{
    /* 创建一个字符串存储输入 */
    string input_line;
    /* 获取输入 */
    getline(cin, input_line);
    istringstream iss(input_line);
    while (true) {
        /* 初始化以便判断非法输入 */
        iss >> inum;
        nums.push_back(inum);
        if (iss.fail() || inum < min_num || inum > max_num) {//非法输入/超过上下限
            cout << "输入数据非法，请重新输入（从头输入）\n";
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
  函数名称：input_int函数
  输入参数：无
  功   能：处理区间输入
  返 回 值：无
 ***************************************************************************/
template <typename datatype>
void find_duplicate_elements<datatype>::input_int()
{
    while (1) {
        cin >> indexDiff >> valueDiff;
        if (cin.fail() || indexDiff < 1 || indexDiff > max_length || valueDiff < 0 || valueDiff > max_num) {
            cin.clear();
            cin.ignore(65536, '\n');
            cout << "输入数据有误，请重新输入\n";
        }
        else {
            if (cin.get() == '\n')
                break;
        }
    }
}
/***************************************************************************
  函数名称：contains_nearby_almost_duplicate函数
  输入参数：无
  功   能：在给定区间里，判断数组里是否有绝对值差为给定值的两个数
  返 回 值：true/false
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
  函数名称：main函数
  输入参数：无
  返 回 值：0
 ***************************************************************************/
int main()
{
    find_duplicate_elements<int> appear_twice_arbitrarily;
    cout << "请输入整数数组:\n";
    while (!appear_twice_arbitrarily.input_nums())
        continue;
    cout << "请输入下标差indexDiff和数值差valueDiff:\n";
    appear_twice_arbitrarily.input_int();
    if (appear_twice_arbitrarily.contains_nearby_almost_duplicate())
        cout << "true\n";
    else
        cout << "false\n";
    return 0;
}