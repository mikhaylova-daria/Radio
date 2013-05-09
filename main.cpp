#include <iostream>
#include <map>
#include <set>
#include <string>
#include <iterator>
#include <algorithm>
using namespace std;
struct classcomp {
  bool operator() (const pair<int, int> &argv_1, const pair<int, int> &argv_2) const
  {
      return (argv_1.second > argv_2.second) || ((argv_1.second == argv_2.second) && (argv_1.first < argv_2.first));
  }
};
int main()
{
    map <string, int> ip; // ключ - ip, значение - последнее защитанное время
    set <pair <int, int>, classcomp> track; // первый элемент пары - track_id, второй - track_score
    track.insert(pair<int, int> (0, -1));
    bool flag = true;
    int min_track_id_has_null_score = 1;
    while (flag) {
        string cmd;
        cin >> cmd;
        if (cmd == "GET"){
            set<pair <int, int>, classcomp>::iterator itr = track.begin();
            if (itr->second != -1) {
                int track_id = itr->first;
                int track_score = itr->first;
                cout << track_id << " " << track_score <<endl;
                track.erase(itr);
                track.insert(pair<int, int> (track_id, -1));
            } else {
               cout << min_track_id_has_null_score << " " << 0 <<endl;
               track.insert(pair <int, int> (min_track_id_has_null_score, -1));
               while (track.count(pair <int, int> (min_track_id_has_null_score, 0)) + track.count(pair <int, int> (min_track_id_has_null_score, -1)) > 0){
                    ++min_track_id_has_null_score;
               }
            }
        }
        if (cmd == "VOTE");
        if(cmd == "EXIT" );
    }
    cout <<"!";
    pair <string, int> a;
    return 0;
}

