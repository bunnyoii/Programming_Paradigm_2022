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
����һ����Ӱ�Ĳ���ʱ�䰲�ŵ�����intervals��
ÿ����Ӱ�Ĳ���ʱ�����俪ʼ�ͽ�����ʱ���ǣ�
��intervals[i] = [starti,endi]��
�뷵�ظ�ӰԺ��Ҫ�����ٷ�ӳ����������ȷ�����е�Ӱ���ܰ��ƻ���ӳ��
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
    //��������
    bool input_intervals();
    //Ѱ�����ٷ�ӳ������
    int min_meeting_rooms();
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
  �������ƣ�min_meeting_rooms����
  �����������
  ��   �ܣ��ж����ٷ�ӳ������
  �� �� ֵ��userooms
 ***************************************************************************/
template <typename datatype>
int movie_intervals<datatype>::min_meeting_rooms()
{
    /* �������starts��ends��vector���� */
    vector<datatype> starts(intervals.size(), 0);
    vector<datatype> ends(intervals.size(), 0);
    /* ��interval�����ڵĶ�Ӧ��ֹʱ�临�Ƶ��մ���������vector������ */
    for (unsigned int i = 0; i < intervals.size(); i++) {
        starts[i] = intervals[i].starti;
        ends[i] = intervals[i].endi;
    }
    /* ���� */
    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());
    int userooms = 0;
    auto startime = starts.begin();
    auto endtime = ends.begin();
    /* �ж�������Ҫ�ķ�ӳ������ */
    while (startime != starts.end()) {
        if (*startime >= *endtime) {
            userooms -= 1;
            endtime++;
        }
        userooms += 1;
        startime++;
    }
    return userooms;
}
/***************************************************************************
  �������ƣ�main����
  �����������
  �� �� ֵ��0
 ***************************************************************************/
int main()
{
    movie_intervals<double> watch_the_entire_movie;
    cout << "���������е�Ӱ����ֹʱ��:(���븺��������\n";
    while (!watch_the_entire_movie.input_intervals())
        continue;
    cout << watch_the_entire_movie.min_meeting_rooms();
    return 0;
}