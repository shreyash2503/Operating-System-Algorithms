# include <bits/stdc++.h>
# include "TextTable.h"
using namespace std;



class Node {
    public:
    int pid;
    int nr;
    vector<int> max;
    vector<int> allocation;
    vector<int> need;
    bool flag;
    Node(int pid, int nr){   // -> nr indicates the number of resources
        this->pid = pid;    // -> pid indicates the process if of the process
        this->nr = nr;
        this->flag = false;
        this->max = vector<int>(nr, -1);
        this->allocation = vector<int>(nr, -1);
        this->need = vector<int>(nr, -1);
    }

    void setMax(vector<int> max){
        this->max = max;
    }
    void setAllocation(vector<int> allocation){
        this->allocation = allocation;
    }
    void setNeed(vector<int> need){
        this->need = need;
    }
    void setFlag(bool flag){
        this->flag = flag;
    }


};

void print(const map<int, Node*> &map, int nr){

    TextTable t('-', '|', '+');
    cout << endl;
    t.add("PID");
    t.add("MAX");
    t.add("ALLOCATION");
    t.add("FLAG");
    t.add("NEED");
    t.endOfRow();
    for(const auto& m : map){
        t.add(to_string(m.second->pid));
        string max = "<";
        for(int i = 0; i < nr; i++){
            max += to_string(m.second->max[i]) + " ";
        }
        max += ">";
        t.add(max);
        
        string allocation = "<";
        for(int i = 0; i < nr; i++){
            allocation += to_string(m.second->allocation[i]) + " ";
        }
        allocation += ">";
        t.add(allocation);
        t.add(m.second->flag == true ? "T" : "F");

        string need = "<";
        for(int i = 0; i < nr; i++){
            need += to_string(m.second->need[i]) + " ";
        }
        need += ">";
        t.add(need);
        t.endOfRow();

    }

    cout << t << endl;

}

void BANKERS(map<int, Node*> &map, vector<int> &total){

    // Calculate NEED vector
        //Calcuate the total allocated resources
        for(const auto& m : map){
            for(int i = 0; i < m.second->nr; i++){
                m.second->need[i] = m.second->max[i] - m.second->allocation[i];
            }
        }

    // Calculate available
        vector<int> available(total.size(), -1);
            // Calculate the allocated vector
                vector<int> allocated(total.size(), 0);
                for(const auto& m : map){
                    for(int i = 0; i < m.second->nr; i++){
                        allocated[i] += m.second->allocation[i];
                    }
                }
                for(int i=0;i<total.size();i++){
                    available[i] = total[i] - allocated[i];
                }

    // Print total
        cout << "Total resources::" << endl;
        TextTable _t('-', '|', '+');
        string tl = "<";
        for(int i=0;i<available.size();i++){
            tl += to_string(total[i]) + " ";
        }
        tl += ">";
        _t.add(tl);
        _t.endOfRow();
        cout << endl;
        cout << _t << endl;

        // Print initial available
        cout << "Initial available::" << endl;
        TextTable _a('-', '|', '+');
        string _available = "<";
        for(int i=0;i<available.size();i++){
            _available += to_string(available[i]) + " ";
        }
        _available += ">";
        _a.add(_available);
        _a.endOfRow();
        cout << endl;
        cout << _a << endl;


    
    // Implement the algorithm
        int count  = 0;
        int size = map.size();
        int iterator = 0;
        queue<Node*> q;
        int flag = 0; // -> Flag to track the iterator
        queue<pair<int, vector<int>>> q1;

        while(count < size){
            if(iterator == size){
                iterator = 0;
            }
            if(map[iterator]->flag == true){
                iterator++;
                continue;
            }
            Node* temp = map[iterator];
            for(int i=0;i<total.size();i++){
                if(temp->need[i] > available[i]){
                    flag = 1;
                    iterator++;
                    break;
                }
            }
            if(flag == 1){
                flag = 0;
                continue;
            }
            temp->flag = true;
            for(int i=0;i<total.size();i++){
                available[i] += temp->allocation[i];
            }
            vector<int> _temp = available;
            pair<int, vector<int>> p(temp->pid, _temp);
            q1.push(p);
            q.push(temp);
            iterator++;
            count++;
        }

    // Print the Table
    
    print(map, total.size());
    cout << endl;


    TextTable t('-', '|', '+');
    cout << "The safe state of the program is ::" << endl;
    while(!q1.empty()){
        pair<int, vector<int>> p = q1.front();
        q1.pop();
        string h = "P" + to_string(p.first) + " <";
        for(int i=0;i<p.second.size();i++){
            h += to_string(p.second[i]) + " ";
        }
        h += ">";
        t.add(h);
    }
    t.endOfRow();

    cout << t ;
    

}


int main(){
    map<int, Node *> map;
    int n;
    int nr;

    // ! Number of Process
    // cout << "Enter the number of process::";
    cin >> n;

    // ! Number of Resources
    // cout << "Enter the number of resources::" ;
    cin >> nr;

    // ! Total resources
    vector<int> total(nr, -1);
    // cout << "Enter the total resources::";
    for(int i = 0; i < nr; i++){
        cin >> total[i];
    }

    for(int i = 0; i < n; i++){
        int pid;
        // ! Process ID
        // cout << "Enter the process id::" << endl;
        cin >> pid;

        Node* node = new Node(pid, nr);
        vector<int> max(nr, -1);
        vector<int> allocation(nr, -1);
        vector<int> need(nr, -1);

        // ! Max resources vector
        // cout << "Enter the max resources::" << endl;
        for(int i = 0; i < nr; i++){
            cin >> max[i];
        }

        // cout << "Enter the allocated resources::" << endl;
        // ! Allocated resources vector
        for(int i = 0; i < nr; i++){
            cin >> allocation[i];
        }
        
        node->setMax(max);
        node->setAllocation(allocation);
        map[pid] = node;
    }
    BANKERS(map, total);
    

    return 0;
}