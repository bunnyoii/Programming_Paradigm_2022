#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

const unsigned int Starti_min = 0;
const int Endi_max = 1e4;
const unsigned int max_length = 1e4;
/*************************************************
��ĿҪ��
ӰԺΪ�����ṩ��һϵ�е�Ӱ�Ĳ���ʱ�䰲��intervals��
����ÿ����Ӱ�Ĳ���ʱ�����俪ʼ�ͽ�����ʱ���ǣ�
��intervals[i] = [starti��endi]��
���ڲ��ֵ�Ӱ���ص��Ĳ���ʱ�䣬ӰԺ�����ϲ���Щʱ�䣬
���ṩһ���µĲ���ʱ�������ϲ������ص��Ĳ���ʱ�䣬
������һ�����ص��Ĳ���ʱ�����飬
��������ǡ�ø��������е�����ʱ�䡣
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
    vector<start_to_end> merge;               //����ϲ���ĵ�Ӱ����ʱ�䰲��
public:
    //���캯��
    movie_intervals() {
        StE.starti = 0;
        StE.endi = 0;
    };
    //�õ�˽�г�Աvector<start_to_end> merge;
    const vector<start_to_end>& get_merge() const { return merge; }
    bool input_intervals();
    void merge_intervals();
    datatype max(datatype a, datatype b) { return a > b ? a : b; }

    /*��Ԫ��������-����<<*/
    friend ostream& operator<<(ostream& out, const vector<start_to_end>& merge)
    {
        if (merge.empty()) {
            out << "vectorΪ�գ�\n";
        }
        else {
            out << "[";
            for (unsigned int count = 0; count < merge.size(); count++) {
                out << "[" << merge[count].starti << "," << merge[count].endi << "]";
                if (count != merge.size() - 1) {
                    out << ", ";
                }
            }
            out << "]";
        }
        return out;
    }
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
  �������ƣ�merge_intervals����
  �����������
  ��   �ܣ��ϲ��ص�ʱ������
  �� �� ֵ����
 ***************************************************************************/
template <typename datatype>
void movie_intervals<datatype>::merge_intervals()
{
    //�����ṹ��
    start_to_end merge_ste;
    //�Ӵ�С����intervals�ڵĿ�ʼʱ��
    sort(intervals.begin(), intervals.end(), [](const start_to_end& a, const start_to_end& b) {
        return a.starti < b.starti;
        });
    //����ϲ�
    for (unsigned int i = 0; i < intervals.size();) {
        datatype temp = intervals[i].endi;
        unsigned int j = i + 1;
        while (j < intervals.size() && intervals[i].starti <= temp) {
            temp = max(temp, intervals[j].endi);
            j++;
        }
        merge_ste.starti = intervals[i].starti;
        merge_ste.endi = temp;
        merge.push_back(merge_ste);
        i = j;
    }
}

/***************************************************************************
  �������ƣ�main����
  �����������
  �� �� ֵ��0
 ***************************************************************************/
int main()
{
    movie_intervals<double> watch_the_entire_movie;
    cout << "���������е�Ӱ����ֹʱ�䣺\n";
    while (!watch_the_entire_movie.input_intervals())
        continue;
    watch_the_entire_movie.merge_intervals();
    cout << watch_the_entire_movie.get_merge();
    return 0;
}