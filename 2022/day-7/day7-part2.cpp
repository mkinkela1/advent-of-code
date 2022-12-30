#include<iostream>
#include<fstream>
#include<vector>
#include<queue>

using namespace std;

struct Node {
    string name;
    int size;
    Node* prev;
    vector<Node*> children;

    Node() {}

    Node(string _name, int _size, Node* _prev) {
        this->name = _name;
        this->size = _size;
        this->prev = _prev;
    }
};

void calcFolderSize(Node* root) {
    if(root == NULL) return;

    int sum = 0;

    for(auto& child: root->children) {   
        calcFolderSize(child);
        root->size += child->size; 
    }
}

vector<int> bfs(Node* root) {
    int ret = 0;
    queue<Node*> Q;
    vector<int> V;
    Q.push(root);

    while(!Q.empty()) {
        Node* tmp = Q.front();
        Q.pop();

        V.push_back(tmp->size);
        for(auto& child: tmp->children)
            Q.push(child);
    }

    return V;
}

int main(void) {

    fstream fin;
    fin.open("day7-input.txt", ios::in);

    cout << fin.is_open() << endl;

    Node* root = new Node("/", 0, NULL);
    Node* head = root;
    Node* head2 = root;

    string line;
    while(getline(fin, line)) {
    
        if(line[0] == '$') {
            if(line[2] == 'c') {
                if(line[5] != '/') {
                    char name[50];

                    sscanf(line.c_str(), "$ cd %s", name);

                    if(name[0] == '.' && name[1] == '.') root = root->prev;
                    else {
                        Node* folder = NULL;
                        for(auto& child: root->children)
                            if(child->name == name)
                                folder = child;

                        root = folder;
                    }
                }
            }
        } else {
            if(isdigit(line[0])) {

                char name[50];
                int size;

                sscanf(line.c_str(), "%d %s", &size, name);

                root->size += size;
            } else {
                char name[50];

                sscanf(line.c_str(), "dir %s", name);

                Node* folder = new Node(name, 0, root);
                root->children.push_back(folder);
            }
        }
    }

    calcFolderSize(head);

    int need = 30000000 - (70000000 - head2->size);
    vector<int> V = bfs(head2);
    sort(V.begin(), V.end());
    
    for(auto& mem : V) {
        if(mem >= need) {
            cout << mem << endl;
            return 0;
        }
        
    }

    return 0;
}