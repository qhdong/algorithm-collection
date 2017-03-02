#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(nullptr) {}
};

class InsertValue {
public:
    // 构建环形链表并插入val
    ListNode* insert(vector<int> A, vector<int> nxt, int val) {
        ListNode *phead = construct(A, nxt);
        if (!phead) {
            phead = new ListNode(val);
            phead->next = phead;
            return phead;
        }

        ListNode *pnode = phead;
        while (val > pnode->val) {
            pnode = pnode->next;
            if (pnode == phead) break;
        }

        ListNode *ptmp = new ListNode(pnode->val);
        ptmp->next = pnode->next;
        pnode->next = ptmp;
        pnode->val = val;

        if (phead == pnode) return ptmp->val < phead->val ? ptmp : phead;
        else return phead;
    }

private:
    // 构建环形链表
    ListNode* construct(const vector<int> &vals, const vector<int> &nexts) {
        if (vals.empty() || nexts.empty() || vals.size() != nexts.size()) {
            return nullptr;
        }

        ListNode *phead = new ListNode(vals[0]);
        ListNode *pnode = phead;
        vector<int>::size_type idx = 0;
        while (nexts[idx]) {
            pnode->next = new ListNode(vals[nexts[idx++]]);
            pnode = pnode->next;
        }
        pnode->next = phead;

        return phead;
    }
};

// 将链表转换为vector
vector<int> list2vector(const ListNode *phead) {
    if (!phead) return {};

    vector<int> ret;
    ret.push_back(phead->val);
    auto pnode = phead->next;
    while (pnode && pnode != phead) {
        ret.push_back(pnode->val);
        pnode = pnode->next;
    }
    return ret;
}

// 打印环形链表
void print_looplist(const ListNode *phead) {
    auto ret = list2vector(phead);

    ostream_iterator<int> out(cout, "->");
    copy(ret.begin(), ret.end()-1, out);
    cout << ret.back() << endl;
}

int main() {
    vector<int> A = {1,3,4,5,7};
    vector<int> nxt = {1,2,3,4,0};

    InsertValue ans;

    print_looplist(ans.insert({1}, {0}, 2));
    print_looplist(ans.insert({1}, {0}, 0));
    print_looplist(ans.insert({}, {0}, 0));
    print_looplist(ans.insert(A, nxt, 0));
    print_looplist(ans.insert(A, nxt, 2));
    print_looplist(ans.insert(A, nxt, 6));
    print_looplist(ans.insert(A, nxt, 9));
    print_looplist(ans.insert(A, nxt, -3));
    return 0;
}
