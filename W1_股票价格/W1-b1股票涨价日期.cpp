#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::vector;

const int MaxLimit = 100;
const int LowLimit = 30;
/*
��ĿҪ��:
����һ���������� prices ��
��ʾ��������Ĺ�Ʊ�۸񡣷���һ������answer��
���� answer[i]��ָ���ڵ�i�죬�ɼ���һ���������ڼ����
�������֮��ɼ۶��������ǣ����ڸ�λ����0�����档
*/

template <typename datatype>
class stock_price
{
private:
    datatype input_num;         //��������
    vector<datatype> answer;    //�������
    vector<datatype> prices;
public:
    stock_price() {
        input_num = 0;
    }
    void input_prices(vector<datatype>& prices);
    void select(vector<datatype> prices, vector<datatype>& answer);
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
  �������ƣ�main����
  �����������
  �� �� ֵ��0
 ***************************************************************************/
int main()
{
    vector<double> prices, answer;
    stock_price<double>prices_increase;
    prices_increase.input_prices(prices);
    prices_increase.select(prices, answer);
    cout << "�������յĹ�Ʊ������Ǽ۵����ڲ�Ϊ\n";
    for (int i = 0; i < answer.size(); i++)
        cout << answer[i] << " ";
    return 0;
}

/* �������ݣ�
case 1:
���룺73 74 76 85 89 32 '\n'
���������1 1 1 1 0 0
�������ã���������

case 2:
���룺30.5 98 45.5 90 54 '\n'
���������1 0 1 0 0
�������ã����и�����������

case 3:
���룺30 70.5 100 58.2 '\n'
���������1 1 0 0
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
���������2 1 0 0 1 1 0 0
�������ã���������
*/