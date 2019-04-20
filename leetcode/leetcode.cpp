//
// Created by wangrl on 19-4-14.
//

#include <vector>
#include <unordered_map>
#include <climits>
#include <algorithm>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {

    }
};



// 0018
vector<vector<int>> fourSum(vector<int> &nums, int target) {
    vector<vector<int>> total;

    int n = nums.size();

    if (n < 4)
        return total;

    sort(nums.begin(), nums.end());

    for (int i = 0; i < n - 3; i++) {
        if (i > 0 && nums[i] == nums[i - 1])
            continue;
        // 最小值比target值大，则后面不存在等于target值。
        if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target)
            break;
        // 最大值小于target值进入下一个循环。
        if (nums[i] + nums[n - 3] + nums[n - 2] + nums[n - 1] < target)
            continue;
        // 回到三个数的比较中。
        for (int j = i + 1; j < n - 2; j++) {
            if (j > i + 1 && nums[j] == nums[j - 1])
                continue;
            if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target)
                break;
            if (nums[i] + nums[j] + nums[n - 2] + nums[n - 1] < target)
                continue;
            int left = j + 1, right = n - 1;
            while (left < right) {
                int sum = nums[left] + nums[right] + nums[i] + nums[j];
                if (sum < target)
                    left++;
                else if (sum > target)
                    right--;
                else {
                    total.push_back(vector<int>{nums[i], nums[j], nums[left], nums[right]});
                    do {
                        left++;
                    } while (nums[left] == nums[left - 1] && left < right);

                    do {
                        right--;
                    } while (nums[right] == nums[right + 1] && left < right);
                }
            }
        }
    }
    return total;
}

// 0017
vector<string> letterCombinations(string digits) {
    vector<string> result;

    if (digits.empty()) {
        return vector<string>();
    }

    // 0和1为空。
    static const vector<string> v = {"", "", "abc", "def", "ghi", "jkl",
                                     "mno", "pqrs", "tuv", "wxyz"};
    // add a seed for the initial case.
    result.push_back("");
    for (int i = 0; i < digits.size(); i++) {
        int num = digits[i] - '0';
        if (num < 0 || num > 9)
            break;
        const string &candidate = v[num];
        if (candidate.empty())
            continue;
        vector<string> tmp;
        for (int j = 0; j < candidate.size(); ++j) {
            for (int k = 0; k < result.size(); ++k) {
                // candidate[j]表示单个的字母。
                tmp.push_back(result[k] + candidate[j]);
            }
        }
        result.swap(tmp);
    }
    return result;
}

// 0016
int threeSumClosest(vector<int> &nums, int target) {
    if (nums.size() < 3)
        return 0;
    sort(nums.begin(), nums.end());
    int closest = nums[0] + nums[1] + nums[2];

    for (int first = 0; first < nums.size() - 2; ++first) {
        if (first > 0 && nums[first] == nums[first - 1])
            continue;

        int second = first + 1;
        int third = nums.size() - 1;
        while (second < third) {
            int cur_sum = nums[first] + nums[second] + nums[third];
            if (cur_sum == target)
                return cur_sum;
            if (abs(target - cur_sum) < abs(target - closest)) {
                closest = cur_sum;
            }

            // 如果大于目标值，最大值就向左移动；
            // 如果小于目标值，第二个值向右移动。
            if (cur_sum > target) {
                --third;
            } else {
                ++second;
            }
        }
    }
    return closest;
}

// 0015
vector<vector<int>> threeSum(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;

    for (unsigned int i = 0; i < nums.size(); i++) {
        // 剔除重复的字符。
        if ((i > 0) && (nums[i] == nums[i - 1])) {
            continue;
        }
        int l = i + 1;
        int r = nums.size() - 1;

        while (l < r) {
            int s = nums[i] + nums[l] + nums[r];
            if (s > 0)
                r--;
            else if (s < 0)
                l++;
            else {
                res.push_back(vector<int>{
                        nums[i], nums[l], nums[r]});

                while (l < r && nums[l] == nums[l + 1])
                    l++;
                while (l < r && nums[r] == nums[r - 1])
                    r--;

                l++;
                r--;
            }
        }
    }
    return res;
}

// 0014
string longestCommonPrefix(vector<string> &strs) {
    string prefix = "";
    for (int idx = 0; strs.size() > 0; prefix += strs[0][idx], idx++) {
        // 单独比较每个字符串的字符是否相等。
        for (int i = 0; i < strs.size(); i++) {
            if (idx >= strs[i].size() || (i > 0 && strs[i][idx] != strs[i - 1][idx])) {
                return prefix;
            }
        }
    }
    return prefix;
}

// 0013
int romanToInt(string s) {
    unordered_map<char, int> T = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}};

    // 返回最后一个字符。
    int sum = T[s.back()];
    for (int i = s.length() - 2; i >= 0; --i) {
        // 依次计算之前的字符
        if (T[s[i]] < T[s[i + 1]]) {
            sum -= T[s[i]];
        } else {
            sum += T[s[i]];
        }
    }
    return sum;
}

// 0012
string intToRoman(int num) {
    string M[] = {"", "M", "MM", "MMM"};
    string C[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    string X[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" /* 100 - 10 */};
    string I[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

    return M[num / 1000] + C[(num % 1000) / 100] + X[(num % 100) / 10] + I[num % 10];
}

// 0011
int maxArea(vector<int> &height) {
    int water = 0;
    int i = 0, j = height.size() - 1;
    while (i < j) {
        int h = min(height[i], height[j]);
        water = max(water, (j - i) * h);
        while (height[i] <= h && i < j) i++;
        while (height[j] <= h && i < j) j--;
    }
    return water;
}

// 0010
bool isMatch(string s, string p) {

}

// 0009
bool isPalindrome(int x) {
    if (x < 0 || (x != 0 && x % 10 == 0))
        return false;

    int sum = 0;

    while (x > sum) {
        sum = sum * 10 + x % 10;
        x = x / 10;
    }
    return (x == sum) || (x == sum / 10);
}

// 0008
int myAtoi(string str) {
    int sign = 1, base = 0, i = 0;

    // 碰到空白字符就跳过。
    while (str[i] == ' ') {
        i++;
    }

    if (str[i] == '-' || str[i] == '+') {
        // 等于1或者等于-1
        sign = 1 - 2 * (str[i++] == '-');
    }

    while (str[i] >= '0' && str[i] <= '9') {
        // 溢出的情况
        if (base > INT_MAX / 10 || (base == INT_MAX / 10 && str[i] - '0' > 7)) {
            if (sign == 1)
                return INT_MAX;
            else {
                /* code */
                return INT_MIN;
            }
        }
        base = 10 * base + (str[i++] - '0');
    }
    return base * sign;
}

// 0007
int reverse(int x) {
    int reverse = 0;
    bool is_negative = x < 0;
    if (x == INT32_MIN)
        return 0;
    x = abs(x);

    while (x != 0) {
        if (reverse > (INT32_MAX - (x % 10)) / 10)
            return 0;
        reverse = (reverse * 10) + (x % 10);
        x /= 10;
    }
    return is_negative ? -reverse : reverse;
}

// 0006
string convert(string s, int numRows) {
    string result = "";
    if (numRows == 1)
        return s;

    int step1, step2, len = s.size();
    for (int i = 0; i < numRows; ++i) {

        // 每步之间的间隔
        step1 = (numRows - i - 1) * 2;
        step2 = i * 2;

        int pos = i;
        if (pos < len)
            result += s.at(pos);
        while (true) {
            pos += step1;
            if (pos >= len)
                break;
            if (step1)
                result += s.at(pos);

            pos += step2;
            if (pos >= len)
                break;
            if (step2)
                result += s.at(pos);
        }
    }
    return result;
}

// 0005
string longestPalindrome(string s) {
    if (s.size() < 2)
        return s;

    int max_len = 0;
    int start_idx = 0;

    int i = 0;
    while (i < s.size()) {
        int r_ptr = i;
        int l_ptr = i;
        // find the middle of a palindrome
        // 相同的字符肯定是对称形式的，所以不用检查依次跳过。
        while (r_ptr < s.size() - 1 && s[r_ptr] == s[r_ptr + 1]) r_ptr++;
        i = r_ptr + 1;
        // expand from the middle out
        while (r_ptr < s.size() - 1 && l_ptr > 0 && s[r_ptr + 1] == s[l_ptr - 1]) {
            r_ptr++;
            l_ptr--;
        }
        int new_len = r_ptr - l_ptr + 1;
        if (new_len > max_len) {
            start_idx = l_ptr;
            max_len = new_len;
        }
    }
    return s.substr(start_idx, max_len);
}

// 0004
double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {

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
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
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
vector<int> twoSum(vector<int> &nums, int target) {
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

        // number was not found. Put it in the map.
        hash[nums[i]] = i;
    }
    return result;
}

