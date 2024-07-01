struct Queue {
    inner: Vec<i32>,
    read: usize,
    write: usize,
}

impl Queue {
    fn new(capacity: usize) -> Self {
        Self {
            inner: vec![0; capacity + 1],
            read: 0,
            write: 0,
        }
    }

    fn is_empty(&self) -> bool {
        self.read == self.write
    }

    fn push(&mut self, elem: i32) {
        let cap = self.inner.len();
        if (self.write + 1) % cap == self.read {
            panic!("cannot push to a full queue")
        }
        self.inner[self.write] = elem;
        self.write = (self.write + 1) % cap;
    }

    fn pop(&mut self) {
        if self.is_empty() {
            panic!("empty queue");
        }
        self.read = (self.read + 1) % self.inner.len();
    }

    fn front(&self) -> i32 {
        if self.is_empty() {
            panic!("empty queue");
        }
        self.inner[self.read]
    }
}

#[cfg(test)]
mod tests {
    use super::Queue;

    #[test]
    fn queue() {
        const CAPACITY: usize = 10;

        let mut queue = Queue::new(CAPACITY);
        assert!(queue.is_empty());
        queue.push(1);
        assert!(!queue.is_empty());
        assert_eq!(queue.front(), 1);
        queue.push(2);
        assert_eq!(queue.front(), 1);

        queue.pop();
        assert_eq!(queue.front(), 2);
    }

    #[test]
    #[should_panic(expected = "cannot push to a full queue")]
    fn queue_push() {
        const CAPACITY: usize = 1;
        let mut queue = Queue::new(CAPACITY);
        queue.push(1);
        queue.push(2);
    }

    #[test]
    #[should_panic(expected = "empty queue")]
    fn queue_pop() {
        const CAPACITY: usize = 1;
        let mut queue = Queue::new(CAPACITY);
        queue.pop();
    }

    #[test]
    #[should_panic(expected = "empty queue")]
    fn queue_front() {
        const CAPACITY: usize = 1;
        let queue = Queue::new(CAPACITY);
        queue.front();
    }
}
