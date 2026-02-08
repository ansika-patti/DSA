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