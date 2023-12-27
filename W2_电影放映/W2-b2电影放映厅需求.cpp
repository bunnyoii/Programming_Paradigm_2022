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
题目要求：
给你一个电影的播放时间安排的数组intervals，
每部电影的播放时间由其开始和结束的时间标记，
即intervals[i] = [starti,endi]。
请返回该影院需要的最少放映厅数量，以确保所有电影都能按计划放映。
**************************************************/

/* 建立一个结构体存储起止时间 */
template <typename datatype>
class movie_intervals
{
private:
    struct start_to_end {
        datatype starti;                      //处理输入电影开始时间
        datatype endi;                        //处理输入电影结束时间
    }StE;
    vector<start_to_end> intervals;           //定义电影播放时间安排
public:
    //构造函数
    movie_intervals() {
        StE.starti = 0;
        StE.endi = 0;
    };
    //处理输入
    bool input_intervals();
    //寻找最少放映厅数量
    int min_meeting_rooms();
};

/***************************************************************************
  函数名称：input_intervals函数
  输入参数：无
  功   能：处理输入
  返 回 值：true/false
 ***************************************************************************/
template <typename datatype>
bool movie_intervals<datatype>::input_intervals()
{
    /* 创建一个字符串存储输入 */
    string input_line;
    /* 获取输入 */
    getline(cin, input_line);
    istringstream iss(input_line);
    while (true) {
        /* 初始化以便判断非法输入 */
        StE.starti = -1;
        StE.endi = -1;
        iss >> StE.starti >> StE.endi;
        intervals.push_back(StE);
        if (iss.fail() || StE.starti < Starti_min || StE.endi > Endi_max || StE.starti >= StE.endi
            || StE.starti == -1 || StE.endi == -1) {//非法输入/超过上下限/starti≥endi/只输入奇数个数
            cout << "输入数据非法，请重新输入（从头输入）\n";
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
  函数名称：min_meeting_rooms函数
  输入参数：无
  功   能：判断最少放映厅数量
  返 回 值：userooms
 ***************************************************************************/
template <typename datatype>
int movie_intervals<datatype>::min_meeting_rooms()
{
    /* 创建存放starts和ends的vector容器 */
    vector<datatype> starts(intervals.size(), 0);
    vector<datatype> ends(intervals.size(), 0);
    /* 将interval容器内的对应起止时间复制到刚创建的两个vector容器里 */
    for (unsigned int i = 0; i < intervals.size(); i++) {
        starts[i] = intervals[i].starti;
        ends[i] = intervals[i].endi;
    }
    /* 排序 */
    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());
    int userooms = 0;
    auto startime = starts.begin();
    auto endtime = ends.begin();
    /* 判断最少需要的放映厅数量 */
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
  函数名称：main函数
  输入参数：无
  返 回 值：0
 ***************************************************************************/
int main()
{
    movie_intervals<double> watch_the_entire_movie;
    cout << "请输入所有电影的起止时间:(输入负数结束）\n";
    while (!watch_the_entire_movie.input_intervals())
        continue;
    cout << watch_the_entire_movie.min_meeting_rooms();
    return 0;
}