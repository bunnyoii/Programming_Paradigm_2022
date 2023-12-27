#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::vector;

const int MaxLimit = 100;
const int LowLimit = 30;
/*
��ĿҪ��:
����һ���������� prices �����е�prices[i]��ʾ��i��Ĺ�Ʊ�۸�
���һ���㷨����������������������Լ�������£�����Ծ����ܵ���ɸ���Ľ���(�������һ֧��Ʊ)��
������Ʊ�����޷��ڵڶ��������Ʊ(���䶳��Ϊ1��)��
ע��:�㲻��ͬʱ�����ʽ���(��������ٴι���ǰ���۵�֮ǰ�Ĺ�Ʊ)��
*/

template <typename datatype>
class stock_price
{
private:
    datatype input_num;         //��������
    datatype answer;            //�������
    vector<datatype> prices;
public:
    stock_price(datatype input_num = 0, datatype answer = 0) {;}
    void input_prices(vector<datatype>& prices);
    void MaxProfit(vector<datatype> prices, datatype& answer);
    datatype profit_max(datatype a, datatype b);
};

/***************************************************************************
  �������ƣ�input_prices����
  ���������vector<datatype>& prices
  ��   �ܣ���������
  �� �� ֵ��0
 ***************************************************************************/
template <typename datatype>
void stock_price<datatype>::input_prices(vector<datatype>& prices)
{
    cout << "�������������յĹ�Ʊ�۸�\n";
    while (1) {
        cin >> input_num;
        prices.emplace_back(input_num);
        if (cin.fail() || input_num < LowLimit || input_num > MaxLimit) {
            cin.clear();
            cin.ignore(65536, '\n');
            cout << "���������������������� (��ͷ���룩\n";
            prices.clear();
        }
        else {
            if (cin.get() == '\n')
                break;
        }
    }
}

/***************************************************************************
  �������ƣ�select����
  ���������vector<datatype> prices, vector<datatype>& answer
  ��   �ܣ��ж���һ�ι�Ʊ�Ǽ۵�����
  �� �� ֵ��0
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
  �������ƣ�profit_max����
  ���������datatype a, datatype b
  ��   �ܣ��Ƚ������Ĵ�С
  �� �� ֵ������a��b�еĽϴ���
 ***************************************************************************/
template <typename datatype>
datatype stock_price<datatype>::profit_max(datatype a, datatype b)
{
    return a > b ? a : b;
}

 /***************************************************************************
   �������ƣ�main����
   �����������
   �� �� ֵ��0
  ***************************************************************************/
int main()
{
    vector<double> prices;
    double answer = 0;
    stock_price<double>prices_increase;
    prices_increase.input_prices(prices);
    prices_increase.MaxProfit(prices, answer);
    cout << "�ɻ�ȡ���������\n" << answer << "\n";
}

/* �������ݣ�
case 1:
���룺73 74 76 85 89 32 '\n'
���������16
�������ã���������

case 2:
���룺30.5 98 45.5 90 54 '\n'
���������67.5
�������ã����и�����������

case 3:
���룺30 70.5 100 58.2 '\n'
���������70
�������ã��߽����

case 4:
���룺101 '\n'
������������������������������� (��ͷ���룩
�������ã�����������ޣ���һ�����ݣ�

case 5:
���룺29 '\n'
������������������������������� (��ͷ���룩
�������ã�����������ޣ���һ�����ݣ�

case 6:
���룺90 1000 87 76 99 100 '\n'
������������������������������� (��ͷ���룩
�������ã��������������

case 7:
���룺87 58 20 7 86 '\n'
������������������������������� (��ͷ���룩
�������ã������������

case 8:
���룺abc 89 78 100 '\n'
������������������������������� (��ͷ���룩
�������ã����������ַ�������ȷ���֣�

case 9:
���룺 a .. ^ '\n'
������������������������������� (��ͷ���룩
�������ã����������ַ�

case 10:
���룺87 69 100 98 56 74 86 55
���������61
�������ã���������
*/