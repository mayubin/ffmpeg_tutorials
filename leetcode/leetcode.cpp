//
// Created by wangrl on 19-4-14.
//

#include <vector>
#include <unordered_map>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {

    }
};



// 0002
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode *head = l1;
    int carry = 0;  // Keep track of the carry digit
    while (l1 != nullptr) {
        l1->val += carry + (l2 != nullptr ? l2->val : 0);    // Add l2->val and carry to l1.val
        carry = l1->val / 10;
        l1->val = l1->val % 10;
        if (l1->next == nullptr && l2 != nullptr) {
            l1->next = l2->next;
            l2 = nullptr;
        }

        if (l1->next == nullptr && carry == 1) {
            l1->next = new ListNode(carry);
            l1 = l1->next;
        }
        l1 = l1->next;
        if (l2 != nullptr) {
            l2 = l2->next;
        }
    }
    return head;
}

// 0001
vector<int> twoSum(vector<int>& nums, int target) {
    // Key is the number and value is its index in the vector.
    unordered_map<int, int> hash;
    vector<int> result;
    for (int i = 0; i < nums.size(); i++) {
        int numberToFind = target - nums[i];

        // if numberToFind is found in map, return them.
        if (hash.find(numberToFind) != hash.end()) {
            result.push_back(hash[numberToFind]);
            result.push_back(i);
            return result;
        }

        // number was not dound. Put it in the map.
        hash[nums[i]] = i;
    }
    return result;
}

