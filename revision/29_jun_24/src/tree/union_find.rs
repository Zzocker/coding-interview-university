use std::collections::HashMap;

struct UnionFind {
    parent: HashMap<i32, i32>,
    size: HashMap<i32, usize>,
}

impl UnionFind {
    fn new() -> Self {
        UnionFind {
            parent: HashMap::new(),
            size: HashMap::new(),
        }
    }

    fn create_set(&mut self, u: i32) {
        self.parent.insert(u, u);
        self.size.insert(u, 1);
    }

    fn find_set(&mut self, u: i32) -> i32 {
        let parent = *self.parent.get(&u).expect("set not found");
        if parent == u {
            return u;
        }
        let parent = self.find_set(self.parent[&u]);
        self.parent.insert(u, parent);
        return parent;
    }

    fn union_set(&mut self, u: i32, v: i32) {
        let u = self.find_set(u);
        let v = self.find_set(v);
        if u != v {
            let u_size = self.size.get(&u).unwrap();
            let v_size = self.size.get(&v).unwrap();
            if u_size > v_size {
                self.parent.insert(v, u);
                self.size.insert(u, u_size + v_size);
            } else {
                self.parent.insert(u, v);
                self.size.insert(v, u_size + v_size);
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::UnionFind;

    #[test]
    fn test_union_find() {
        let mut uf = UnionFind::new();

        uf.create_set(0);
        assert_eq!(uf.find_set(0), 0);

        for i in 1..=5 {
            uf.create_set(i);
        }

        uf.union_set(1, 3);
        uf.union_set(3, 5);
        assert_eq!(uf.find_set(1), uf.find_set(3));
        assert_eq!(uf.find_set(3), uf.find_set(5));
        assert_eq!(uf.find_set(1), uf.find_set(5));
    }
}
