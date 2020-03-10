#ifndef ROAD_GRAPH_H_
#define ROAD_GRAPH_H_

#include "./driver.h"

template <typename Tvalue>
class RoadGraph {
private:
    std::vector<std::vector<int>> nodes;
    int size;

public:
    // Constructor
    RoadGraph () {
    	size = 0;
    }

    RoadGraph(int size) {
        this->size = size;
        nodes.resize(size);
        for (int i = 0; i < nodes.size(); ++i) {
            nodes[i].resize(size);
        }
    }

    // Destructor
    ~RoadGraph() {
    // 	for (int i = 0; i < size; ++i) {
  		// 	while (!nodes[i].empty()) {
  		// 		nodes[i].pop_back();
  		// 	}
  		// }
    	//delete [] nodes;
    // 	for (int i = 0; i < size; ++i) {
  		// 	while (!neigh[i].empty()) {
  		// 		neigh[i].pop_back();
  		// 	}
  		// }
    // 	delete [] neigh;
    }

    void put_nodes(int size) {
  		this->size = size;
        nodes.resize(size);
        for (int i = 0; i < nodes.size(); ++i) {
            nodes[i].resize(size);
        }
  		//this->nodes = new std::list<Tvalue>[size];
  		// neigh = new std::list<Tvalue>[size];
  	}

    void addRoad(Tvalue src, Tvalue dst) {
    	this->nodes[src][dst] = 1;
     //    int found = 0; // the element has not been found
     //    Tvalue i = src, j = dst;
    	// for (auto it = this->nodes[i].begin(); it != this->nodes[i].end(); ++it) {
     //  		if (*it == dst) {
     //    		found = 1; // the element has already been added to the graph
     //    	}
    	// }
    	// if (found == 0) {
     //    	this->nodes[i].push_back(dst);
     //  	}
     //  	found = 0;
     //  	for (auto it = neigh[j].begin(); it != neigh[j].end(); ++it) {
     //  		if (*it == src) {
     //    		found = 1; // the element has already been added to the graph
     //    	}
    	// }
    	// if (found == 0) {
     //    	neigh[j].push_back(src);
     //  	}
    }

    void removeRoad(Tvalue src, Tvalue dst) {
    	this->nodes[src][dst] = 0;
     //    Tvalue i = src , j = dst;
    	// auto it = this->nodes[i].begin();
    	// for (it = this->nodes[i].begin(); it != this->nodes[i].end(); ++it) {
     //  		if (*it == dst) { // the element has been found
     //    		break;
     //  		}
    	// }
    	// if (it != this->nodes[i].end()) {
     //  		this->nodes[i].erase(it);
    	// }
    	// for (it = this->neigh[j].begin(); it != this->neigh[j].end(); ++it) {
     //  		if (*it == src) { // the element has been found
     //    		break;
     //  		}
    	// }
    	// if (it != this->neigh[i].end()) {
     //  		this->neigh[i].erase(it);
    	// }
    }

    bool hasRoad(Tvalue src, Tvalue dst) {
        Tvalue i = src;
        if (src == dst) {
        	return true;
        }
        if (this->nodes[src][dst] == 1) {
        	return true;
        }
    	// auto it = this->nodes[i].begin();
    	// for (it = this->nodes[i].begin(); it != this->nodes[i].end(); ++it) {
     //  		if (*it == dst) {
     //    		return true; //returns true if the element exists
     //  		}
    	// }
    	return false; // the element does not exist
    }

    int getSize() {
        return size;
    }

   //  void print_streets(std::ofstream& fout) {
   //  	for (int i = 0; i < size; i++) {
   //   		fout << "node = " << i << ": ";
			// for (auto it = nodes[i].begin(); it != nodes[i].end(); it++) {
   //      		fout << *it << " | ";
   //    		}
   //    		fout << "\n";
   //  	}
  	// }

  	std::vector<Tvalue> getNeighbors(Tvalue node) {
        std::vector<Tvalue> ngh;
        //int size = 0;
        // for (auto it = nodes[node].begin(); it != nodes[node].end(); it++) {
        // 	//size++;
        // 	//ngh.resize(size);
        // 	ngh.push_back(*it);
        // }

        for (int i = 0; i < size; ++i) {
            if (nodes[node][i] == 1) {
                ngh.push_back(i);
            }
        }
        return ngh;
    }

    std::vector<Tvalue> getReverseNeighbors(Tvalue node) {
    	std::vector<Tvalue> reverse_neigh;
    	// for (auto it = neigh[node].begin(); it != neigh[node].end(); it++) {
    	// 	reverse_neigh.push_back(*it);
    	// }
   //  	for (int i = 0; i < size; i++) {
			// // for (auto it = nodes[i].begin(); it != nodes[i].end(); it++) {
   // //      		if (*it == node) {
   // //      			reverse_neigh.push_back(i);
   // //      		}
   // //    		}
   //  		if (hasRoad(i, node)) {
   //  			reverse_neigh.push_back(i);
   //  		}
   //  	}
    	for (int i = 0; i < size; ++i) {
            if (nodes[i][node] == 1) {
                reverse_neigh.push_back(i);
            }
        }
    	return reverse_neigh;
    }

  	int BFS(Tvalue start, Tvalue dest) {
  		std::vector<Tvalue> visited(size, -1), distance(size, -1);
  		int level = 1;
        visited[start] = 1;
        if (start == dest) {
        	return 0;
        }
        distance[start] = 0;
        std::queue<Tvalue> queue;
        queue.push(start);
        while (!queue.empty()) {
            Tvalue node;
            node = queue.front();
            queue.pop();
            std::vector<Tvalue> n = getNeighbors(node);
            for (int i = 0; i < n.size(); i++) {
                if (visited[n[i]] == -1) {
                    visited[n[i]] = 1;
                    distance[n[i]] = distance[node] + 1;
                    queue.push(n[i]);
                }
            }
        }
        return distance[dest];
    }

    std::vector<Tvalue> BFS_distance(Tvalue start) {
    	std::vector<Tvalue> visited(size, 0), distance(size, -1);
    	int level = 1;
        visited[start] = 1;
        distance[start] = 0;
        std::queue<Tvalue> queue;
        queue.push(start);
        while (!queue.empty()) {
            Tvalue node;
            node = queue.front();
            queue.pop();
            std::vector<Tvalue> n = getNeighbors(node);
            for (int i = 0; i < n.size(); i++) {
                if (visited[n[i]] == 0) {
                    visited[n[i]] = 1;
                    distance[n[i]] = distance[node] + 1;
                    queue.push(n[i]);
                }
            }
        }
        return distance;
    }

    std::vector<Tvalue> BFS_reverse_distance(Tvalue start) {
    	std::vector<Tvalue> visited(size, 0), distance(size, -1);
    	int level = 1;
        visited[start] = 1;
        distance[start] = 0;
        std::queue<Tvalue> queue;
        queue.push(start);
        while (!queue.empty()) {
            Tvalue node;
            node = queue.front();
            queue.pop();
            std::vector<Tvalue> n = getReverseNeighbors(node);
            for (int i = 0; i < n.size(); i++) {
                if (visited[n[i]] == 0) {
                    visited[n[i]] = 1;
                    distance[n[i]] = distance[node] + 1;
                    queue.push(n[i]);
                }
            }
        }
        return distance;
    }
};

#endif  // ROAD_GRAPH_H_