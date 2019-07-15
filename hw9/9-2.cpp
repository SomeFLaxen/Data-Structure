    #include <iostream>
    using namespace std;
    enum PointerTag { Link, Thread };
    typedef char TElemType;
    class BiThrNode;
    typedef BiThrNode* BiThrTree;
    struct BiThrNode
    {
        TElemType data;
        BiThrTree lchild, rchild;
        PointerTag ltag;
        PointerTag rtag;
    };
    BiThrTree pre = NULL;
    bool FLAG = false;
     
    BiThrTree FindPrevNode_Mid(BiThrTree &p)
    {
        if (p->ltag == Thread)
            return p->lchild;
        BiThrTree q = p->lchild;
        while (q->rtag == Link)
            q = q->rchild;
        return q;
    }
     
    BiThrTree FindSuccNode_Mid(BiThrTree &p)
    {
        if (p->rtag == Thread)
            return p->rchild;
        BiThrTree q = p->rchild;
        while (q->ltag == Link)
            q = q->lchild;
        return q;
    }
     
    bool JudgeChar(BiThrTree p, char c)
    {
        if (p && p->data == c) {
            BiThrTree succ = FindSuccNode_Mid(p);
            BiThrTree prev = FindPrevNode_Mid(p);
            cout << "succ is ";
            if (!succ)
                cout << "NULL\n";
            else
                cout << succ->data << succ->rtag << endl;
            cout << "prev is ";
            if (!prev)
                cout << "NULL\n";
            else
                cout << prev->data << prev->ltag << endl;
            return true;
        }
        return false;
    }
     
    /*?????ж??ַ?????????1_?ǵݹ?*/
    void FindSucPreNode1(BiThrTree &btt, char c)
    {
        BiThrTree p = btt;
        bool flag = false;
        while (p) {
            if (flag = JudgeChar(p, c))
                break;
            while (p->ltag == Link)
                p = p->lchild;
            if (flag = JudgeChar(p, c))
                break;
            while (p->rtag == Thread && p->rchild) {
                p = p->rchild;
                if (flag = JudgeChar(p, c))
                    break;
            }
            if (flag)
                break;
            p = p->rchild;
        }
        if (!flag)
            cout << "Not found\n";
    }
     
    /*?????ж??ַ?????????2_?ݹ?*/
    void FindSucPreNode2(BiThrTree &btt, char c)
    {
        if (btt && !FLAG) {
            if (btt->ltag == Link)
                FindSucPreNode2(btt->lchild, c);
            if (JudgeChar(btt, c)) {
                FLAG = true;
                return;
            }
            if (btt->rtag == Link)
                FindSucPreNode2(btt->rchild, c);
        }
    }
     
    /*????????????*/
    void InThreading_Mid(BiThrTree &btt)
    {
        if (btt) {
            if (btt->ltag == Link)    //?Ӳ??Ӿ???
                InThreading_Mid(btt->lchild);
            if (btt->ltag == Thread)
                btt->lchild = pre;
            if (pre && pre->rtag == Thread)
                pre->rchild = btt;
            pre = btt;
            if (btt->rtag == Link)  //?Ӳ??Ӿ???
                InThreading_Mid(btt->rchild);
            //????ǰ?????????????ʲ????ж?
            //btt->rtag ?Ƿ?Ϊ Link ????????????????
            //ʵ?ʣ?????????ʱ?Ƿ?Ӱ??????????
        }
    }
     
    /*?????????????????????1_?ǵݹ?*/
    void TraverseThrTree_Mid1(BiThrTree &btt)
    {
        BiThrTree p = btt;
        while (p) {
        //?൱????????һ???ڵ?ĺ??
            while (p->ltag == Link)
                p = p->lchild;
            putchar(p->data);
            while (p->rtag == Thread && p->rchild) {
                p = p->rchild;
                putchar(p->data);
            }
            p = p->rchild;
        }
        putchar('\n');
    }
     
    /*?????????????????????2_?ݹ?*/
    void TraverseThrTree_Mid2(BiThrTree &btt)
    {
        if (btt) {
            if (btt->ltag == Link)
                TraverseThrTree_Mid2(btt->lchild);
            putchar(btt->data);
            if (btt->rtag == Link)
                TraverseThrTree_Mid2(btt->rchild);
        }
    }
     
    void CreateBiTree_Pre(BiThrTree &btt)
    {
        char c;
        cin >> c;
        if (c == '#')
            return;
        btt = new BiThrNode;
        btt->data = c;
        btt->lchild = NULL;
        btt->rchild = NULL;
        CreateBiTree_Pre(btt->lchild);
        if (btt->lchild)
            btt->ltag = Link;
        else
            btt->ltag = Thread;
        CreateBiTree_Pre(btt->rchild);
        if (btt->rchild)
            btt->rtag = Link;
        else
            btt->rtag = Thread;
    }
     
    int main()
    {
        BiThrTree btt = NULL;
        char c;
        CreateBiTree_Pre(btt);
        InThreading_Mid(btt);
        TraverseThrTree_Mid2(btt);
        putchar('\n');
        cin >> c;
        FindSucPreNode2(btt, c);
        if (!FLAG)
            cout << "Not found\n";
        return 0;
    }