#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::vector;

const int MaxLimit = 100;
const int LowLimit = 30;
/*
题目要求:
给定一个整数数组 prices ，其中第prices[i]表示第i天的股票价格。
设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易(多次买卖一支股票)∶
卖出股票后，你无法在第二天买入股票(即冷冻期为1天)。
注意:你不能同时参与多笔交易(你必须在再次购买前出售掉之前的股票)。
*/

template <typename datatype>
class stock_price
{
private:
    datatype input_num;         //处理输入
    datatype answer;            //处理输出
    vector<datatype> prices;
public:
    stock_price(datatype input_num = 0, datatype answer = 0) {;}
    void input_prices(vector<datatype>& prices);
    void MaxProfit(vector<datatype> prices, datatype& answer);
    datatype profit_max(datatype a, datatype b);
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
void stock_price<datatype>::MaxProfit(vector<datatype> prices, datatype& answer)
{
    if (prices.empty())
        return;
    datatype f0 = -prices[0], f1 = 0, f2 = 0;
    for (int i = 1; i < prices.size(); i++) {
        datatype new_f0 = profit_max(f0, f2 - prices[i]);
        datatype new_f1 = f0 + prices[i];
        datatype new_f2 = profit_max(f1, f2);
        f0 = new_f0;
        f1 = new_f1;
        f2 = new_f2;
    }
    answer = profit_max(f1, f2);
}

/***************************************************************************
  函数名称：profit_max函数
  输入参数：datatype a, datatype b
  功   能：比较两数的大小
  返 回 值：返回a、b中的较大数
 ***************************************************************************/
template <typename datatype>
datatype stock_price<datatype>::profit_max(datatype a, datatype b)
{
    return a > b ? a : b;
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
输入： a .. ^ '\n'
期望输出：输入数据有误，请重新输入 (从头输入）
案例作用：输入其他字符

case 10:
输入：87 69 100 98 56 74 86 55
期望输出：61
案例作用：正常数据
*/