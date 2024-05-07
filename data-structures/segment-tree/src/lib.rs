use std::cmp::{min, max};

#[derive(Debug)]
pub struct SegmentTree<'a>{
    arr: &'a [i32],
    tree_arr: Vec<i32>
}

/// support range based query with O(logn) time complexity
/// updating value at a given index with O(logn) time complexity
impl<'a> SegmentTree<'a> {
    pub fn new(arr: &'a [i32]) -> Self {
        let n = arr.len() as i32;
        let tree_arr = vec![0; 4*(n as usize)];
        let mut tree = SegmentTree {arr, tree_arr: tree_arr};
        tree.build(0, 0, n-1);
        tree
    }

    /// set `value` at provide index
    /// with O(logn) time complexity
    pub fn set(&mut self, index: usize, value: i32) {
        let n = self.arr.len() as i32;
        self.internal_set(index, 0, 0, n-1, value);
    }

    fn internal_set(&mut self,arr_index: usize ,tree_index: usize, left: i32, right: i32, value: i32){
        if left == right {
            self.tree_arr[tree_index] = value;
            return;
        }
        let mid = (right - left)/2 + left;
        if arr_index <= (mid as usize){
            self.internal_set(arr_index, 2*tree_index + 1, left, mid, value);
        }else {
            self.internal_set(arr_index, 2*tree_index + 2, mid+1, right, value);
        }
        self.tree_arr[tree_index] = self.tree_arr[2*tree_index + 1] + self.tree_arr[2*tree_index + 2];
    }

    /// return range query from `left` to `right`
    pub fn get(&self, left: usize, right: usize) -> i32 {
        let n = self.arr.len() as i32;
        self.internal_get(0, 0, n - 1,left as i32, right as i32)
    }

    fn internal_get(&self, tree_index: usize, s_left: i32, s_right: i32 ,left: i32, right: i32) -> i32 {
        if left > right {
            return 0;
        }
        if left == s_left && right == s_right {
            return self.tree_arr[tree_index as usize];
        }
        let mid = (s_right - s_left)/2 + s_left;
        let left_value = self.internal_get(2*tree_index + 1, s_left, mid, left, min(mid, right));
        let right_value = self.internal_get(2*tree_index + 2, mid + 1, s_right, max(mid+1, left), right);
        left_value + right_value
    }

    fn build(&mut self, tree_index: usize, left: i32, right: i32) {
         if left == right {
            self.tree_arr[tree_index] = self.arr[left as usize];
            return;
        }
        let mid = (right - left)/2 + left;
        self.build(2*tree_index + 1, left, mid);
        self.build(2*tree_index + 2, mid + 1, right);
        self.tree_arr[tree_index] = self.tree_arr[2*tree_index + 1] + self.tree_arr[2*tree_index + 2];
    }
}


#[cfg(test)]
mod test{
    use super::*;

    #[test]
    fn test_segment_tree(){
        let vec = vec![1, 2, 3, 4, 5];
        let mut segment_tree = SegmentTree::new(&vec);

        // test get method
        assert_eq!(segment_tree.get(0, 4), 15);

        // test set method
        segment_tree.set(2, 10);
        assert_eq!(segment_tree.get(0,1), 3);
        assert_eq!(segment_tree.get(0,2), 13);
        assert_eq!(segment_tree.get(0,4), 22);
    }
}