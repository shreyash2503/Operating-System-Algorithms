# include <bits/stdc++.h>
# include "TextTable.h"
using namespace std;


void FCFS(vector<int> &v, int head){
    int size = v.size();
    vector<int> trav;

    int overhead_movement = 0;
    for(auto i : v){
        overhead_movement += abs(head - i);
        trav.push_back(abs(head - i));
        head = i;
    }
    // cout << "Request" << "          " << "Tracks Traversed" << endl;
    TextTable t('-', '|', '+');
    t.add("Request");
    t.add("Tracks Traversed");
    t.endOfRow();

    for(int i=0;i<v.size();i++){
        t.add(to_string(v[i]));
        t.add(to_string(trav[i]));
        t.endOfRow();
    }
    cout << t << endl;

    cout << "Total overhead movement: " << overhead_movement << endl;

}


void SSTF(vector<int> &v, int head){
    vector<pair<int, int >> temp;
    for(auto i : v){
        temp.push_back({i, 0});
    }

    int size = v.size();
    int overhead_movement = 0;
    int count = 0;
    int min = INT_MAX;
    int break_count = 0;
    vector<int> ans;
    vector<int> trav;
    vector<int> heads;
    while(true){
        int min = INT_MAX;
        for(int i=0;i<size;i++){
            if(temp[i].second == 0){
                if(abs(head - temp[i].first) < min){
                    min = abs(head - temp[i].first);
                    count = i;
                }
            }
        }
        int flag = 0;
        for(int i=0;i<size;i++){
            if(temp[i].second == 0){
                flag = 1;
                break;

            }
        }

        if(flag == 0){
            break;
        }
        ans.push_back(temp[count].first);
        temp[count].second = 1;
        if(break_count == size){
            break;
        }
        trav.push_back(min);

        overhead_movement += min;
        head = temp[count].first;
        heads.push_back(head);


    }
    TextTable s('-', '|', '+');
    s.add("Request");
    s.add("Tracks Traversed");
    s.endOfRow();

    for(int i=0;i<heads.size();i++){
        s.add(to_string(heads[i]));
        s.add(to_string(trav[i]));
        s.endOfRow();
    }
    cout << s << endl;


    // cout << "Sequence of execution requests: ";
    // for (auto i : ans){
    // cout << endl;
    //     cout << i << " ";
    // }

    cout << "Total overhead movement: " << overhead_movement << endl;

}


void SCAN(vector<int> &v, int head, int end){
    vector<int> temp;
    vector<int> heads;
    vector<int> trav;
    int _temp = head;
    for(auto i : v){
        if(i > _temp){
            heads.push_back(i);
            temp.push_back(i);
        }
    }
    temp.push_back(end);

    sort(temp.begin(), temp.end());

    vector<int> temp2; 

    for(auto i : v){
        if(i < head){
            temp2.push_back(i);
            heads.push_back(i);
            head = i;
        }
    }
    sort(temp2.begin(), temp2.end(), greater<int>());

    int overhead_movement = 0;

    for(auto i : temp){
        cout << i << " ";
    }
    cout << endl;

    for(auto i : temp){
        overhead_movement += abs(head - i);
        trav.push_back(abs(head - i));
        head = i;
    }


    head = end;

    for(auto i : temp2){
        cout << i << " ";
    }
    cout << endl;

    for(auto i : temp2){
        overhead_movement += abs(head - i);
        trav.push_back(abs(head - i));
        head = i;
    }
    TextTable t('-', '|', '+');
    t.add("Requets");
    t.add("Tracks Traversed");
    t.endOfRow();
    for(int i=0;i<heads.size();i++){
        t.add(to_string(heads[i]));
        t.add(to_string(trav[i]));
        t.endOfRow();
    }

    cout << t << endl;


    cout << "Total overhead movement: " << overhead_movement << endl;

}



void CSCAN(vector <int> v, int head, int end){
    vector<int> temp1;
    vector<int> temp2;
    vector<int> heads;
    vector<int> trav;


    for(int i : v){
        if(i > head){
            temp1.push_back(i);
        }
        else{
            temp2.push_back(i);
        }
    }

    temp1.push_back(end);
    sort(temp1.begin(), temp1.end());
    for(int i=0;i<temp1.size();i++){
        heads.push_back(temp1[i]);
    }

    int overhead_movement = 0;

    for(auto i : temp1){
        overhead_movement += abs(head - i);
        trav.push_back(abs(head - i));
        head = i;
    }

    head = 0;
    sort(temp2.begin(), temp2.end());
    for(int i=0;i<temp2.size();i++){
        heads.push_back(temp2[i]);
    }
    overhead_movement += end;

    for(auto i : temp2){
        overhead_movement += abs(head - i);
        trav.push_back(abs(head - i));
        head = i;
    }
    TextTable t('-', '|', '+');
    t.add("Requests");
    t.add("Tracks Traversed");
    t.endOfRow();
    for(int i=0;i<heads.size();i++){
        t.add(to_string(heads[i]));
        t.add(to_string(trav[i]));
        t.endOfRow();
    }

    cout << "Total overhead movement: " << overhead_movement << endl;
}


void LOOK(vector<int> v, int head){
    vector<int> temp1;
    vector<int> temp2;
    vector<int> heads;
    vector<int> trav;

    for(int i : v){
        if(i > head){
            temp1.push_back(i);
        }
        else{
            temp2.push_back(i);
        }
    }

    sort(temp1.begin(), temp1.end());
    for(int i=0;i<temp1.size();i++){
        heads.push_back(temp1[i]);
    }
    sort(temp2.begin(), temp2.end(), greater<int>());
    for(auto i : temp2){
        heads.push_back(i);
    }

    int overhead_movement = 0;
    for(auto i : temp1){
        overhead_movement += abs(head - i);
        trav.push_back(abs(head - i));
        head = i;
    }
    head = temp1[temp1.size() - 1];
    for(auto i : temp2){
        overhead_movement += abs(head - i);
        trav.push_back(abs(head - i));
        head = i;
    }

    TextTable t('-', '|', '+');
    t.add("Requests");
    t.add("Tracks Traversed");
    t.endOfRow();
    for(int i=0;i<heads.size();i++){
        t.add(to_string(heads[i]));
        t.add(to_string(trav[i]));
        t.endOfRow();

    }
    cout << t << endl;
    cout << "Total overhead movement: " << overhead_movement << endl;
}

void CLOOK(vector<int> v, int head){
    vector<int> temp1;
    vector<int> temp2;
    vector<int> heads;
    vector<int> trav;

    for(int i : v){
        if(i > head){
            temp1.push_back(i);
        }
        else{
            temp2.push_back(i);
        }
    }
    sort(temp1.begin(), temp1.end());
    for(auto i : temp1){
        heads.push_back(i);
    }
    sort(temp2.begin(), temp2.end());
    for(auto i : temp2){
        heads.push_back(i);
    }

    int overhead_movement = 0;

    for(auto i : temp1){
        overhead_movement += abs(head - i);
        trav.push_back(abs(head - i));
        head = i;
    }
    overhead_movement += abs(head - temp2[0]);
    head = temp2[0];

    for(int i=1;i<temp2.size();i++){
        overhead_movement += abs(head - temp2[i]);
        trav.push_back(abs(head - temp2[i]));
        head = temp2[i];
    }

    TextTable t('-', '|', '+');
    t.add("Requests");
    t.add("Tracks Traversed");
    t.endOfRow();
    for(int i=0;i<heads.size();i++){
        t.add(to_string(heads[i]));
        t.add(to_string(trav[i]));
        t.endOfRow();

    }
    cout << t << endl;

    

    cout << "Total overhead movement: " << overhead_movement << endl;


}


int main(){
    int head;
    cout << "Enter the initial head position::";
    cin >> head;

    int n;
    cout << "Enter the number of requests::";
    cin >> n;


    vector<int> v;
    cout << "Enter the requests::" << endl;
    for(int i=0;i<n;i++){
        int data;
        cin >> data;
        v.push_back(data);

    }
    cout << "FCFS" << endl;
    FCFS(v, head);
    cout << "SSTF" << endl;
    SSTF(v, head);

    cout << "SCAN" << endl;
    SCAN(v, head, 199);

    cout << "CSCAN" << endl;
    CSCAN(v, head, 199);

    cout << "LOOK" << endl;
    LOOK(v, head);

    cout << "CLOOK" << endl;
    CLOOK(v, head);

}



