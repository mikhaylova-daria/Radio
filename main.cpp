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
    map <int, int> track_map; //ключ - track_id, значение - track_score
    track.insert(pair<int, int> (0, -1));
    bool flag = true;
    int min_track_id_has_null_score = 1;
    while (flag) {
        string cmd;
        cin >> cmd;
        if (cmd == "GET"){
            set<pair <int, int>, classcomp>::iterator itr = track.begin();
            int track_id = itr->first;
            int track_score = itr->second;
            if (itr->second > 0) {
                    cout << track_id << " " << track_score <<'\n';
                    track.erase(itr);
                    track.insert(pair<int, int> (track_id, -1));
                    track_map.find(track_id) -> second = -1;
            } else {
               if (itr->second == 0 && itr->first == min_track_id_has_null_score) {
                        track.erase(itr);
               }
               track.insert(pair<int, int> (min_track_id_has_null_score, -1));
               cout << min_track_id_has_null_score << " " << 0 << endl;
               track.insert(pair <int, int> (min_track_id_has_null_score, -1));
               map<int, int>::iterator itr_map = track_map.find (min_track_id_has_null_score);
               if (itr_map == track_map.end()) {
                   track_map.insert(pair<int, int> (min_track_id_has_null_score, -1));
               } else {
                   itr_map->second = -1;
               }
               map<int, int>::iterator find_pair = track_map.find(min_track_id_has_null_score);
               do {
                   ++min_track_id_has_null_score;
                   find_pair = track_map.find(min_track_id_has_null_score);
                   if (find_pair == track_map.end()) {
                       break;
                   }
               } while (find_pair->second != 0);
            }
        }
        if (cmd == "VOTE") {
            string fun_ip;
            int track_id;
            int score;
            int time;
            cin >> fun_ip >> track_id >> score >> time;
            map <string, int>::iterator itr_ip = ip.find(fun_ip);
            bool flag_changing_of_score = false;
            if (itr_ip == ip.end()) {
                ip.insert(pair <string, int> (fun_ip, time));
                flag_changing_of_score = true;
             } else {
                if ((time - (itr_ip -> second)) >= 600) {
                     itr_ip->second = time;
                     flag_changing_of_score = true;
                }
             }
             map<int, int>::iterator itr_map_track = track_map.find(track_id);
             if (itr_map_track == track_map.end()) { // если трека не было - вставляем и запоминаем итератор
                 itr_map_track = track_map.insert(pair <int, int > (track_id, 0)).first;
             }
             if (flag_changing_of_score){ // если нужно внести изменения
                 set<pair<int, int> >::iterator itr;
                 if ((itr = (track.find(pair <int, int> (*itr_map_track)))) != track.end()) { // из сета удаляем старые значения для этого трека
                     track.erase(itr);
                 }
                 itr_map_track->second += score;
                 track.insert(pair <int, int> (*itr_map_track));
             }
             cout << itr_map_track->second << '\n';// выдаём текущий рейтинг
             if ((itr_map_track->first == min_track_id_has_null_score) && (itr_map_track->second != 0)) {
                 map<int, int>::iterator find_pair;
                 do {
                     ++min_track_id_has_null_score;
                     find_pair = track_map.find(min_track_id_has_null_score);
                     if (find_pair == track_map.end()) {
                         break;
                     }
                 } while (find_pair->second != 0);
             } else {
                 if (itr_map_track->second == 0) {
                     if (min_track_id_has_null_score > itr_map_track->first) {
                         min_track_id_has_null_score = itr_map_track->first;
                    }
                }
             }
        }
        if(cmd == "EXIT") {
            cout<< "OK";
            flag = false;
        }
    }
    return 0;
}

