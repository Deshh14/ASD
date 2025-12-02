class DSU {
    int* _parent;
    size_t _size;
    int* _rank;

public:
    DSU(size_t size);
    void unite(int, int);
    int find(int);
    ~DSU();
};

DSU::DSU(size_t size) : _size(size) {
    _parent = new int[_size];
    _rank = new int[_size];
    for (size_t i = 0; i < _size; i++) {
        _parent[i] = i;
        _rank[i] = 0;  
    }
}

DSU::~DSU() {
    delete[] _parent;
    delete[] _rank;    
}

int DSU::find(int x) {
    if (_parent[x] != x) {
        _parent[x] = find(_parent[x]);  
    }
    return _parent[x];
}

void DSU::unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) {
        return;
    }

    if (_rank[rootX] < _rank[rootY]) {
        _parent[rootX] = rootY;
    }
    else if (_rank[rootX] > _rank[rootY]) {
        _parent[rootY] = rootX;
    }
    else {
        _parent[rootY] = rootX;
        _rank[rootX]++;
    }
}