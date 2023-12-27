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
给你一个整数数组nums。
如果任意一值在数组中出现至少两次，返回true;
如果数组中每个值仅出现一次，返回false 。
**************************************************/

/* 建立一个结构体存放解决方案 */
template <typename datatype>
class find_duplicate_elements
{
private:
    vector<datatype> nums;           //定义电影播放时间安排
    datatype inum;
public:
    //构造函数
    find_duplicate_elements() {
        inum = 0;
    }
    //见函数标签
    bool input_nums();
    //见函数标签
    bool appear_twice_least();
};

/***************************************************************************
  函数名称：input_nums函数
  输入参数：无
  功   能：处理输入
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
  函数名称：appear_twice_least函数
  输入参数：无
  功   能：判断数组里是否有重复元素
  返 回 值：true：至少有一个元素重复了两次或以上
           false：所有元素均不重复
 ***************************************************************************/
template <typename datatype>
bool find_duplicate_elements<datatype>::appear_twice_least()
{
    //创建一个unordered_set容器用于标记
    unordered_set<datatype> sort_num;
    //遍历比较前一个的结束时间和后一个的开始时间
    for (int x : nums) {
        if (sort_num.find(x) != sort_num.end())
            return true;
        sort_num.insert(x);
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
    if (appear_twice_arbitrarily.appear_twice_least())
        cout << "true\n";
    else
        cout << "false\n";
    return 0;
}