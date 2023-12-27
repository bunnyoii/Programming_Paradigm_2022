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
某影院为观众提供了一系列电影的播放时间安排intervals，
每部电影的播放时间由其开始和结束的时间标记，
即intervals[i] = [starti，endi]。
请你判断一个人是否能够看完这里面的全部电影，不错过任何一部。
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
    //见函数标签
    bool input_intervals();
    //比较前后的结束时间
    static bool min_to_max_endi(start_to_end a, start_to_end b) { return a.endi < b.endi; }
    //见函数标签
    bool watch_them_all();
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
  函数名称：watch_them_all函数
  输入参数：无
  功   能：判断一个人是否能看完全部电影
  返 回 值：true：区间不重合个数等于电影总部数，能看完全部电影
           false：区间不重合个数不等于电影总部数，不能看完全部电影
 ***************************************************************************/
template <typename datatype>
bool movie_intervals<datatype>::watch_them_all()
{
    /* 将interval容器内的endi时间从小到大排序 */
    sort(intervals.begin(), intervals.end(), min_to_max_endi);
    int ans = 1;//计算区间不重合的个数
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
  函数名称：main函数
  输入参数：无
  返 回 值：0
 ***************************************************************************/
int main()
{
    movie_intervals<double> watch_the_entire_movie;
    cout << "请输入所有电影的起止时间:\n";
    while (!watch_the_entire_movie.input_intervals())
        continue;
    if (watch_the_entire_movie.watch_them_all())
        cout << "true\n";
    else
        cout << "false\n";
    return 0;
}