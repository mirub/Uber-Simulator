// Copyright 2019 SD_Homework_Team

#ifndef SOLVER_H_
#define SOLVER_H_
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <queue>
#include "./road_graph.h"
#include "./road_table.h"
#include "./driver.h"

struct indexDistance {
	int dist;
	int index;

	indexDistance& operator=(const indexDistance& d) {
		if (this != &d) {
			this->dist = d.dist;
			this->index = d.index;
		}
		return *this;	
	}
};

class solver {
	private:
		int n, m;
		RoadTable<std::string, int> crossroads;
		RoadGraph<int> streets;
		driver_vector<driver> uber;
		std::vector<std::string> indexToName;
	public:
		void task1_solver(std::ifstream& fin, std::ofstream& fout) {
			fin>>n>>m;
			crossroads.put_capacity(n);
			streets.put_nodes(n);
			std::string croad;
			for (int i = 0; i < n; ++i) {
				fin>>croad;
				this->crossroads.put(croad, i);
				indexToName.push_back(croad);
			}
			std::string c1, c2;
			for (int i = 0; i < m; ++i) {
				fin>>c1>>c2;
				this->streets.addRoad(crossroads.get(c1), crossroads.get(c2));
			}
			int q1;
			fin>>q1;
			for (int i = 0; i < q1; ++i) {
				fin>>c1>>c2;
				if (streets.BFS(crossroads.get(c1), crossroads.get(c2)) != -1) {
					fout<<"y\n";
				} else {
					fout<<"n\n";
				}
			}
		}

		void task2_solver(std::ifstream& fin, std::ofstream& fout) {
			int q2;
			fin>>q2;
			std::string c1, c2;
			for (int i = 0; i < q2; ++i) {
				fin>>c1>>c2;
				// if (streets.BFS(crossroads.get(c1), crossroads.get(c2)) != -1) {
				// 	fout<<streets.BFS(crossroads.get(c1), crossroads.get(c2))<<"\n";
				// } else {
				// 	fout<<"-1\n";
				// }
				std::vector<int> distance = streets.BFS_distance(crossroads.get(c1));
				fout<<distance[crossroads.get(c2)]<<"\n";
			}
		}

		void task3_solver(std::ifstream& fin, std::ofstream& fout) {
			int q3, n;
			fin>>q3;
			std::string line, c1, c2, c3, c4;
			getline(fin, line);
			for (int i = 0; i < q3; ++i) {
				fin>>c1>>c2>>c3>>n;
				if (c1 == "q" && n == 2) {
					fin>>c4;
				}
				if (c1 == "c") {
					if (n == 0) {
						if (!this->streets.hasRoad(crossroads.get(c2), crossroads.get(c3))) {
							this->streets.addRoad(crossroads.get(c2), crossroads.get(c3));
						}	
					}	
					if (n == 1) {
						//if (this->streets.hasRoad(crossroads.get(c2), crossroads.get(c3))) {
							this->streets.removeRoad(crossroads.get(c2), crossroads.get(c3));
						//}
						//if (this->streets.hasRoad(crossroads.get(c3), crossroads.get(c2))) {
							this->streets.removeRoad(crossroads.get(c3), crossroads.get(c2));
						//}
					}	
					if (n == 2) {
						if (!this->streets.hasRoad(crossroads.get(c2), crossroads.get(c3))) {
							this->streets.addRoad(crossroads.get(c2), crossroads.get(c3));
						}
						if (!this->streets.hasRoad(crossroads.get(c3), crossroads.get(c2))) {
							this->streets.addRoad(crossroads.get(c3), crossroads.get(c2));
					    }
					}	
					if (n == 3) {
						//int modify = 0;
						if (this->streets.hasRoad(crossroads.get(c2), crossroads.get(c3)) &&
							!this->streets.hasRoad(crossroads.get(c3), crossroads.get(c2))) {
							this->streets.removeRoad(crossroads.get(c2), crossroads.get(c3));
							// if (!this->streets.hasRoad(crossroads.get(c3), crossroads.get(c2))) {
							this->streets.addRoad(crossroads.get(c3), crossroads.get(c2));
						 //    }
						 //    modify = 1;
						} else if (!this->streets.hasRoad(crossroads.get(c2), crossroads.get(c3)) &&
							this->streets.hasRoad(crossroads.get(c3), crossroads.get(c2))) {
						//if (this->streets.hasRoad(crossroads.get(c3), crossroads.get(c2)) && !modify) {
							this->streets.addRoad(crossroads.get(c2), crossroads.get(c3));
						 	this->streets.removeRoad(crossroads.get(c3), crossroads.get(c2));
						// 	if (!this->streets.hasRoad(crossroads.get(c2), crossroads.get(c3))) {
						// 		this->streets.addRoad(crossroads.get(c2), crossroads.get(c3));
						// 	}
						// }
						 }
					}
				}
				if (c1 == "q") {
					if (n == 0) {
						if (streets.BFS(crossroads.get(c2), crossroads.get(c3)) != -1) {
							fout<<"y\n";
						} else {
							fout<<"n\n";
						}
					}
					if (n == 1) {
							fout<<streets.BFS(crossroads.get(c2), crossroads.get(c3))<<"\n";
					}
					if (n == 2) {
						int a = 0, b = 0;
						a = streets.BFS(crossroads.get(c2), crossroads.get(c4));
						b = streets.BFS(crossroads.get(c4), crossroads.get(c3));
						if (a == -1 || b == -1) {
							fout<<"-1\n";
						} else {
							fout<<(a+b)<<'\n';
						}
					}
				}
			}
		}

		int hasDriver(int index) {
			for (auto i = uber.d_vector.begin(); i != uber.d_vector.end(); ++i) {
				if (i->location == indexToName[index] && i->status == 1) {
					return 1;
				}
			}
			return 0;
		}

		std::vector<int> getClosestDriverPositions(std::string start) {
			std::vector<int> distance = streets.BFS_reverse_distance(crossroads.get(start));
			std::vector<int> positions;
			int min_distance = n + 1;
			for (int i = 0; i < distance.size(); ++i) {
				if (distance[i] != -1 && distance[i] < min_distance && hasDriver(i)) {
					min_distance = distance[i];
				}
			}
			for (int i = 0; i < distance.size(); ++i) {
				if (distance[i] != -1 && distance[i] == min_distance
					&& hasDriver(i) && distance[i] != n+1) {
					positions.push_back(i);
				}
			}
	        return positions;
    	}

    	int getDistanceFromStart(std::string start) {
    		std::vector<int> distance = streets.BFS_reverse_distance(crossroads.get(start));
			std::vector<int> positions;
			int min_distance = n + 1;
			for (int i = 0; i < distance.size(); ++i) {
				if (distance[i] != -1 && distance[i] < min_distance && hasDriver(i)) {
					min_distance = distance[i];
				}
			}
			for (int i = 0; i < distance.size(); ++i) {
				if (distance[i] != -1 && distance[i] == min_distance
					&& hasDriver(i)) {
					positions.push_back(i);
				}
			}
	        return min_distance;
    	}

    	std::string getClosestDriver(std::string start) {
    		std::vector<int> pos = getClosestDriverPositions(start);
    		if (!pos.size()) {
    			return "no";
    		}
    		int max_rating = -1;
    		std::string name = "no";
    		for (int i = 0; i < pos.size(); i++) {
    			for (auto it = uber.d_vector.begin(); it != uber.d_vector.end(); ++it) {
	    			if (crossroads.get(it->location) == pos[i]) {
	    				if (it->rating > max_rating && it->status == 1) {
	    					max_rating = it->rating;
	    					name = it->name;
	    				} else {
	    					if (it->rating == max_rating && it->name < name && it->status == 1) {
	    						name = it->name;
	    					}
	    				}
	    			}
	    		}
	    		
    		}
    		if (max_rating == -1) {
    			return "no";
    		}
    		return name;
    	}

    	int getDestination(std::string start, std::string destination, std::ofstream& fout) {
    		std::vector<int> distance = streets.BFS_distance(crossroads.get(start));
    		if (start == destination) {
    			return crossroads.get(destination);
    		}
    		if (distance[crossroads.get(destination)] != -1) {
    			//fout<<"\n Distanta "<<start<<" "<<destination<<" este :"<<distance[crossroads.get(destination)]<<"\n";
    			return crossroads.get(destination);
    		}
    		std::vector<int> isNeighbor(n, 0);
    		std::vector<int> neigh = streets.getNeighbors(crossroads.get(destination));
    		//fout<<"\n Vecinii "<< destination<< " sunt: "<<start<<" ";
    		 for (int i = 0; i < neigh.size(); ++i) {
    		 	isNeighbor[neigh[i]] = 1;
    			//fout<<neigh[i]<<" ";
    		}
    		//fout<<"\n";
    		//std::vector<int> distance = streets.BFS_distance(crossroads.get(start));
    		int min_distance = n + 1;
    		int dest = -1;
    		for (int i = 0; i < n; ++i) {
    			if (distance[i] < min_distance && isNeighbor[i] && distance[i] != -1) {
    				min_distance = distance[i];
    				dest = i;
    			}
    		}
    		// fout<<min_distance<<" ";
    		return dest;
    	}

    	int getDestinationDistance(std::string start, std::string destination) {
    		int k = streets.BFS(crossroads.get(start), crossroads.get(destination));
    		if (k != -1) {
    			return k;
    		}
    		std::vector<int> isNeighbor(n, 0);
    		std::vector<int> neigh = streets.getNeighbors(crossroads.get(destination));
    		for (int i = 0; i < neigh.size(); ++i) {
    			isNeighbor[neigh[i]] = 1;
    		}
    		std::vector<int> distance = streets.BFS_distance(crossroads.get(start));
    		int min_distance = n + 1;
    		int dest = -1;
    		for (int i = 0; i < n; ++i) {
    			if (distance[i] < min_distance && isNeighbor[i] && distance[i] != -1) {
    				min_distance = distance[i];
    				dest = i;
    			}
    		}
    		if (min_distance == n + 1) {
    			return -1;
    		}
    		return min_distance;
    	}

		void task4_solver(std::ifstream& fin, std::ofstream& fout) {
			int q4, nr, k = 0;
			float rating;
			fin>>q4;
			std::string line, start, name, destination, c1;
			getline(fin, line);
			//streets.print_streets(fout);
			for (int i = 0; i < q4; ++i) {
				fin>>c1;
				if (c1 == "d") {
					fin>>name>>destination;
					int status = 1;
					this->uber.addDriver(name);
					this->uber.changeStatus(name, status);
					this->uber.changeLocation(name, destination);
				}
				if (c1 == "b") {
					fin>>name;
					int status = 0;
					this->uber.addDriver(name);
					this->uber.changeStatus(name, status);
				}
				if (c1 == "r") {
					fin>>start>>destination>>rating;
					k++;
					//fout<<driver<<"\n";
					std::string driver = getClosestDriver(start);
					//std::string driver = "no";
					if (driver == "no") {
						fout<<"Soferi indisponibili\n";
					} else {
						int d = getDestination(start, destination, fout);
						if (d == -1) {
							fout<<"Destinatie inaccesibila\n";
						} else {
							int d1, d2;
							d1 = getDistanceFromStart(start);
							d2 = getDestinationDistance(start, indexToName[d]);
							//fout<<"\n"<<d1<<" "<<d2<<" "<<driver<<"\n";
							uber.changeDistance(driver, (d1 + d2));
							uber.changeLocation(driver, indexToName[d]);
							// fout<<"\n"<<uber.getLocation(driver)<<"\n";
							// fout<<"\n";
							// for (int i = 0; i < uber.d_vector.size(); i++) {
							// 	fout<<uber.d_vector[i].name<<" "<<uber.d_vector[i].total_rating<<"\n";
							// }
							// fout<<"\n";
							uber.changeRating(driver, rating);
							//break;
						}
					}		
				}
				if (c1 == "top_rating") {
					fin>>nr;
					fout<<std::setprecision(3);
					fout<<std::fixed;
					uber.printRating(nr, fout);
				}
				if (c1 == "top_dist") {
					fin>>nr;
					uber.printDistance(nr, fout);
				}
				if (c1 == "top_rides") {
					fin>>nr;
					uber.printRides(nr, fout);
				}
				if (c1 == "info") {
					fin>>name;
					//this->uber.addDriver(name);
					fout<<std::setprecision(3);
					fout<<std::fixed;
					this->uber.printDriver(name, fout);
				}
			}	
			// fout<<k;
		}

		void task5_solver(std::ifstream& fin, std::ofstream& fout) {
			std::string name, dest;
			int fuel,nr;
			fin>>fuel>>name>>nr;
			//std::cout<<fuel<<"\n";
			std::vector<int> toVisit(n, 0);
			for (int i = 0; i < nr; ++i) {
				fin>>dest;
				toVisit[crossroads.get(dest)] = 1;
			}
			std::vector<int> distance = streets.BFS_distance(crossroads.get(uber.getLocation(name)));
			int d = distance.size();
			std::vector<int> index(d, 0);
			for (int i = 0; i < index.size(); ++i) {
				index[i] = i;
			}
			for (int i = 0; i < distance.size() - 1; ++i) {
				for (int j = i + 1; j < distance.size(); ++j) {
					if (distance[i] > distance[j]) {
						int aux1 = distance[i];
						int aux2 = index[i];
						distance[i] = distance[j];
						index[i] = index[j];
						distance[j] = aux1;
						index[j] = aux2;
					} else {
						if (distance[i] == distance[j]) {
							if (indexToName[index[i]] > indexToName[index[j]]) {
								int aux2 = index[i];
								index[i] = index[j];
								index[j] = aux2;
							}
						}
					}
				}
			}

			for (int i = 0; i < distance.size(); ++i) {
				if (distance[i] != -1 && distance[i] <= fuel && toVisit[index[i]]) {
					fout<<indexToName[index[i]]<<" ";
				}
			}

		}	
};		
#endif  // SOLVER_H_
