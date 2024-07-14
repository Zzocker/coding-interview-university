struct SegmentTree {
    inner: Vec<i32>,
    n: usize,
}

impl SegmentTree {
    pub fn new(v: Vec<i32>) -> Self {
        let mut inner = vec![0; 4 * v.len()];
        SegmentTree::build(&mut inner, &v, 0, 0, v.len() - 1);
        SegmentTree { inner, n: v.len() }
    }

    pub fn range_query(&self, l: usize, r: usize) -> i32 {
        return self._range_query(0, 0, self.n - 1, l, r);
    }

    pub fn update(&mut self, index: usize, elem: i32) {
        self._update(0, 0, self.n - 1, index, elem);
    }

    fn build(inner: &mut [i32], v: &[i32], index: usize, l: usize, r: usize) -> i32 {
        if l == r {
            inner[index] = v[l];
            return v[l];
        }
        let mid = (r - l) / 2 + l;
        let left = SegmentTree::build(inner, v, 2 * index + 1, l, mid);
        let right = SegmentTree::build(inner, v, 2 * index + 2, mid + 1, r);
        inner[index] = left + right;
        inner[index]
    }

    fn _range_query(&self, index: usize, l: usize, r: usize, ql: usize, qr: usize) -> i32 {
        if ql == l && qr == r {
            return self.inner[index];
        }
        let mid = (r - l) / 2 + l;
        if qr <= mid {
            return self._range_query(2 * index + 1, l, mid, ql, qr);
        } else if mid < ql {
            return self._range_query(2 * index + 2, mid + 1, r, ql, qr);
        }
        self._range_query(2 * index + 1, l, mid, ql, mid)
            + self._range_query(2 * index + 2, mid + 1, r, mid + 1, qr)
    }

    fn _update(&mut self, index: usize, l: usize, r: usize, update_index: usize, elem: i32) -> i32 {
        if l == r {
            if l == update_index {
                self.inner[index] = elem;
            }
            return self.inner[index];
        }
        let mid = (r - l) / 2 + l;
        let left = self._update(2 * index + 1, l, mid, update_index, elem);
        let right = self._update(2 * index + 2, mid + 1, r, update_index, elem);
        self.inner[index] = left + right;
        self.inner[index]
    }
}

#[cfg(test)]
mod tests {
    use super::SegmentTree;

    #[test]
    fn test_sum_segment_tree() {
        let v = vec![1, 5, 2, 9, 12, 13];
        let mut st = SegmentTree::new(v);
        assert_eq!(st.range_query(1, 4), 28);
        st.update(3, -1);
        assert_eq!(st.range_query(3, 5), 24);
    }
}
