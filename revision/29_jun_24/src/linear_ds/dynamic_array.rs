use std::{
    alloc::{alloc, dealloc, Layout},
    cmp, ptr,
};

const DEFAULT_BUCKET_SIZE: usize = 8;

struct DynamicArray {
    bucket: *mut i32,
    capacity: usize,
    size: usize,
}

impl DynamicArray {
    fn new() -> Self {
        let layout = Layout::array::<i32>(DEFAULT_BUCKET_SIZE).unwrap();
        let bucket = unsafe { alloc(layout) as *mut i32 };
        Self {
            bucket,
            capacity: DEFAULT_BUCKET_SIZE,
            size: 0,
        }
    }

    fn is_empty(&self) -> bool {
        self.size == 0
    }

    fn size(&self) -> usize {
        self.size
    }

    fn capacity(&self) -> usize {
        self.capacity
    }

    fn push(&mut self, elem: i32) {
        if self.size == self.capacity {
            self._resize(2 * self.capacity);
        }
        unsafe {
            ptr::write(self.bucket.add(self.size), elem);
        }
        self.size += 1;
    }

    fn at(&self, index: usize) -> i32 {
        if index >= self.size {
            panic!("index out of bound");
        }
        unsafe { ptr::read(self.bucket.add(index)) }
    }

    fn set(&mut self, index: usize, elem: i32) {
        if index == self.size {
            panic!("index out of bound");
        }
        unsafe { ptr::write(self.bucket.add(index), elem) }
    }
    fn remove(&mut self, index: usize) {
        if self.is_empty() {
            panic!("array is empty");
        }
        if index >= self.size {
            panic!("index out of bound");
        }
        for i in index..self.size - 1 {
            unsafe { ptr::write(self.bucket.add(i), ptr::read(self.bucket.add(i + 1))) }
        }
        self.size -= 1;
        if 4 * self.size <= self.capacity {
            self._resize(self.capacity / 2);
        }
    }

    fn _resize(&mut self, new_cap: usize) {
        let new_cap = cmp::max(DEFAULT_BUCKET_SIZE, new_cap);
        let layout = Layout::array::<i32>(new_cap).unwrap();
        let new_bucket = unsafe { alloc(layout) as *mut i32 };
        for i in 0..self.size {
            unsafe { ptr::write(new_bucket.add(i), ptr::read(self.bucket.add(i))) }
        }
        unsafe {
            dealloc(
                self.bucket as *mut u8,
                Layout::array::<i32>(self.capacity).unwrap(),
            );
        }
        self.bucket = new_bucket;
        self.capacity = new_cap;
    }
}

impl Drop for DynamicArray {
    fn drop(&mut self) {
        unsafe {
            dealloc(
                self.bucket as *mut u8,
                Layout::array::<i32>(self.capacity).unwrap(),
            )
        }
    }
}

#[cfg(test)]
mod tests {

    use super::{DynamicArray, DEFAULT_BUCKET_SIZE};

    #[test]
    fn basic_dynamic_array() {
        let mut array = DynamicArray::new();
        assert!(array.is_empty());
        assert_eq!(array.size(), 0);
        assert_eq!(array.capacity(), DEFAULT_BUCKET_SIZE);
        array.push(1);
        assert!(!array.is_empty());
        assert_eq!(array.size(), 1);
        assert_eq!(array.at(0), 1);
        array.set(0, 9);
        assert_eq!(array.at(0), 9);
    }

    #[test]
    fn amortization_expand() {
        let mut array = DynamicArray::new();
        for i in 0..DEFAULT_BUCKET_SIZE {
            array.push(i as i32);
            assert_eq!(array.size(), i + 1);
            assert_eq!(array.capacity(), DEFAULT_BUCKET_SIZE);
        }
        array.push(98);
        assert_eq!(array.size(), DEFAULT_BUCKET_SIZE + 1);
        assert_eq!(array.capacity(), 2 * DEFAULT_BUCKET_SIZE);
    }

    #[test]
    fn amortization_shrink() {
        let mut array = DynamicArray::new();
        for i in 0..=DEFAULT_BUCKET_SIZE {
            array.push(i as i32);
        }
        while 2*(array.size()-1) > /* cap/4 */ DEFAULT_BUCKET_SIZE {
            println!("{} {}", array.size(), array.at(array.size() - 1));
            array.remove(array.size() - 1);
            assert_eq!(array.capacity(), 2 * DEFAULT_BUCKET_SIZE);
        }
        array.remove(array.size() - 1);
        assert_eq!(array.capacity(), DEFAULT_BUCKET_SIZE);
    }
}
