# include <bits/stdc++.h>
# include "TextTable.h"
using namespace std;


class Node {
    public:
    int data;
    int key;
    int value;
    Node* next;
    Node* prev;
    Node(int data){
        this->data = data;
        this->next = NULL;
    }
    Node(int key, int value){
        this->key = key;
        this->value = value;
    }

};

void print(vector<int> str, vector<vector<int>> &v) {
    TextTable t( '-', '|', '+' );
    for(auto x : str){
        t.add("-" + to_string(x) + "-");
    }
    t.endOfRow();

    int count = 0;

    while(count < 4){
        for(int i=0;i<v.size();i++){
            if(v[i].size() > count){
                t.add(to_string(v[i][count]));
            } else {
                t.add(" ");
            }
        }
        t.endOfRow();
        count ++;
    }

    cout << t << endl;
   

}


void FIFO(vector<int> v, int frames){
    int faults = 0;
    Node* head = NULL;
    Node* tail = NULL;
    unordered_map<int, Node*> map;
    int size = 0;
    vector<vector<int>> ans;
    Node* ptr = head;

    for(int i=0;i<v.size();i++){
        if(map.find(v[i]) != map.end()){
            vector<int> p;
            Node* temp = head;
            while(temp != NULL){
                p.push_back(temp->data);
                temp = temp->next;
            }
            ans.push_back(p);
            continue;
        }
        if(head == NULL && tail == NULL){
            head = new Node(v[i]);
            tail = head;
            ptr = head;
            map[v[i]] = head;
            size ++;
            faults ++;
        }else if(size < frames){
            tail->next = new Node(v[i]);
            tail->next->prev = tail;
            tail = tail->next;
            map[v[i]] = tail;
            faults ++;
            size++;
        } else {
            if(ptr == head){
                Node* temp = new Node(v[i]);
                Node* next = head->next;
                temp->next = next;
                next->prev = temp;
                head->next = NULL;
                ptr = next;

                map.erase(head->data);
                head = temp;
            } else {
                if(ptr){
                    Node* temp = new Node(v[i]);
                    Node* next = ptr->next;
                    temp->prev = ptr->prev;
                    temp->prev->next = temp;
                    temp->next = next;
                    if(next){
                        next->prev = temp;
                    }
                    ptr->next = NULL;
                    map.erase(ptr->data);
                    ptr->prev = NULL;
                    if(next == NULL){
                        ptr = head;
                    } else{
                        ptr = next;
                    }
                }
            }
            
            faults ++;
        }
        vector<int> p;
        Node* temp = head;
        while(temp != NULL){
            p.push_back(temp->data);
            temp = temp->next;
        }
        ans.push_back(p);
    }
    for(auto x : ans){
        for(auto y : x){
            cout << y << " ";
        }
        cout << endl;
    }
    print(v, ans);
    cout << endl;
    cout << "Number of page faults::" << faults << endl;
    faults = 0;


}

class LRU{
    public:
    Node* head = new Node(-1, -1);
    Node* tail = new Node(-1, -1);
    int cap;
    unordered_map<int, Node*> m;
    int faults;
    vector<vector<int>> ans;
    vector<int> str;

    LRU(int capacity, vector<int> str){
        this->cap = capacity;
        head->next = tail;
        tail->prev = head;
        this->str = str;
        this->faults = 0;

    }

    void addNode(Node* newNode){
        // cout << "Hi" << endl;
        Node* temp = head->next;

        newNode->next = temp;
        newNode->prev = head;

        head->next = newNode;
        temp->prev = newNode;
        this->faults++;
        Node* iterator = head->next;
        vector<int> p;
        while(iterator->key != -1){
            p.push_back(iterator->key);
            iterator = iterator->next;
        }
        
        // for(auto x : p){
        //     cout << x << " ";
        // }
        ans.push_back(p);
    }

    void deleteNode(Node* delNode){
        // cout << "Hello" << endl;
        Node* prevv = delNode->prev;
        Node* nextt = delNode->next;
        delNode->next = NULL;
        delNode->prev = NULL;

        prevv->next = nextt; 
        nextt->prev = prevv;
    }

    int get(int key){
        if(m.find(key) != m.end()){
            Node* resNode = m[key];
            int ans = resNode->value;

            m.erase(key);
            deleteNode(resNode);
            // deleteNode(tail->prev);
            addNode(resNode);
            faults--;
            m[key] = head->next;
            return ans;
        }
    }

    void put(int key, int value){
        if(m.find(key) != m.end()){
            int ans = get(key);
            return;
        }
        
        if(m.size() == cap){
            // cout << "This is the second block" << endl;
            m.erase(tail->prev->key);
            deleteNode(tail->prev);
        }

        addNode(new Node(key, value));
        m[key] = head->next;
    }

    void _print(){
        print(str, ans);

    }
};



bool search(int key, vector<int>& fr)
{
    for (int i = 0; i < fr.size(); i++)
        if (fr[i] == key)
            return true;
    return false;
}

int predict(int pg[], vector<int>& fr, int pn, int index)
{
    int res = -1, farthest = index;
    for (int i = 0; i < fr.size(); i++) {
        int j;
        for (j = index; j < pn; j++) {
            if (fr[i] == pg[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
 
        if (j == pn)
            return i;
    }
 
    return (res == -1) ? 0 : res;
}


void optimalPage(int pg[], int pn, int fn)
{
    vector<int> fr;
 
    int hit = 0;
    for (int i = 0; i < pn; i++) {
 
        if (search(pg[i], fr)) {
            hit++;
            continue;
        }
 
 
        if (fr.size() < fn)
            fr.push_back(pg[i]);
 
        else {
            int j = predict(pg, fr, pn, i + 1);
            fr[j] = pg[i];
        }
    }
    cout << "No. of hits = " << hit << endl;
    cout << "No. of misses = " << pn - hit << endl;
}




int main(){

    string t;
    cout << "Enter the reference string::";
    cin >> t;

    vector<int> a;
    for(auto x : t){
        a.push_back(x - '0');
    }

    int frames;
    cout << "Enter the number of frames::";
    cin >> frames;

    // FIFO(a, frames);
    // LRU  *l = new LRU(frames, a);
    // for(auto x : a){
    //     l->put(x, x);
    // }
    // l->_print();
    // cout << l->faults << endl;

    while(true){
        int option;
        cout << "1). FIFO" << endl;
        cout << "2). LRU" << endl;
        cout << "3). Optimal" << endl;
        cin >> option;
        if(option == 1){
            FIFO(a, frames);
        } else if(option == 2){
            LRU  *l = new LRU(frames, a);
            for(auto x : a){
                l->put(x, x);
            }
            l->_print();
            cout << "Number of page faults::" << l->faults << endl;
            l->faults = 0;
        } else if(option == 3){
            int size = a.size();
            int pg[size];
            for(int i=0;i<size;i++){
                pg[i] = a[i];
            }
            optimalPage(pg, size, frames);

        }
        
         else {
            break;
        }

        
    }


    







}