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

    cout << root->name << " " << root->size << endl;
}

int bfs(Node* root) {
    int ret = 0;
    queue<Node*> Q;
    Q.push(root);

    while(!Q.empty()) {
        Node* tmp = Q.front();
        Q.pop();

        if(tmp->size <= 100000) ret += tmp->size;
        for(auto& child: tmp->children)
            Q.push(child);
    }

    return ret;
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

    cout << bfs(head2) << endl;

    return 0;
}