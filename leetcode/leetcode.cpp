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


// 0004
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size();
    int n = nums2.size();


}

// 0003
int lengthOfLongestSubstring(string s) {
    // ASCII char sequence，最长256个字符。
    vector<int> dest(256, -1);
    int longest = 0, start = 0;

    for (int i = 0; i < s.length(); i++) {
        // 如果数组中存在当前字符，就把当前的下标值赋值给start变量。
        start = max(dest[s[i]] + 1, start);
        // 将当前的下标值存入到数组中。
        dest[s[i]] = i;
        // 缓存最大值的计算结果。
        longest = max(longest, i - start + 1);
    }

    return longest;
}

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

