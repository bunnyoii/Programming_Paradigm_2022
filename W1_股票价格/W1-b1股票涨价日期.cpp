#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::vector;

const int MaxLimit = 100;
const int LowLimit = 30;
/*
题目要求:
给定一个整数数组 prices ，
表示连续几天的股票价格。返回一个数组answer，
其中 answer[i]是指对于第i天，股价下一次上涨是在几天后。
如果在这之后股价都不会上涨，请在该位置用0来代替。
*/

template <typename datatype>
class stock_price
{
private:
    datatype input_num;         //处理输入
    vector<datatype> answer;    //处理输出
    vector<datatype> prices;
public:
    stock_price() {
        input_num = 0;
    }
    void input_prices(vector<datatype>& prices);
    void select(vector<datatype> prices, vector<datatype>& answer);
};

/***************************************************************************
  函数名称：input_prices函数
  输入参数：vector<datatype>& prices
  功   能：处理输入
  返 回 值：0
 ***************************************************************************/
template <typename datatype>
void stock_price<datatype>::input_prices(vector<datatype>& prices)
{
    cout << "请输入连续几日的股票价格\n";
    while (1) {
        cin >> input_num;
        prices.emplace_back(input_num);
        if (cin.fail() || input_num < LowLimit || input_num > MaxLimit) {
            cin.clear();
            cin.ignore(65536, '\n');
            cout << "输入数据有误，请重新输入 (从头输入）\n";
            prices.clear();
        }
        else {
            if (cin.get() == '\n')
                break;
        }
    }
}

/***************************************************************************
  函数名称：select函数
  输入参数：vector<datatype> prices, vector<datatype>& answer
  功   能：判断下一次股票涨价的日期
  返 回 值：0
 ***************************************************************************/
template <typename datatype>
void stock_price<datatype>::select(vector<datatype> prices, vector<datatype>& answer)
{
    if (prices.empty())
        return;
    for (int i = 0; i < prices.size() - 1; i++) {
        for (int j = i + 1; j < prices.size(); j++) {
            if (prices[j] > prices[i]) {
                answer.insert(answer.begin() + i, j - i);
                break;
            }
            if (j == prices.size() - 1)
                answer.insert(answer.begin() + i, 0);
        }
    }
    answer.emplace_back(0);
}

/***************************************************************************
  函数名称：main函数
  输入参数：无
  返 回 值：0
 ***************************************************************************/
int main()
{
    vector<double> prices, answer;
    stock_price<double>prices_increase;
    prices_increase.input_prices(prices);
    prices_increase.select(prices, answer);
    cout << "连续几日的股票的最近涨价的日期差为\n";
    for (int i = 0; i < answer.size(); i++)
        cout << answer[i] << " ";
    return 0;
}

/* 测试数据：
case 1:
输入：73 74 76 85 89 32 '\n'
期望输出：1 1 1 1 0 0
案例作用：常规输入

case 2:
输入：30.5 98 45.5 90 54 '\n'
期望输出：1 0 1 0 0
案例作用：含有浮点数的输入

case 3:
输入：30 70.5 100 58.2 '\n'
期望输出：1 1 0 0
案例作用：边界情况

case 4:
输入：101 '\n'
期望输出：输入数据有误，请重新输入 (从头输入）
案例作用：超过最大上限（仅一个数据）

case 5:
输入：29 '\n'
期望输出：输入数据有误，请重新输入 (从头输入）
案例作用：低于最低下限（仅一个数据）

case 6:
输入：90 1000 87 76 99 100 '\n'
期望输出：输入数据有误，请重新输入 (从头输入）
案例作用：：超过最大上限

case 7:
输入：87 58 20 7 86 '\n'
期望输出：输入数据有误，请重新输入 (从头输入）
案例作用：低于最低下限

case 8:
输入：abc 89 78 100 '\n'
期望输出：输入数据有误，请重新输入 (从头输入）
案例作用：输入其他字符（含正确数字）

case 9:
输入： a .. ^ '\n'
期望输出：输入数据有误，请重新输入 (从头输入）
案例作用：输入其他字符

case 10:
输入：87 69 100 98 56 74 86 55
期望输出：2 1 0 0 1 1 0 0
案例作用：正常数据
*/