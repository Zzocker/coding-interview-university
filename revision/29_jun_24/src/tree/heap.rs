struct Heap {
    inner: Vec<i32>,
}

impl Heap {
    fn new() -> Self {
        Self { inner: Vec::new() }
    }

    fn move_up(v: &mut [i32], index: usize) {
        let value = v[index];
        let mut child = index as i32;
        let mut parent = (child - 1) / 2;
        while child > 0 && value > v[parent as usize] {
            v[child as usize] = v[parent as usize];
            child = parent;
            parent = (child - 1) / 2
        }
        v[child as usize] = value;
    }

    fn move_down(v: &mut [i32], size: usize) {
        let size = size as i32;
        let value = v[0];
        let mut parent: i32 = 0;
        let mut left_child = 2 * parent + 1;
        let mut right_child = 2 * parent + 2;
        loop {
            if left_child <= size - 1 && right_child <= size - 1 {
                if v[left_child as usize] > value && v[right_child as usize] > value {
                    if v[left_child as usize] > v[right_child as usize] {
                        v[parent as usize] = v[left_child as usize];
                        parent = left_child;
                    } else {
                        v[parent as usize] = v[right_child as usize];
                        parent = right_child;
                    }
                } else if v[left_child as usize] > value {
                    v[parent as usize] = v[left_child as usize];
                    parent = left_child;
                } else if v[right_child as usize] > value {
                    v[parent as usize] = v[right_child as usize];
                    parent = right_child;
                } else {
                    break;
                }
            } else if left_child <= size - 1 && v[left_child as usize] > value {
                v[parent as usize] = v[left_child as usize];
                parent = left_child;
            } else if right_child <= size - 1 && v[right_child as usize] > value {
                v[parent as usize] = v[right_child as usize];
                parent = right_child;
            } else {
                break;
            }
            left_child = 2 * parent + 1;
            right_child = 2 * parent + 2;
        }
        v[parent as usize] = value;
    }

    fn is_empty(&self) -> bool {
        self.inner.len() == 0
    }

    fn push(&mut self, elem: i32) {
        self.inner.push(elem);
        let index = self.inner.len() - 1;
        Heap::move_up(&mut self.inner, index);
    }

    fn pop(&mut self) {
        if self.is_empty() {
            panic!("heap is empty")
        }
        self.inner[0] = *self.inner.last().unwrap();
        self.inner.pop();
        let size = self.inner.len();
        Heap::move_down(&mut self.inner, size);
    }

    fn top(&self) -> i32 {
        if self.is_empty() {
            panic!("heap is empty");
        }
        self.inner[0]
    }

    // use heap_sort to sort
    // provided vector `a`
    fn sort(v: &mut Vec<i32>) {
        for i in 1..v.len() {
            Heap::move_up(v, i);
        }
        let mut size = v.len();
        for _ in 0..v.len() {
            let top = v[0];
            v[0] = v[size - 1];
            v[size - 1] = top;
            size -= 1;
            Heap::move_down(v, size);
        }
    }
}

#[cfg(test)]
mod tests {
    use super::Heap;

    #[test]
    fn heap_operations() {
        let mut heap = Heap::new();
        assert!(heap.is_empty());

        heap.push(2);
        assert_eq!(heap.top(), 2);

        heap.push(5);
        assert_eq!(heap.top(), 5);

        heap.push(3);
        assert_eq!(heap.top(), 5);

        heap.pop();
        assert_eq!(heap.top(), 3);
    }

    #[test]
    fn heap_sort() {
        let mut v = vec![9, 3, 8, 10, 2, 4];
        Heap::sort(&mut v);
        assert_eq!(v, vec![2, 3, 4, 8, 9, 10])
    }
}
