/*
    trie: prefix tree

    example: Given array of string `A` = {s_i} and string s
             check if there exists s_i in `A` such that s_i has prefix s
*/

struct TrieNode {
    ending_count: usize,
    child: Vec<Option<Box<TrieNode>>>,
}

impl TrieNode {
    pub fn create_child() -> Vec<Option<Box<TrieNode>>> {
        (0..26).map(|_| None).collect()
    }
}

struct Trie {
    // character, count of string ending at given char
    root: Vec<Option<Box<TrieNode>>>,
}

impl Trie {
    fn new() -> Self {
        Trie {
            root: TrieNode::create_child(),
        }
    }

    pub fn is_empty(&self) -> bool {
        self.root.iter().all(|node| node.is_none())
    }

    pub fn add(&mut self, s: &str) {
        let index = s.chars().nth(0).unwrap() as u8 - b'a';
        let mut root_node = self.root[index as usize]
            .take()
            .unwrap_or(Box::new(TrieNode {
                ending_count: 0,
                child: TrieNode::create_child(),
            }));
        Trie::_add(&mut root_node, s, 0);
        self.root[index as usize] = Some(root_node);
    }

    pub fn remove(&mut self, s: &str) {
        let index = s.chars().nth(0).unwrap() as u8 - b'a';
        let root_node = match self.root[index as usize].take() {
            None => return,
            Some(root_node) => Trie::_remove(root_node, s, 0),
        };
        self.root[index as usize] = root_node;
    }

    fn _remove(mut node: Box<TrieNode>, s: &str, i: usize) -> Option<Box<TrieNode>> {
        if i == s.len() - 1 {
            if node.ending_count == 0 {
                return Some(node);
            } else {
                node.ending_count -= 1;
                if node.ending_count == 0 {
                    return None;
                } else {
                    return Some(node);
                }
            }
        }
        let index = s.chars().nth(i).unwrap() as u8 - b'a';
        let child_node = match node.child[index as usize].take() {
            None => return Some(node),
            Some(child_node) => child_node,
        };
        let child_node = Trie::_remove(child_node, s, i + 1);
        node.child[index as usize] = child_node;

        if node.child.iter().all(|n| n.is_none()) {
            None
        } else {
            Some(node)
        }
    }

    fn _add(node: &mut TrieNode, s: &str, i: usize) {
        if i == s.len() - 1 {
            node.ending_count += 1;
            return;
        }
        let index = s.chars().nth(i).unwrap() as u8 - b'a';
        let mut child_node = node.child[index as usize]
            .take()
            .unwrap_or(Box::new(TrieNode {
                ending_count: 0,
                child: TrieNode::create_child(),
            }));
        Trie::_add(&mut child_node, s, i + 1);
        node.child[index as usize] = Some(child_node);
    }

    // check if there exists element s in trie
    pub fn contains(&self, s: &str) -> bool {
        let index = s.chars().nth(0).unwrap() as u8 - b'a';
        match &self.root[index as usize] {
            None => false,
            Some(child_node) => Trie::_contains(&child_node, s, 0),
        }
    }

    fn _contains(node: &TrieNode, s: &str, i: usize) -> bool {
        if i == s.len() - 1 {
            return node.ending_count > 0;
        }
        let index = s.chars().nth(i).unwrap() as u8 - b'a';
        match &node.child[index as usize] {
            None => false,
            Some(child_node) => Trie::_contains(&child_node, s, i + 1),
        }
    }

    // check if there exists element s_i such that s is prefix of s_i
    pub fn has_prefix(&self, s: &str) -> bool {
        let index = s.chars().nth(0).unwrap() as u8 - b'a';
        match &self.root[index as usize] {
            None => false,
            Some(child_node) => Trie::_has_prefix(&child_node, s, 0),
        }
    }

    fn _has_prefix(node: &TrieNode, s: &str, i: usize) -> bool {
        if i == s.len() {
            return true;
        }
        let index = s.chars().nth(i).unwrap() as u8 - b'a';
        match &node.child[index as usize] {
            None => false,
            Some(child_node) => Trie::_has_prefix(&child_node, s, i + 1),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::Trie;

    #[test]
    fn test_trie() {
        let mut trie = Trie::new();

        assert!(trie.is_empty());
        trie.add("abcd");
        trie.add("abef");
        trie.add("bfe");

        assert!(trie.contains("abcd"));
        assert!(!trie.contains("ab"));
        assert!(!trie.contains("abcdf"));
        assert!(trie.has_prefix("abc"));
        assert!(!trie.has_prefix("abt"));

        trie.remove("abcde");
        trie.remove("abef");
        assert!(!trie.contains("abef"));
        assert!(trie.has_prefix("abc"));
        assert!(trie.contains("abcd"));
    }
}
