use std::cmp;

#[derive(Debug, Clone, Copy)]
enum Entry {
    Deleted,
    // k, v
    Value((i32, i32)),
}

const DEFAULT_SIZE: usize = 7;

struct HashTable {
    inner: Vec<Option<Entry>>,
    n: usize,
    m: usize,
}

impl HashTable {
    fn new() -> Self {
        Self {
            inner: vec![None; DEFAULT_SIZE],
            n: 0,
            m: DEFAULT_SIZE,
        }
    }

    fn has(&self, k: i32) -> bool {
        let mut index = HashTable::hash(k, self.m);
        let mut entry = self.inner[index];
        while let Some(e) = entry {
            if let Entry::Value((e_k, _)) = e {
                if e_k == k {
                    return true;
                }
            }
            // linear probing
            index = (index + 1) % self.m;
            entry = self.inner[index];
        }
        false
    }

    fn get(&self, k: i32) -> Option<i32> {
        let mut index = HashTable::hash(k, self.m);
        let mut entry = self.inner[index];
        while let Some(e) = entry {
            if let Entry::Value((e_k, e_v)) = e {
                if e_k == k {
                    return Some(e_v);
                }
            }
            // linear probing
            index = (index + 1) % self.m;
            entry = self.inner[index];
        }
        None
    }

    fn remove(&mut self, k: i32) {
        let mut index = HashTable::hash(k, self.m);
        let mut entry = self.inner[index];
        while let Some(e) = entry {
            if let Entry::Value((e_k, e_v)) = e {
                if e_k == k {
                    self.inner[index] = Some(Entry::Deleted);
                    self.n -= 1;
                    break;
                }
            }
            // linear probing
            index = (index + 1) % self.m;
            entry = self.inner[index];
        }
        if 4 * self.n <= self.m {
            self.resize(self.m / 2);
        }
    }

    fn insert(&mut self, k: i32, v: i32) {
        if self.n >= self.m {
            self.resize(2 * self.m);
        }
        let mut index = HashTable::hash(k, self.m);
        let mut entry = self.inner[index];
        while let Some(e) = entry {
            if let Entry::Value((e_k, e_v)) = e {
                if e_k == k {
                    self.inner[index] = Some(Entry::Value((k, v)));
                    return;
                }
            }
            // linear probing
            index = (index + 1) % self.m;
            entry = self.inner[index];
        }
        self.inner[index] = Some(Entry::Value((k, v)));
        self.n += 1;
    }

    fn len(&self) -> usize {
        self.n
    }

    fn resize(&mut self, new_cap: usize) {
        let new_cap = cmp::max(DEFAULT_SIZE, new_cap);
        let mut new_inner = vec![None; new_cap];
        self.inner.iter().for_each(|e| {
            if let Some(Entry::Value((k, v))) = e {
                let mut index = HashTable::hash(*k, new_cap);
                let mut entry = new_inner[index];
                while let Some(e) = entry {
                    index = (index + 1) % new_cap;
                    entry = self.inner[index];
                }
                new_inner[index] = Some(Entry::Value((*k, *v)))
            }
        });
        self.inner = new_inner;
        self.m = new_cap;
    }

    fn hash(mut k: i32, m: usize) -> usize {
        // very simple hash function
        if k < 0 {
            k %= m as i32;
            k += m as i32
        }
        (k as usize) % m
    }
}

#[cfg(test)]
mod tests {
    use super::HashTable;

    #[test]
    fn hash_table() {
        let mut hash_table = HashTable::new();
        assert_eq!(hash_table.len(), 0);

        hash_table.insert(1, 5);
        assert_eq!(hash_table.len(), 1);
        assert!(hash_table.has(1));
        assert_eq!(hash_table.get(1), Some(5));
        hash_table.insert(1, 6);
        assert_eq!(hash_table.get(1), Some(6));

        hash_table.remove(1);
        assert!(!hash_table.has(1));
        assert_eq!(hash_table.get(1), None);

        const N: usize = 64;
        for i in 0..N {
            hash_table.insert(i as i32, (N + i) as i32);
            assert!(hash_table.has(i as i32));
            assert_eq!(hash_table.get(i as i32), Some((N + i) as i32));
        }
        for i in 0..N {
            hash_table.remove(i as i32);
            assert!(!hash_table.has(i as i32));
            assert_eq!(hash_table.get(i as i32), None);
        }
    }
}
