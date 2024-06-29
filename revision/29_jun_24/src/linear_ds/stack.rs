struct Stack(Vec<i32>);

impl Stack {
    fn new() -> Self {
        Self(Vec::new())
    }

    fn is_empty(&self) -> bool {
        self.0.is_empty()
    }

    fn push(&mut self, elem: i32) {
        self.0.push(elem);
    }

    fn pop(&mut self) {
        if self.is_empty() {
            panic!("empty stack")
        }
        self.0.pop();
    }

    fn top(&self) -> i32 {
        if self.is_empty() {
            panic!("empty stack")
        }
        self.0[self.0.len() - 1]
    }
}

#[cfg(test)]
mod tests {
    use super::Stack;

    #[test]
    fn stack() {
        let mut stack = Stack::new();
        assert!(stack.is_empty());
        stack.push(1);
        assert!(!stack.is_empty());
        assert_eq!(stack.top(), 1);
        stack.pop();
        assert!(stack.is_empty());

        const N: usize = 10;
        for i in 0..N {
            stack.push(i as i32);
            assert_eq!(stack.top(), i as i32);
        }
    }
}
