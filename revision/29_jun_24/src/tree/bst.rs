use std::collections::VecDeque;

struct TreeNode {
    val: i32,
    left: Option<Box<TreeNode>>,
    right: Option<Box<TreeNode>>,
}

struct Tree {
    root: Option<Box<TreeNode>>,
}

impl Tree {
    fn new() -> Self {
        Self { root: None }
    }

    fn is_empty(&self) -> bool {
        self.root.is_none()
    }

    fn has(&self, val: i32) -> bool {
        Tree::_has(self.root.as_ref(), val)
    }

    fn _has(node: Option<&Box<TreeNode>>, val: i32) -> bool {
        match node {
            None => false,
            Some(node) => {
                if node.val == val {
                    true
                } else if val < node.val {
                    Tree::_has(node.left.as_ref(), val)
                } else {
                    Tree::_has(node.right.as_ref(), val)
                }
            }
        }
    }

    fn insert(&mut self, val: i32) {
        self.root = Tree::_insert(self.root.take(), val);
    }

    fn _insert(node: Option<Box<TreeNode>>, val: i32) -> Option<Box<TreeNode>> {
        match node {
            None => Some(Box::new(TreeNode {
                val,
                left: None,
                right: None,
            })),
            Some(mut node) => {
                if val < node.val {
                    node.left = Tree::_insert(node.left.take(), val);
                } else if val > node.val {
                    node.right = Tree::_insert(node.right.take(), val)
                }
                Some(node)
            }
        }
    }

    fn remove(&mut self, val: i32) {
        self.root = Tree::_remove(self.root.take(), val);
    }

    fn _remove(node: Option<Box<TreeNode>>, val: i32) -> Option<Box<TreeNode>> {
        match node {
            None => node,
            Some(mut node) => {
                if val == node.val {
                    if node.left.is_none() && node.right.is_none() {
                        return None;
                    } else if node.left.is_none() {
                        return node.right;
                    } else if node.right.is_none() {
                        return node.left;
                    } else {
                        let left_greatest = Tree::_find_greatest(node.left.as_ref().unwrap());
                        node.val = left_greatest;
                        node.left = Tree::_remove(node.left.take(), left_greatest);
                    }
                } else if val < node.val {
                    node.left = Tree::_remove(node.left.take(), val);
                } else {
                    node.right = Tree::_remove(node.right.take(), val);
                }
                Some(node)
            }
        }
    }

    fn _find_greatest(node: &Box<TreeNode>) -> i32 {
        match node.right.as_ref() {
            None => node.val,
            Some(right) => Tree::_find_greatest(right),
        }
    }

    // give sorted array
    fn in_order(&self) -> Vec<i32> {
        let mut out = Vec::new();
        Tree::_in_order(self.root.as_ref(), &mut out);
        out
    }

    fn _in_order(node: Option<&Box<TreeNode>>, out: &mut Vec<i32>) {
        if let Some(node) = node {
            Tree::_in_order(node.left.as_ref(), out);
            out.push(node.val);
            Tree::_in_order(node.right.as_ref(), out);
        }
    }

    fn pre_order(&self) -> Vec<i32> {
        let mut out = Vec::new();
        Tree::_pre_order(self.root.as_ref(), &mut out);
        out
    }

    fn _pre_order(node: Option<&Box<TreeNode>>, out: &mut Vec<i32>) {
        if let Some(node) = node {
            out.push(node.val);
            Tree::_pre_order(node.left.as_ref(), out);
            Tree::_pre_order(node.right.as_ref(), out);
        }
    }

    fn post_order(&self) -> Vec<i32> {
        let mut out = Vec::new();
        Tree::_post_order(self.root.as_ref(), &mut out);
        out
    }

    fn _post_order(node: Option<&Box<TreeNode>>, out: &mut Vec<i32>) {
        if let Some(node) = node {
            Tree::_post_order(node.left.as_ref(), out);
            Tree::_post_order(node.right.as_ref(), out);
            out.push(node.val);
        }
    }

    fn bfs(&self) -> Vec<i32> {
        let mut queue: VecDeque<&Box<TreeNode>> = VecDeque::new();
        if let Some(node) = self.root.as_ref() {
            queue.push_back(node);
        }
        let mut out = Vec::new();
        while let Some(node) = queue.pop_front() {
            out.push(node.val);
            if let Some(left) = node.left.as_ref() {
                queue.push_back(left);
            }
            if let Some(right) = node.right.as_ref() {
                queue.push_back(right);
            }
        }
        out
    }
}

#[cfg(test)]
mod tests {
    use super::Tree;

    #[test]
    fn tree_insert() {
        let mut tree = Tree::new();

        assert!(tree.is_empty());
        assert!(!tree.has(-1));

        tree.insert(5);
        tree.insert(0);
        tree.insert(10);
        assert!(tree.has(10));
        assert!(tree.has(5));
        assert!(tree.has(0));
        assert!(!tree.has(9));
    }

    #[test]
    fn tree_remove() {
        let mut tree = Tree::new();

        let node_v = [5, 0, 10, -1, 2, 7, 11];
        for v in node_v {
            tree.insert(v);
        }

        // remove leaf
        tree.remove(7);
        assert!(!tree.has(7));

        // remove node with single child
        tree.remove(10);
        assert!(!tree.has(10));

        // remove node with two child
        tree.remove(0);
        assert!(!tree.has(0));

        assert_eq!(tree.in_order(), vec![-1, 2, 5, 11]);
    }

    #[test]
    fn tree_traversal() {
        let mut tree = Tree::new();

        let node_v = [5, 0, 10, -1, 2, 7, 11];
        for v in node_v {
            tree.insert(v);
        }

        assert_eq!(tree.in_order(), vec![-1, 0, 2, 5, 7, 10, 11]);
        assert_eq!(tree.pre_order(), vec![5, 0, -1, 2, 10, 7, 11]);
        assert_eq!(tree.post_order(), vec![-1, 2, 0, 7, 11, 10, 5]);
        assert_eq!(tree.bfs(), vec![5, 0, 10, -1, 2, 7, 11]);
    }
}
