# include <bits/stdc++.h>
# include "TextTable.h"
# define tii tuple<int, int, int>
using namespace std;

class Node {
    public:
    int id;
    int art;
    int brt;
    int pr;
    int bt;
    
    public:
    Node(int id, int art, int brt, int pr){
        this->id = id;
        this->art = art;
        this->brt = brt;
        this->pr = pr;
        this->bt = brt;
    }
};



bool compareSJF(Node* a, Node* b){
    if(a->art < b->art){
        return true;
    }
    if(a->art == b->art){
        if(a->brt < b->brt){
            return true;
        }
        if(a->brt == b->brt){
            if(a->id < b->id){
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

bool comparePriority(Node* a, Node* b){
    if(a->art < b->art){
        return true;
    }
    if(a->art == b->art){
        if(a->pr < b->pr){
            return true;
        }
        if(a->pr == b->pr){
            if(a->id < b->id){
                return true;
            } else {
                return false;
            }
        } 
    }
    return false;
}



bool compareRoundRobin(Node* a, Node* b){
    if(a->art < b->art){
        return true;
    }

    if(a->art == b->art){
        if(a->id < b->id){
            return true;

        } else {
            return false;
        }
    }
    return false;
}



void SJF(vector<Node*> &v){

    sort(v.begin(), v.end(), compareSJF);

    int n = v.size();

    int time = 0;

    vector <tii> ans;

    priority_queue <tii, vector<tii>, greater<tii>> pq;

    cout << v[0]->id << " " << v[0]->art << " " << v[0]->brt << endl;

    time = v[0]->art + v[0]->brt;
    int j = 1;
    ans.push_back(make_tuple(v[0]->id, time, v[0]->art));
    while(true) {
        while(j < n && v[j]->art <= time){
            pq.push(make_tuple(v[j]->brt, v[j]->id, v[j]->art));
            j++;
        }

        if(j >= n){
            break;
        }
        auto temp = pq.top();
        pq.pop();
        time += get<0>(temp);
        ans.push_back(make_tuple(get<1>(temp), time, get<2>(temp)));
        time = max(time, v[j]->art);
    }

    while(!pq.empty()){
        auto temp = pq.top();
        pq.pop();
        time += get<0>(temp);
        ans.push_back(make_tuple(get<1>(temp), time, get<2>(temp)));
    }
    cout << "The size of ans is ::" << ans.size() << endl;

    // for(auto x: ans){
    //     cout << get<0>(x) << " " << get<1>(x) << " " << get<2>(x) << endl;
    // }
    
    vector<int> wt(n, 0);
    vector<int> tat(n, 0);

    for(int i=0;i<n;i++){
        wt[i] = get<1>(ans[i]) - v[i]->art - v[i]->brt;
        tat[i] = get<1>(ans[i]) - v[i]->art;
    }
    



    // ! Print the  Gantt Chart

    cout << "The Gantt Chart is ::" << endl;
    TextTable p( '-', '|', '+' );

    for(int i=0;i<n;i++){
        string t = "P" + to_string(get<0>(ans[i])) + "<" + to_string(get<2>(ans[i])) + " " + to_string(get<1>(ans[i])) + ">";
        p.add(t);
    }

    p.endOfRow();
    cout << p << endl;

    cout << endl;

    TextTable t( '-', '|', '+' );
    t.add( "Process ID" );
    t.add( "Arrival Time" );
    t.add( "Burst Time" );
    t.add("Completion Time");
    t.add( "Waiting Time" );
    t.add( "Turn Around Time" );

    t.endOfRow();
    for(int i=0;i<n;i++){
        t.add(to_string(get<0>(ans[i])));
        t.add(to_string(get<2>(ans[i])));
        t.add(to_string(get<1>(ans[i])));
        t.add(to_string(v[i]->brt));
        t.add(to_string(wt[i]));
        t.add(to_string(tat[i]));
        t.endOfRow();
    }

    cout << t << endl;

}



void preemptiveSJF(vector<Node*> &v){

    sort(v.begin(), v.end(), compareSJF);
    list<Node*> l;
    for (auto x: v){
        l.push_back(x);
    }


    int n = v.size();
    int time = 0;
    vector <tii> ans;
    vector <tii> store; 
    vector <int> burst;

    priority_queue <tii, vector<tii>, greater<tii>> pq;

    time = l.front()->art;
    pq.push(make_tuple(l.front()->brt, l.front()->id, l.front()->art));
    l.pop_front();

    while(true){
        auto top = pq.top();
        pq.pop();
        time += 1;
        // cout << "Before::";
        // cout << get<0>(top) << endl;
        get<0>(top)--;
        // cout << "After::";
        // cout << get<0>(top) << endl;
        if(get<0>(top) > 0){
            pq.push(top);
        }
        if(get<0>(top) == 0){
            store.push_back(make_tuple(get<1>(top), time, get<2>(top)));
        }
        ans.push_back(make_tuple(get<1>(top), time, get<2>(top)));

        if(!l.empty()){

            time = max(time, l.front()->art);
        }
        for(list<Node*>::iterator it = l.begin(); it != l.end();){
            if((*it)->art <= time && (*it)->brt < get<0>(pq.top())){
                pq.push(make_tuple((*it)->brt, (*it)->id, (*it)->art));
                it = l.erase(it);
            } else {
                it++;
            }
            
        }
        if(pq.empty()){
            if(!l.empty()){
                pq.push(make_tuple(l.front()->brt, l.front()->id, l.front()->art));
                l.pop_front();
            } else {
                break;
            }
        }
    }

//     sort(v.begin(), v.end(), compareSJF);

//    list<Node*> l; 
//    for(auto x : v){
//     l.push_back(x);
//    }

//    int n = v.size();

//    vector<tii> ans;
//    vector<tii> store;
//    vector<int> burst;

//    priority_queue<tii, vector<tii>, greater<tii>> pq;
//    int time = 0;
//    pq.push(make_tuple(l.front()->brt, l.front()->id, l.front()->art));
//    l.pop_front();

//    time = l.front()->art;

//    while(true){
//         auto top = pq.top();
//         pq.pop();

//         get<0>(top)--;
//         time += 1;
//         if(get<0>(top) > 0){
//             pq.push(top);
//         }
//         if(get<0>(top) == 0){
//             store.push_back(make_tuple(get<1>(top), time, get<2>(top)));
//         }
//         ans.push_back(make_tuple(get<1>(top), time, get<2>(top)));

//         if(!l.empty()){
//             time = max(time, l.front()->art);
//         }

//         for(list<Node*>::iterator it = l.begin(); it != l.end();){
//             if((*it)->art <= time && (*it)->brt < get<0>(pq.top())){
//                 pq.push(make_tuple((*it)->brt, (*it)->id, (*it)->art));
//                 it = l.erase(it);
//             } else {
//                 it++;
//             }
//         }

//         if(pq.empty()){
//             if(!l.empty()){
//                 pq.push(make_tuple(l.front()->brt, l.front()->id, l.front()->art));
//                 l.pop_front();
//             } else {
//                 break;
//             }
//         }

//    }






    // for(auto x : l){
    //     cout << x->id << " " << x->art << " " << x->brt << endl;
    // }

    // cout << "The size of ans is ::" << ans.size() << endl;

    // for(auto x : store){
    //     cout << get<0>(x) << " " << get<1>(x) << " " << get<2>(x) << endl;
    // }

    for(auto x : store){
        int id = get<0>(x);
        for(int i=0;i<n;i++){
            if(v[i]->id == id){
                burst.push_back(v[i]->brt); 
            }
        }
    }


    // ! Calculate the waiting time and the turn around time
    vector<int> wt(n, 0);
    vector<int> tat(n, 0);
    for(int i=0;i<n;i++){
        wt[i] = get<1>(store[i]) - get<2>(store[i]) - burst[i];
        tat[i] = get<1>(store[i]) - get<2>(store[i]);

    }

    // ! Print the Gantt Chart

    cout << "The Gantt Chart is ::" << endl;
    TextTable p( '-', '|', '+' );
    for(int i=0;i<ans.size();i++){
        string t = "P" + to_string(get<0>(ans[i])) + "<" + to_string(get<2>(ans[i])) + " " + to_string(get<1>(ans[i])) + ">";
        p.add(t);
    }
    p.endOfRow();

    cout << p << endl;

    // ! Printing the table;

    cout << endl;

    TextTable t( '-', '|', '+' );
    t.add( "Process ID" );
    t.add( "Arrival Time" );
    t.add( "Burst Time" );
    t.add("Completion Time");
    t.add( "Waiting Time" );
    t.add( "Turn Around Time" );
    t.endOfRow();

    for(int i=0;i<store.size();i++){
        t.add(to_string(get<0>(store[i])));
        t.add(to_string(get<2>(store[i])));
        t.add(to_string(burst[i]));
        t.add(to_string(get<1>(store[i])));
        t.add(to_string(wt[i]));
        t.add(to_string(tat[i]));
        t.endOfRow();
    }

    cout << t << endl;


}


void NPPS(vector<Node*> &v){

    int n = v.size();
    sort(v.begin(), v.end(), comparePriority);

    priority_queue<tii, vector<tii>, greater<tii>> pq;
    vector<tii> ans;
    vector<int> arrival;

    int time = 0;
    int j = 0;
    time = v[0]->art + v[0]->brt;
    ans.push_back(make_tuple(v[0]->id, time, v[0]->brt));
    j = 1;
    while(true){
       while(j < n && v[j]->art <= time){
        pq.push(make_tuple(v[j]->pr, v[j]->id, v[j]->brt));
        j++;
       }
       if(j >= n){
        break;
       }

       auto top = pq.top();
       pq.pop();
       time += get<2>(top);
       ans.push_back(make_tuple(get<1>(top), time, get<2>(top)));
       time = max(time, v[j]->art);

    }
    while(!pq.empty()){
        auto top = pq.top();
        pq.pop();
        time += get<2>(top);
        ans.push_back(make_tuple(get<1>(top), time, get<2>(top)));
    }
    for(auto x : ans){
        cout << get<0>(x) << endl;
    }

    for(int i=0;i<n;i++){
        int temp = get<0>(ans[i]);
        for(int j=0;j<n;j++){
            if(v[j]->id == temp){
                arrival.push_back(v[j]->art);
            }
        }
    }

    vector<int> wt(n, 0);
    vector<int> tat(n, 0);

    for(int i=0;i<n;i++){
        wt[i] = get<1>(ans[i]) - arrival[i] - get<2>(ans[i]);
        tat[i] = get<1>(ans[i]) - arrival[i];
    }

    cout << "The Gantt Chart is ::" << endl;

    TextTable p( '-', '|', '+' );
    for(int i=0;i<ans.size();i++){
        string t = "P" + to_string(get<0>(ans[i])) + "<" + to_string(arrival[i]) + " " + to_string(get<1>(ans[i])) + ">";
        p.add(t);
    }
    p.endOfRow();

    cout << p << endl;


    cout << endl;

    TextTable t( '-', '|', '+' );
    t.add( "Process ID" );
    t.add( "Arrival Time" );
    t.add( "Burst Time" );
    t.add("Completion Time");
    t.add( "Waiting Time" );
    t.add( "Turn Around Time" );
    t.endOfRow();
    for(int i=0;i<n;i++){
        t.add(to_string(get<0>(ans[i])));
        t.add(to_string(arrival[i]));
        t.add(to_string(get<2>(ans[i])));
        t.add(to_string(get<1>(ans[i])));
        t.add(to_string(wt[i]));
        t.add(to_string(tat[i]));
        t.endOfRow();
    }
    
    cout << t << endl;
    cout << endl;


}

void PPS(vector<Node*> &v){
    int n = v.size();

    sort(v.begin(), v.end(), comparePriority);
    priority_queue<tii, vector<tii>, greater<tii>> pq;

    vector<tii> ans;
    vector<tii> store;

    vector<int> arrival;
    vector<int> burst;
    list<Node*> l;
    for(auto x : v){
        l.push_back(x);
    }

    pq.push(make_tuple(l.front()->pr, l.front()->id, l.front()->brt));
    int time = l.front()->art;
    l.pop_front();
    while(true){
        auto top = pq.top();
        pq.pop();
        time += 1;
        get<2>(top)--;
        if(get<2>(top) > 0){
            pq.push(top);
        }
        if(get<2>(top) == 0){
            store.push_back(make_tuple(get<1>(top), time, get<2>(top)));
        }
        ans.push_back(make_tuple(get<1>(top), time, get<2>(top)));

        if(!l.empty()){
            time = max(time, l.front()->art);
        }

        for(list<Node*>::iterator it = l.begin(); it != l.end();){
            if((*it)->art < time && (*it)->pr < get<0>(pq.top())){
                pq.push(make_tuple((*it)->pr, (*it)->id, (*it)->brt));
                it = l.erase(it);
            } else {
                it++;
            }
        }
        if(pq.empty()){
            if(!l.empty()){
                pq.push(make_tuple(l.front()->pr, l.front()->id, l.front()->brt));
                l.pop_front();
            } else {
                break;
            }
        }
    }
    cout << "The size of l is ::" << l.size() << endl;

    cout << "The size of ans is ::" << ans.size();

    for(auto x : ans){
        cout << get<0>(x) << endl;
    }

    vector<int> wt(n, 0);
    vector<int> tat(n, 0);

    for(int i=0;i<store.size();i++){
        int id = get<0>(store[i]);
        for(int j=0;j<n;j++){
            if(v[j]->id == id){
                arrival.push_back(v[j]->art); 
                burst.push_back(v[j]->brt);
            }
        }
    }

    for(int i=0;i<n;i++){
        wt[i] = get<1>(store[i]) - arrival[i] - get<2>(store[i]);
        tat[i] = get<1>(store[i]) - arrival[i];
    }

    cout << "The Gantt Chart is ::" << endl;
    int j = 0;
    TextTable p( '-', '|', '+' );
    for(int i=0;i<ans.size();i++){
        string t = "P" + to_string(get<0>(ans[i])) + "<" + to_string(get<2>(ans[i])) + " " + to_string(get<1>(ans[i])) + ">";
        p.add(t);
        j++;
        if(j > 14){
            j = 0;
            p.endOfRow();
        }
         
    }
    p.endOfRow();

    cout << p << endl;

    cout << endl;

    TextTable t( '-', '|', '+' );
    t.add( "Process ID" );
    t.add( "Arrival Time" );
    t.add( "Burst Time" );
    t.add("Completion Time");
    t.add( "Waiting Time" );
    t.add( "Turn Around Time" );
    t.endOfRow();
    for(int i=0;i<n;i++){
        t.add(to_string(get<0>(store[i])));
        t.add(to_string(arrival[i]));
        t.add(to_string(burst[i]));
        t.add(to_string(get<1>(store[i])));
        t.add(to_string(wt[i]));
        t.add(to_string(tat[i]));
        t.endOfRow();
    }

    cout << t << endl;


}


void RoundRobin(vector<Node*> v, int tq){
    int n = v.size();
    sort(v.begin(), v.end(), compareRoundRobin);


    list<Node*> l;
    for(auto x : v){
        l.push_back(x);
    }
    int time = l.front()->art;

    vector<tii> ans;
    vector<tii> store;

    vector<int> arrival;


    queue<Node*> q;

    q.push(l.front());
    l.pop_front();
    time = q.front()->art;
    while(!q.empty()){
        auto front = q.front();
        q.pop();

        int temp = min(tq, front->bt);

        front->brt -= temp;

        time += temp;

        ans.push_back(make_tuple(front->id, time, temp));
        for(list<Node*>::iterator it = l.begin(); it != l.end();){
            if((*it)->art < time){
                q.push(*it);
                it = l.erase(it);
            } else {
                it++;
            }
        }

        if(front->brt > 0){
            q.push(front);
        } else {
            store.push_back(make_tuple(front->id, time, front->art));

        }

        if(q.empty()){
            if(!l.empty()){
                q.push(l.front());
                l.pop_front();
            } else {
                break;
            }
        }

    }


    // for(auto x : ans){
    //     cout << get<0>(x) << " " << get<2>(x) << endl;
    // }

    // cout << "the size of store is " << store.size() << endl;

    vector<int> wt(store.size(), 0);
    vector<int> tat(store.size(), 0);

    for(int i=0;i<n;i++){
        int id = get<0>(ans[i]);
        for(int j=0;j<n;j++){
            if(v[j]->id == id){
               arrival.push_back(v[j]->art);
            }
        }
    }

    for(int i=0;i<store.size();i++){
        wt[i] = get<1>(store[i]) - arrival[i] - get<2>(store[i]);
        tat[i] = get<1>(store[i]) - arrival[i];
    }

    cout << "The Gantt Chart is ::" << endl;
    TextTable p( '-', '|', '+' );
    for(int i=0;i<ans.size();i++){
        string t = "P" + to_string(get<0>(ans[i])) + "<" + to_string(get<2>(ans[i])) + " " + to_string(get<1>(ans[i])) + ">";
        p.add(t);
    }

    p.endOfRow();

    cout << p << endl;

    cout << endl;

    TextTable t( '-', '|', '+' );
    t.add( "Process ID" );
    t.add( "Arrival Time" );
    t.add( "Burst Time" );
    t.add("Completion Time");
    t.add( "Waiting Time" );
    t.add( "Turn Around Time" );
    t.endOfRow();

    for(int i=0;i<n;i++){
        t.add(to_string(get<0>(store[i])));
        t.add(to_string(arrival[i]));
        t.add(to_string(get<2>(store[i])));
        t.add(to_string(get<1>(store[i])));
        t.add(to_string(wt[i]));
        t.add(to_string(tat[i]));
        t.endOfRow();
    }


    cout << t << endl;
   



}

int main(){

    int option;
    
    while(true){
        cout << "1. Shortest Job First" << endl;
        cout << "2. Preemptive Shortest Job First" << endl;
        cout << "3. Non Preemptive Priority Scheduling" << endl;
        cout << "4. Preemptive Priority Scheduling" << endl;
        cout << "5. Round Robin" << endl;
        cin >> option;

        if(option == 1){
            cout << "Enter the file name::";
            string filename;
            cin >> filename;


            streambuf* orig_buf = cin.rdbuf();
            ifstream input(filename);

            cin.rdbuf(input.rdbuf());

            int n;
            cin >> n;
            vector<Node*> v;
            for(int i=0;i<n;i++){
                int art, brt;
                cin >> art >> brt;
                v.push_back(new Node(i, art, brt, 0));
            }

            cin.rdbuf(orig_buf);

            SJF(v);

        } else if(option == 2){
            cout << "Enter the file name::";
            string filename;
            cin >> filename;
            streambuf* orig_buf = cin.rdbuf();
            ifstream input(filename);

            cin.rdbuf(input.rdbuf());

            int n;
            cin >> n;
            vector<Node*> v;
            for(int i=0;i<n;i++){
                int art, brt;
                cin >> art >> brt;
                v.push_back(new Node(i, art, brt, 0));
            }
            cin.rdbuf(orig_buf);
            preemptiveSJF(v);
        } else if(option == 3){
            cout << "Enter the file name::";
            string filename;
            cin >> filename;
            streambuf* orig_buf = cin.rdbuf();
            ifstream input(filename);

            cin.rdbuf(input.rdbuf());

            int n;
            cin >> n;
            vector<Node*> v;
            for(int i=0;i<n;i++){
                int art, brt, pr;
                cin >> art >> brt >> pr;
                v.push_back(new Node(i, art, brt, pr));
            }
            cin.rdbuf(orig_buf);
            NPPS(v);
        } else if(option == 4){
            cout << "Enter the file name::";
            string filename;
            cin >> filename;
            streambuf* orig_buf = cin.rdbuf();
            ifstream input(filename);

            cin.rdbuf(input.rdbuf());

            int n;
            cin >> n;
            vector<Node*> v;
            for(int i=0;i<n;i++){
                int art, brt, pr;
                cin >> art >> brt >> pr;
                v.push_back(new Node(i, art, brt, pr));
            }
            cin.rdbuf(orig_buf);
            PPS(v);
        } else if(option == 5){
            cout << "Enter the file name::";
            string filename;
            cin >> filename;
            streambuf* orig_buf = cin.rdbuf();
            ifstream input(filename);

            cin.rdbuf(input.rdbuf());

            int n;
            cin >> n;
            int tq;
            cin >> tq;
            vector<Node*> v;
            for(int i=0;i<n;i++){
                int art, brt;
                cin >> art >> brt;
                v.push_back(new Node(i, art, brt, 0));
            }
            cin.rdbuf(orig_buf);
            RoundRobin(v, tq);
        } else {
            break;
        }

    }

    return 0;
}

