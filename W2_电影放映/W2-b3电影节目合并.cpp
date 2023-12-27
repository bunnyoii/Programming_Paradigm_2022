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
题目要求：
影院为观众提供了一系列电影的播放时间安排intervals，
其中每部电影的播放时间由其开始和结束的时间标记，
即intervals[i] = [starti，endi]。
由于部分电影有重叠的播放时间，影院决定合并这些时间，
以提供一个新的播放时间表。请你合并所有重叠的播放时间，
并返回一个不重叠的播放时间数组，
该数组需恰好覆盖输入中的所有时间。
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
    vector<start_to_end> merge;               //定义合并后的电影播放时间安排
public:
    //构造函数
    movie_intervals() {
        StE.starti = 0;
        StE.endi = 0;
    };
    //得到私有成员vector<start_to_end> merge;
    const vector<start_to_end>& get_merge() const { return merge; }
    bool input_intervals();
    void merge_intervals();
    datatype max(datatype a, datatype b) { return a > b ? a : b; }

    /*友元函数声明-重载<<*/
    friend ostream& operator<<(ostream& out, const vector<start_to_end>& merge)
    {
        if (merge.empty()) {
            out << "vector为空！\n";
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
  函数名称：merge_intervals函数
  输入参数：无
  功   能：合并重叠时间区间
  返 回 值：无
 ***************************************************************************/
template <typename datatype>
void movie_intervals<datatype>::merge_intervals()
{
    //创建结构体
    start_to_end merge_ste;
    //从大到小排序intervals内的开始时间
    sort(intervals.begin(), intervals.end(), [](const start_to_end& a, const start_to_end& b) {
        return a.starti < b.starti;
        });
    //区间合并
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
  函数名称：main函数
  输入参数：无
  返 回 值：0
 ***************************************************************************/
int main()
{
    movie_intervals<double> watch_the_entire_movie;
    cout << "请输入所有电影的起止时间：\n";
    while (!watch_the_entire_movie.input_intervals())
        continue;
    watch_the_entire_movie.merge_intervals();
    cout << watch_the_entire_movie.get_merge();
    return 0;
}