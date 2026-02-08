/*
 * Problem: Reverse Pairs (LeetCode 493)
 * 
 * Approach:
 * - Uses a modified Merge Sort algorithm (Divide & Conquer).
 * - During the merge step, counts "reverse pairs" where:
 *      arr[i] > 2 * arr[j]  with i < j.
 * - The counting is done before merging, using a two-pointer scan
 *   across the sorted left and right halves.
 * - After counting, the halves are merged to maintain sorted order.
 * 
 * Complexity:
 * - Time: O(n log n), due to merge sort recursion and linear counting per merge.
 * - Space: O(n), for temporary arrays during merging.
 * 
 * Key Notes:
 * - Uses long long to avoid overflow when checking arr[i] > 2 * arr[j].
 * - Ensures correctness by counting cross pairs before merging.
 * - Optimal solution compared to brute force O(n^2).
 */

class Solution {
public:
    // Merge two sorted halves of arr[low..mid] and arr[mid+1..high]
    void merge(vector<int> &arr, int low, int mid, int high){
        vector<int> temp;
        int left = low;
        int right = mid+1;

        // Merge while both halves have elements
        while(left<=mid && right<=high){
            if(arr[left] <= arr[right]){
                temp.push_back(arr[left]);
                left++;
            }
            else{
                temp.push_back(arr[right]);
                right++;
            }
        }

        // Copy remaining elements from left half
        while(left<=mid){
            temp.push_back(arr[left]);
            left++;
        }

        // Copy remaining elements from right half
        while(right<=high){
            temp.push_back(arr[right]);
            right++;
        }

        // Copy merged result back into arr
        for(int i=low; i<=high; i++){
            arr[i] = temp[i-low];
        }
    }

    // Count reverse pairs across the split
    int countPairs(vector<int> &arr, int low, int mid, int high){
        int right = mid+1, cnt = 0;
        for(int i=low; i<=mid; i++){
            while(right<=high && (long long)arr[i] > 2LL * arr[right]){
                right++;
            }
            cnt += (right-mid-1);
        }
        return cnt;
    }

    // Modified merge sort that counts reverse pairs
    int mergeSort(vector<int> &arr, int low, int high){
        int cnt=0;
        if(low>=high) return cnt;
        int mid = (low+high)/2;
        cnt += mergeSort(arr, low, mid);
        cnt += mergeSort(arr, mid+1, high);
        cnt += countPairs(arr, low, mid, high);
        merge(arr, low, mid, high);
        return cnt;
    }

    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        return mergeSort(nums, 0, n-1);
    }
};