#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

const int Starti_min = 0;
const int Endi_max = 1e6;
const int max_length = 1e4;
/*************************************************
��ĿҪ��
ĳӰԺΪ�����ṩ��һϵ�е�Ӱ�Ĳ���ʱ�䰲��intervals��
ÿ����Ӱ�Ĳ���ʱ�����俪ʼ�ͽ�����ʱ���ǣ�
��intervals[i] = [starti��endi]��
�����ж�һ�����Ƿ��ܹ������������ȫ����Ӱ��������κ�һ����
**************************************************/

/* ����һ���ṹ��洢��ֹʱ�� */
template <typename datatype>
class movie_intervals
{
private:
    struct start_to_end {
        datatype starti;                      //���������Ӱ��ʼʱ��
        datatype endi;                        //���������Ӱ����ʱ��
    }StE;
    vector<start_to_end> intervals;           //�����Ӱ����ʱ�䰲��
public:
    //���캯��
    movie_intervals() {
        StE.starti = 0;
        StE.endi = 0;
    };
    //��������ǩ
    bool input_intervals();
    //�Ƚ�ǰ��Ľ���ʱ��
    static bool min_to_max_endi(start_to_end a, start_to_end b) { return a.endi < b.endi; }
    //��������ǩ
    bool watch_them_all();
};

/***************************************************************************
  �������ƣ�input_intervals����
  �����������
  ��   �ܣ���������
  �� �� ֵ��true/false
 ***************************************************************************/
template <typename datatype>
bool movie_intervals<datatype>::input_intervals()
{
    /* ����һ���ַ����洢���� */
    string input_line;
    /* ��ȡ���� */
    getline(cin, input_line);
    istringstream iss(input_line);
    while (true) {
        /* ��ʼ���Ա��жϷǷ����� */
        StE.starti = -1;
        StE.endi = -1;
        iss >> StE.starti >> StE.endi;
        intervals.push_back(StE);
        if (iss.fail() || StE.starti < Starti_min || StE.endi > Endi_max || StE.starti >= StE.endi
            || StE.starti == -1 || StE.endi == -1) {//�Ƿ�����/����������/starti��endi/ֻ������������
            cout << "�������ݷǷ������������루��ͷ���룩\n";
            iss.str("");
            iss.clear();
            iss.ignore(65536, '\n');
            intervals.clear();
            return false;
        }
        if (iss.eof() || intervals.size() >= max_length) {
            break;
        }
    }
}

/***************************************************************************
  �������ƣ�watch_them_all����
  �����������
  ��   �ܣ��ж�һ�����Ƿ��ܿ���ȫ����Ӱ
  �� �� ֵ��true�����䲻�غϸ������ڵ�Ӱ�ܲ������ܿ���ȫ����Ӱ
           false�����䲻�غϸ��������ڵ�Ӱ�ܲ��������ܿ���ȫ����Ӱ
 ***************************************************************************/
template <typename datatype>
bool movie_intervals<datatype>::watch_them_all()
{
    /* ��interval�����ڵ�endiʱ���С�������� */
    sort(intervals.begin(), intervals.end(), min_to_max_endi);
    int ans = 1;//�������䲻�غϵĸ���
    datatype endtime = intervals[0].endi;
    for (unsigned int i = 1; i < intervals.size(); i++) {
        if (intervals[i].starti >= endtime) {
            endtime = intervals[i].endi;
            ans++;
        }
    }
    return ans == intervals.size() ? true : false;
}
/***************************************************************************
  �������ƣ�main����
  �����������
  �� �� ֵ��0
 ***************************************************************************/
int main()
{
    movie_intervals<double> watch_the_entire_movie;
    cout << "���������е�Ӱ����ֹʱ��:\n";
    while (!watch_the_entire_movie.input_intervals())
        continue;
    if (watch_the_entire_movie.watch_them_all())
        cout << "true\n";
    else
        cout << "false\n";
    return 0;
}