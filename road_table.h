#ifndef ROAD_TABLE_H_
#define ROAD_TABLE_H_

template <typename Tkey, typename Tvalue>
struct crossroad {
	Tkey name;
	Tvalue index;

	crossroad() {}

	crossroad(Tkey n, Tvalue i) {
		this->name = n;
		this->index = i;
	}
};

template <typename Tkey, typename Tvalue> 
class RoadTable {
private:
  std::list<crossroad<Tkey, Tvalue>> *table;
  int size;
  int capacity;
public:

	RoadTable() {
    	this->size = 0;
    	this->capacity = 0;
    	this->table = nullptr;
  	}

  	RoadTable(int capacity) {
    	this->capacity = capacity/5;
    	this->size = 0;
    	this->table = new std::list<crossroad<Tkey, Tvalue>>[capacity];
  	}

  	~RoadTable() {
  		for (int i = 0; i < capacity; ++i) {
  			while (!table[i].empty()) {
  				table[i].pop_back();
  			}
  		}
    	delete [] table;

  	}

  	void put_capacity(int capacity) {
  		this->capacity = capacity/5;
  		this->table = new std::list<struct crossroad<Tkey, Tvalue>>[capacity/5];
  	}

  	int hash_function (Tkey name, int capacity) {
		int k = name.length();
		return k % capacity;
	}

    void put(Tkey key, Tvalue value) {
        int found = 0; // the element has not been found
    	int i = this->hash_function(key, capacity); // calculates hash
    	for (auto it = this->table[i].begin(); it != this->table[i].end(); ++it) {
      		if (it->name == key) {
        	it->index = value;
        	found = 1; // the element has already been added to the hashtable
        	}
    	}  	
    	if (found == 0) {
        	struct crossroad<Tkey,Tvalue> node;
        	node.name = key;
        	node.index = value;
        	this->table[i].push_back(node);
        	size++;
      	}
  	}

  	void remove(Tkey key) {
    	int i = this->hash_function(key, capacity);
    	auto it = this->table[i].begin();
    	for (it = this->table[i].begin(); it != this->table[i].end(); ++it) {
      		if (it->name == key) { // the element exists 
        		break;
      		}
    	}
    	if (it != this->table[i].end()) {
      		this->table[i].erase(it);
    	}
  	}

  	Tvalue get(Tkey key) {
    	int i = this->hash_function(key, capacity);
    	auto it = this->table[i].begin();
    	for (it = table[i].begin(); it != table[i].end(); ++it) {
      		if (it->name == key) { 
        		return it->index; // returns the element
      		}
    	}
    	return Tvalue(); // the element is not in the hashtable
  	}

  	bool has_key(Tkey key) {
    	int i = this->hash_function(key, capacity);
    	auto it = table[i].begin();
    	for (it = table[i].begin(); it != table[i].end(); ++it) {
      		if (it->name == key) {
        		return true; //returns true if the element exists
      		}
    	}
    	return false; // the element does not exist in the hashtable
  	}

  	int get_size() {
    	return size;
  	}

  	int get_capacity() {
    	return capacity;
  	}

  	void print_hashtable() {
    	for (int i = 0; i < capacity; i++) {
     		std::cout << "HASH = " << i << ": ";
      		typename std::list<struct crossroad<Tkey, Tvalue>>::iterator it;
			for (it = table[i].begin(); it != table[i].end(); it++) {
        		std::cout << it->index << " | ";
      		}
      		std::cout << "\n";
    	}
  	}
};

#endif  // ROAD_TABLE_H_