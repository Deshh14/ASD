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
	for (int i = 0; i < _size; i++) {
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

void DSU::unite(int a, int b) {
	int rootA = find(a);
	int rootB = find(b);
	if (rootA == rootB) return;
	if (_rank[rootA] < _rank[rootB]) {
		_parent[rootA] = rootB;
	}
	else if (_rank[rootA] > _rank[rootB]) {
		_parent[rootB] = rootA;
	}
	else {
		_parent[rootB] = rootA;
		_rank[rootA]++;
	}
}