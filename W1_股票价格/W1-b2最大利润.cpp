#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::vector;

const int MaxLimit = 100;
const int LowLimit = 30;

/*
题目要求:
给定一个数组 prices ，它的第i个元素 prices[i]表示一支给定股票第i天的价格。
你只能选择某一天买入这只股票，并选择在未来的某一个不同的日子卖出该股票。设计一个算法来计算你所能获取的最大利润。
返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回0。
注：卖出价格需要大于买入价格;同时，你不能在买入前卖出股（如果股票价格最大是第一天）。
*/

template <typename datatype>
class stock_price
{
private:
    datatype input_num;         //处理输入
    datatype answer;            //处理输出
    vector<datatype> prices;
public:
    stock_price() {
        input_num = 0;
        answer = 0;
    }
    void input_prices(vector<datatype>& prices);
    void MaxProfit(vector<datatype> prices, datatype& answer);
};

/***************************************************************************
  函数名称：input_prices函数
  输入参数：vector<datatype>& prices
  功   能：处理输入
  返 回 值：0
 ***************************************************************************/
template <typename datatype>
void stock_price<datatype> ::input_prices(vector<datatype>& prices)
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
  函数名称：MaxProfit函数
  输入参数：vector<datatype> prices, datatype& answer
  功   能：计算能获得的最大利润
  返 回 值：0
 ***************************************************************************/
template <typename datatype>
void stock_price<datatype>::MaxProfit(vector<datatype> prices, datatype& answer)
{
    if (prices.empty())
        return;
    datatype max_price = 0, min_price = prices[0];
    datatype max_num = 0, min_num = 0;
    for (int i = 1; i < prices.size(); i++) {
        if (prices[i] < min_price) {
            min_price = prices[i];
        }
        else if (prices[i] - min_price > answer) {
            answer = prices[i] - min_price;
        }
    }
}

/***************************************************************************
  函数名称：main函数
  输入参数：无
  返 回 值：0
 ***************************************************************************/
int main()
{
    vector<double> prices;
    double answer = 0;
    stock_price<double>prices_increase;
    prices_increase.input_prices(prices);
    prices_increase.MaxProfit(prices, answer);
    cout << "可获取的最大利润\n" << answer << "\n";
}

/* 测试数据：
case 1:
输入：73 74 76 85 89 32 '\n'
期望输出：16
案例作用：常规输入

case 2:
输入：30.5 98 45.5 90 54 '\n'
期望输出：67.5
案例作用：含有浮点数的输入

case 3:
输入：30 70.5 100 58.2 '\n'
期望输出：70
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
输入： 40 60 30
期望输出：20
案例作用：测试是否满足股票买入卖出的时间顺序

case 10:
输入：87 69 100 98 56 74 86 55
期望输出：31
案例作用：正常数据
*/