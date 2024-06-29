struct ListNode {
    val: i32,
    next: Option<Box<ListNode>>,
}

struct LinkedList {
    aux: Box<ListNode>,
}

impl LinkedList {
    fn new() -> Self {
        LinkedList {
            aux: Box::new(ListNode { val: 0, next: None }),
        }
    }

    fn is_empty(&self) -> bool {
        self.aux.next.is_none()
    }

    fn push(&mut self, val: i32) {
        self.aux.next = Some(match self.aux.next.take() {
            None => Box::new(ListNode { val, next: None }),
            Some(head) => Box::new(ListNode {
                val,
                next: Some(head),
            }),
        })
    }

    fn pop(&mut self) {
        match self.aux.next.take() {
            None => panic!("empty linked list"),
            Some(mut head) => self.aux.next = head.next.take(),
        }
    }

    fn front(&self) -> i32 {
        if self.is_empty() {
            panic!("empty linked list");
        }
        match &self.aux.next {
            None => panic!("empty linked list"),
            Some(head) => head.val,
        }
    }

    fn reverse(&mut self) {
        let mut new_head = None;
        let mut head = self.aux.next.take();
        while let Some(mut head_val) = head {
            let next = head_val.next;
            head_val.next = None;
            match new_head.take() {
                None => new_head = Some(head_val),
                Some(new_head_val) => {
                    head_val.next = Some(new_head_val);
                    new_head = Some(head_val);
                }
            }
            head = next;
        }
        self.aux.next = new_head;
    }
}

impl Drop for LinkedList {
    fn drop(&mut self) {
        while !self.is_empty() {
            self.pop();
        }
    }
}

#[cfg(test)]
mod tests {

    use super::*;

    #[test]
    fn linked_list() {
        let mut list = LinkedList::new();
        assert!(list.is_empty());
        list.push(1);
        assert!(!list.is_empty());
        assert_eq!(list.front(), 1);
        list.pop();
        assert!(list.is_empty());

        const N: usize = 10;
        for i in 0..N {
            list.push(i as i32);
        }
        list.reverse();
        for i in 0..N {
            assert_eq!(list.front(), i as i32);
            list.pop();
        }
        assert!(list.is_empty());
    }
}
