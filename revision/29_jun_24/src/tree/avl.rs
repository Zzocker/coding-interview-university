use std::cmp;

struct AVLNode {
    v: i32,
    left_child: Option<Box<AVLNode>>,
    right_child: Option<Box<AVLNode>>,
    height: usize,
}

struct AVL {
    root: Option<Box<AVLNode>>,
}

impl AVL {
    fn new() -> Self {
        AVL { root: None }
    }

    fn is_empty(&self) -> bool {
        self.root.is_none()
    }

    fn insert(&mut self, elem: i32) {
        self.root = AVL::_insert(self.root.take(), elem);
    }
    fn remove(&mut self, elem: i32) {
        self.root = AVL::_remove(self.root.take(), elem);
    }
    fn exists(&self, elem: i32) -> bool {
        AVL::_exists(&self.root, elem)
    }

    fn _exists(node: &Option<Box<AVLNode>>, elem: i32) -> bool {
        match node {
            Some(n) => {
                if n.v == elem {
                    true
                } else if elem < n.v {
                    AVL::_exists(&n.left_child, elem)
                } else {
                    AVL::_exists(&n.right_child, elem)
                }
            }
            None => false,
        }
    }

    fn _insert(node: Option<Box<AVLNode>>, elem: i32) -> Option<Box<AVLNode>> {
        match node {
            None => Some(Box::new(AVLNode {
                v: elem,
                left_child: None,
                right_child: None,
                height: 0,
            })),
            Some(mut node) => {
                if elem < node.v {
                    node.left_child = AVL::_insert(node.left_child.take(), elem);
                } else if elem > node.v {
                    node.right_child = AVL::_insert(node.right_child.take(), elem);
                }
                Some(AVL::balance(node))
            }
        }
    }

    fn _remove(node: Option<Box<AVLNode>>, elem: i32) -> Option<Box<AVLNode>> {
        match node {
            None => None,
            Some(mut node) => {
                if node.v == elem {
                    if node.left_child.is_none() && node.right_child.is_none() {
                        return None;
                    } else if node.left_child.is_none() {
                        return Some(AVL::balance(node.right_child.unwrap()));
                    } else if node.right_child.is_none() {
                        return Some(AVL::balance(node.left_child.unwrap()));
                    } else {
                        let left_greatest = AVL::find_greatest(node.left_child.as_ref().unwrap());
                        node.v = left_greatest;
                        node.left_child = AVL::_remove(node.left_child.take(), left_greatest);
                    }
                } else if elem < node.v {
                    node.left_child = AVL::_remove(node.left_child.take(), elem);
                } else {
                    node.right_child = AVL::_remove(node.right_child.take(), elem);
                }
                Some(AVL::balance(node))
            }
        }
    }

    fn find_greatest(node: &Box<AVLNode>) -> i32 {
        match node.right_child.as_ref() {
            None => node.v,
            Some(right) => AVL::find_greatest(right),
        }
    }

    fn rotate_ll(mut node: Box<AVLNode>) -> Box<AVLNode> {
        let mut a = node;
        let mut b = a.left_child.take().unwrap();
        let b_r = b.right_child.take();
        // fix a
        a.left_child = b_r;
        a.height = AVL::get_height(&a);
        // fix b
        b.right_child = Some(a);
        b.height = AVL::get_height(&b);
        b
    }

    fn rotate_lr(node: Box<AVLNode>) -> Box<AVLNode> {
        let mut a = node;
        let mut b = a.left_child.take().unwrap();
        let mut c = b.right_child.take().unwrap();
        let c_l = c.left_child.take();
        let c_r = c.right_child.take();
        // fix a
        a.left_child = c_r;
        a.height = AVL::get_height(&a);
        // fix b
        b.right_child = c_l;
        b.height = AVL::get_height(&b);
        // fix c
        c.left_child = Some(b);
        c.right_child = Some(a);
        c.height = AVL::get_height(&c);
        c
    }

    fn rotate_rl(node: Box<AVLNode>) -> Box<AVLNode> {
        let mut a = node;
        let mut b = a.right_child.take().unwrap();
        let mut c = b.left_child.take().unwrap();
        let c_l = c.left_child.take();
        let c_r = c.right_child.take();
        // fix a
        a.right_child = c_l;
        a.height = AVL::get_height(&a);
        // fix b
        b.left_child = c_r;
        b.height = AVL::get_height(&b);
        // fix c
        c.left_child = Some(a);
        c.right_child = Some(b);
        c.height = AVL::get_height(&c);
        c
    }

    fn rotate_rr(node: Box<AVLNode>) -> Box<AVLNode> {
        let mut a = node;
        let mut b: Box<AVLNode> = a.right_child.take().unwrap();
        let b_l = b.left_child.take();
        // fix a
        a.right_child = b_l;
        a.height = AVL::get_height(&a);
        // fix b
        b.left_child = Some(a);
        b.height = AVL::get_height(&b);
        b
    }

    fn balance(mut node: Box<AVLNode>) -> Box<AVLNode> {
        if AVL::get_balance_factor(&node) == 2 {
            // L
            if AVL::get_balance_factor(node.left_child.as_ref().unwrap()) == 1 {
                // LL
                return AVL::rotate_ll(node);
            } else if AVL::get_balance_factor(node.left_child.as_ref().unwrap()) == -1 {
                // LR
                return AVL::rotate_lr(node);
            }
        } else if AVL::get_balance_factor(&node) == -2 {
            // R
            if AVL::get_balance_factor(node.right_child.as_ref().unwrap()) == 1 {
                // RL
                return AVL::rotate_rl(node);
            } else if AVL::get_balance_factor(node.right_child.as_ref().unwrap()) == -1 {
                // RR
                return AVL::rotate_rr(node);
            }
        }
        node.height = AVL::get_height(&node);
        node
    }

    fn get_balance_factor(node: &Box<AVLNode>) -> i32 {
        // +1 for edge between node and child
        let left: i32 = node.left_child.as_ref().map(|n| n.height + 1).unwrap_or(0) as i32;
        let right: i32 = node.right_child.as_ref().map(|n| n.height + 1).unwrap_or(0) as i32;
        left - right
    }

    fn get_height(node: &Box<AVLNode>) -> usize {
        let left = node
            .left_child
            .as_ref()
            .map(|n| n.height as i32)
            .unwrap_or(-1);
        let right = node
            .right_child
            .as_ref()
            .map(|n| n.height as i32)
            .unwrap_or(-1);
        (1 + cmp::max(left, right)) as usize
    }

    fn in_order(&self) -> Vec<i32> {
        let mut out = Vec::new();
        AVL::_in_order(self.root.as_ref(), &mut out);
        out
    }

    fn _in_order(node: Option<&Box<AVLNode>>, out: &mut Vec<i32>) {
        if let Some(node) = node {
            AVL::_in_order(node.left_child.as_ref(), out);
            out.push(node.v);
            AVL::_in_order(node.right_child.as_ref(), out);
        }
    }
}

#[cfg(test)]
mod tests {
    use super::AVL;

    #[test]
    fn test_avl_insert() {
        let mut avl = AVL::new();
        assert!(avl.is_empty());
        avl.insert(4);
        avl.insert(3);
        avl.insert(2);
        assert!(!avl.is_empty());
        assert!(avl.exists(4));
        assert!(avl.exists(3));
        assert!(avl.exists(2));

        avl.insert(-9);
        avl.insert(-7);
        assert!(avl.exists(-9));
        assert!(avl.exists(-7));

        avl.insert(9);
        avl.insert(6);
        assert!(avl.exists(9));
        assert!(avl.exists(6));

        avl.insert(10);
        avl.insert(11);
        assert!(avl.exists(10));
        assert!(avl.exists(11));
    }

    #[test]
    fn test_avl_remove() {
        let mut avl = AVL::new();
        avl.insert(4);
        avl.insert(3);
        avl.insert(2);

        avl.insert(-9);
        avl.insert(-7);

        avl.insert(9);
        avl.insert(6);

        avl.insert(10);
        avl.insert(11);

        avl.remove(10);
        assert!(!avl.exists(10));

        avl.remove(4);
        assert!(!avl.exists(4));

        avl.remove(-9);
        avl.remove(-7);
        avl.remove(2);
        assert!(!avl.exists(-9));
        assert!(!avl.exists(-7));
        assert!(!avl.exists(2));
    }
}
