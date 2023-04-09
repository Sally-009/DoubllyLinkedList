#include <iostream>

using namespace std;

struct Node{
    int data;
    Node *previous, *next;
};

class DLL{
    private:
    
    Node *first, *last;
    int size;
    
    public:
    
    // CONSTRUCTOR
    // リストの初期化
    DLL()
    {
        first = last = nullptr;
        size = 0;
    }
    
    // DESTORACTOR
    // リストの消去
    ~DLL()
    {
        Node *p;    // p = 現在地
        
        cout << endl;   // 改行
        
        p = first;

        while(p != nullptr)
        {
            // 先頭を更新
            first = first -> next;
            
            cout << p -> data << " ";
            
            delete p;   // ノードを消去
            p = first;  // 次のノードへ
            
            size--;
        }
        
        cout << "deleted." << endl;
    }
    
    // ノードの新規追加
    void addNode(int newData)
    {
        Node *newNode = new Node;   // 新規ノードを作成
        newNode -> data = newData;  // データを代入
        newNode -> next = nullptr;  // 末尾なのでnextはNULL
        
        // リストが空のとき
        if(size == 0)
        {
            first = last = newNode;         // 先頭と末尾を更新
            newNode -> previous = nullptr;  // 先頭なのでpreviousはNULL
        }
        // リストが空でないとき ...
        else
        {
            newNode -> previous = last;     // 新規ノードを末尾のノードとリンクさせる
            last -> next = newNode;         // 末尾のノードを新規ノードとリンクさせる
            last = newNode;                 // 末尾を更新
        }
        
        size++;
        
    }
    
    
    // n番目に新規ノードを挿入
    void insertNode(int n, int newData)
    {
        Node *p = first;    // p = 現在地（この前に新規ノードを挿入）
        
        // nが有効かチェック
        if(n > size || n <= 0)
        {
            cout << n << " is not a valid position." << endl;
            return;
        }
        
        // 新規ノードを作成
        Node *newNode = new Node;
        newNode -> data = newData;
        
        // n = 1 (先頭のとき)
        if(n == 1)
        {
            newNode -> next = first;        // 新規ノードのnextを先頭のノードとリンク
            first -> previous = newNode;    // 先頭のpreviousを新規ノードにリンク
            first = newNode;                // 先頭を更新
            
            cout << "New node with data " << newData << " added at the head." << endl;
        }
        
        // n = size (末尾のとき)
        else if(n == size){
            addNode(newData);
            size--;             // size++;が上の関数に含まれているため
            cout << "New node with data " << newData << " added at the end." << endl;
        }
        
        // それ以外のとき
        else
        {
            for(int i = 1; i < n; i++)
                p = p -> next;
            
            // 新規ノードを前後とリンク
            newNode -> next = p;
            newNode -> previous = p -> previous;
            
            // 前後のノードを新規ノードとリンク
            p -> previous -> next = newNode;    // 前
            p -> previous = newNode;            // 次
            
            cout << "New node with data " << newData << " added at the " << n << "th." << endl;
        }
        
        // サイズを更新
        size++;
    }
    
    // n番目のノードの削除
    void deleteNode(int n)
    {
        Node *p;    // p = 現在地
        
        p = first;

        // nが有効かチェック
        if(n > size || n <= 0)
        {
            cout << n << " is not a valid position." << endl;
            return;
        }
        
        // 先頭のとき
        if(n == 1)
        {
            cout << "1st Node: " << p -> data << " deleted." << endl;
            first -> next -> previous = nullptr;    // 二番目のノードのpreviousをNULLにする
            first = first -> next;                  // 先頭を更新
        
            delete p;   // ノードを削除
        }
        // 末尾のとき
        else if(n == size)
        {
            p = last;
            cout << "Last Node: " << p -> data << " deleted." << endl;
            last -> previous -> next = nullptr;     // 末尾の一つ前のノードのnextをNULLにする
            last = last -> previous;                // 末尾を更新
            
            delete p;
        }
        // それ以外のとき
        else{
            // n番目まで移動
            for(int i = 1; i < n; i++)
                p = p -> next;
            
            // リンクを更新
            p -> previous -> next = p -> next;      // 前のノードのnextを次のノードとリンクする
            p -> next -> previous = p -> previous;  // 次のノードのpreviousを前のノードとリンクする
            
            // ノードを削除
            cout << n << "th node: " << p -> data << " deleted." << endl;
            delete p;
        }
        size--;
    }
    
    // リストの表示 (引数： 0 通常、1 逆順)
    void showList(bool reverse)
    {
        Node *p = nullptr;  // p = 現在地
        
        switch(reverse)
        {
            // 通常順
            case 0:
            
                cout << "Normal Order:\t";
            
                p = first;  // 初期位置
                
                while(p != nullptr)
                {
                    cout << p -> data << "->";
                    p = p -> next;
                }
            
            break;
            
            // 逆順
            case 1:
            
                cout << "Reverse Order:\t";
            
                p = last;   // 初期位置
                
                while(p != nullptr)
                {
                    cout << p -> data << "->";
                    p = p -> previous;
                }
            
            break;
        }
        
        cout << endl;
    }
    
    // サイズの表示
    void showSize()
    {
        cout << "Size: " << size << endl;
    }
    
    // サイズを返す
    int getSize()
    {
        return size;
    }
};

int main()
{
    DLL list;
    
    cout << "Before adding nodes . . ." << endl;
    list.showSize();
    
    list.addNode(10);
    list.addNode(4);
    list.addNode(24);
    list.addNode(9);
    list.addNode(2);
    list.addNode(64);
    list.addNode(3);
    list.addNode(12);
    
    cout << "\nAfter adding nodes . . ." << endl;
    list.showSize();
    list.showList(0);
    list.showList(1);
    
    cout << "\nDeleting some nodes . . ." << endl;
    list.deleteNode(1);
    list.deleteNode(list.getSize());
    list.deleteNode(10);
    list.deleteNode(5);

    cout << endl;
    
    list.showSize();
    list.showList(0);
    list.showList(1);
    
    cout << "\nAfter inserting some nodes . . ." << endl;
    list.insertNode(1, 100);
    list.insertNode(list.getSize(), 500);
    list.insertNode(3, 200);
    list.insertNode(10, 1);

    cout << endl;
    
    list.showSize();
    list.showList(0);
    list.showList(1);

    return 0;
}

