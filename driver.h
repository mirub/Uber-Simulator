#ifndef DRIVER_H_
#define DRIVER_H_

class driver {
public:
	std::string name, location;
	int prev_online, status, distance, rides, total_rating;
	float rating;

	driver(std::string name, std::string location, int prev_online, int status,
		int distance, int rides, int total_rating, float rating) {
		this->name = name;
		this->location = location;
		this->prev_online = prev_online;
		this->status = status;
		this->distance = distance;
		this->rides = rides;
		this->rating = rating;
		this->total_rating = total_rating;
	}

	driver() {
		this->prev_online = 0;
		this->status = 1;
		this->distance = 0;
		this->rides = 0;
		this->rating = 0;
		this->total_rating = 0;
	}

	driver(std::string name) {
		this->name = name;
		this->prev_online = 0;
		this->status = 1;
		this->distance = 0;
		this->rides = 0;
		this->rating = 0;
		this->total_rating = 0;
	}

	void changeStatus(int status) {
		this->status = status;
	}

	void changeLocation(std::string location) {
		this->location = location;
	}

	void changeRating(int rating) {
		this->rides = this->rides+1;
		this->total_rating += rating;
		this->rating = (float)this->total_rating/rides;
	}

	int getTotalRating() {
		return this->total_rating;
	}

	void changeDistance(int d) {
		this->distance = this->distance + d;
	}

	bool operator==(const driver& d){
		if (this->name == d.name && this->location == d.location && this->prev_online
	      		== d.prev_online && this->status == d.status && this->distance ==
	      		d.distance && this->rides == d.rides && this->rating == d.rating &&
	      		this->total_rating == d.total_rating) {
			return true;
		}
		return false;
	}

	driver& operator=(const driver& d) {
		if (this != &d) {
			this->name = d.name;
			this->location = d.location;
			this->prev_online = d.prev_online;
			this->status = d.status;
			this->distance = d.distance;
			this->rides = d.rides;
			this->rating = d.rating;
			this->total_rating = d.total_rating;
		}
		return *this;	
	}	
};


template <typename T>
class driver_vector {
	public:
		std::vector<T> d_vector;
		int size;
		int capacity;

		driver_vector () {
			this->capacity = 0;
			this->size = 0;
		}

		driver_vector (std::vector<T> v, int capacity, int size) {
			this->d_vector = v;
			this->capacity = capacity;
			this->size = size;
		}

		bool isDriver(driver d) {
			auto it = this->d_vector.begin();
	    	for (it = this->d_vector.begin(); it != this->d_vector.end(); ++it) {
	      		if (*it == d) {
	      			// the element exists 
	        		return true;
	      		}
	    	}
	    	return false;
		}

		void addDriver(std::string name) {
			int found = 0;
			auto it = this->d_vector.begin();
	    	for (it = this->d_vector.begin(); it != this->d_vector.end(); ++it) {
	      		if (it->name == name) {
	        		found = 1;
	      		}
	    	}
	    	if (found == 0) {
	      		driver aux(name);
				d_vector.push_back(aux);
	    	}
		}

		void changeStatus(std::string name, int status) {
			auto it = this->d_vector.begin();
			for (it = this->d_vector.begin(); it != this->d_vector.end(); ++it) {
	      		if (it->name == name) {
	      			it->changeStatus(status);
	      		}
	    	}
		}

		void changeLocation(std::string name, std::string location) {
			auto it = this->d_vector.begin();
			for (it = this->d_vector.begin(); it != this->d_vector.end(); ++it) {
	      		if (it->name == name) {
	      			// the element exists 
	      			//std::cout<<it->name<<" "<<it->location<<"\n";
	      			it->changeLocation(location);
	      			//std::cout<<it->location<<"\n\n";
	      		}
	    	}
		}

		int getStatus(std::string name) {
			auto it = this->d_vector.begin();
			for (it = this->d_vector.begin(); it != this->d_vector.end(); ++it) {
	      		if (it->name == name) {
	      			// the element exists 
	        		return it->status;
	      		}
	    	}
		}

		std::string getLocation(std::string name) {
			auto it = this->d_vector.begin();
			for (it = this->d_vector.begin(); it != this->d_vector.end(); ++it) {
	      		if (it->name == name) {
	      			// the element exists 
	        		return it->location;
	      		}
	    	}
		}

		void changeRating(std::string name, int rating) {
			auto it = this->d_vector.begin();
			for (it = this->d_vector.begin(); it != this->d_vector.end(); ++it) {
	      		if (it->name == name) {
	      			//std::cout<<it->name<<" "<<rating<<" "<<it->total_rating<<"\n";
	        		it->changeRating(rating);
	        		//std::cout<<it->name<<" "<<rating<<" "<<it->total_rating<<"\n\n";
	      		}
	    	}
		}

		float getRating(std::string name) {
			auto it = this->d_vector.begin();
			for (it = this->d_vector.begin(); it != this->d_vector.end(); ++it) {
	      		if (it->name == name) {
	      			// the element exists 
	        		return it->total_rating;
	      		}
	    	}
		}

		void sortByRating() {
			if (d_vector.size() != 0) {
				for (int i = 0; i < d_vector.size() - 1; ++i) {
					bool wasSwapped = false;
					for (int j = 0; j < d_vector.size() - i - 1; ++j) {
						if (d_vector[j].rating < d_vector[j + 1].rating) {
							driver aux = d_vector[j];
							d_vector[j] = d_vector[j + 1];
							d_vector[j + 1] = aux;
							wasSwapped = true;
						} else {
							if (d_vector[j].rating == d_vector[j + 1].rating) {
								if (d_vector[j].name > d_vector[j + 1].name) {
									driver aux = d_vector[j];
									d_vector[j] = d_vector[j + 1];
									d_vector[j + 1] = aux;
									wasSwapped = true;
								}
							}
						}
					}
					if (wasSwapped == false) {
						break;
					}
				} 
			}
		}

		void printRating(int nr, std::ofstream& fout) {
			this->sortByRating();
			if (nr < d_vector.size()) {
				for (int i = 0; i < nr; ++i) {
					fout<<d_vector[i].name<<":"<<d_vector[i].rating<<" ";
				}
				fout<<"\n";
			} else {
				if (nr >= d_vector.size()) {
					auto it = d_vector.begin();
					for (auto it = d_vector.begin(); it < d_vector.end(); ++it) {
						fout<<it->name<<":"<<it->rating<<" ";
					}
					fout<<"\n";
				}
			}
		}

		void sortByDistance() {
			if (d_vector.size() != 0) {
					for (int i = 0; i < d_vector.size() - 1; ++i) {
					bool wasSwapped = false;
					for (int j = 0; j < d_vector.size() - i - 1; ++j) {
						if (d_vector[j].distance < d_vector[j + 1].distance) {
							driver aux = d_vector[j];
							d_vector[j] = d_vector[j + 1];
							d_vector[j + 1] = aux;
							wasSwapped = true;
						} else {
							if (d_vector[j].distance == d_vector[j + 1].distance) {
								if (d_vector[j].name > d_vector[j + 1].name) {
									driver aux = d_vector[j];
									d_vector[j] = d_vector[j + 1];
									d_vector[j + 1] = aux;
									wasSwapped = true;
								}
							}
						}
					}
					if (wasSwapped == false) {
						break;
					}
				} 
			}
		}

		void printDistance(int nr, std::ofstream& fout) {
			this->sortByDistance();
			if (nr < d_vector.size()) {
				for (int i = 0; i < nr; ++i) {
					fout<<d_vector[i].name<<":"<<d_vector[i].distance<<" ";
				}
				fout<<"\n";
			} else {
				if (nr >= d_vector.size()) {
					auto it = d_vector.begin();
					for (auto it = d_vector.begin(); it < d_vector.end(); ++it) {
						fout<<it->name<<":"<<it->distance<<" ";
					}
					fout<<"\n";
				}
			}
		}

		void sortByRides() {
			if (d_vector.size() != 0) {
				for (int i = 0; i < d_vector.size() - 1; ++i) {
					bool wasSwapped = false;
					for (int j = 0; j < d_vector.size() - i - 1; ++j) {
						if (d_vector[j].rides < d_vector[j + 1].rides) {
							driver aux = d_vector[j];
							d_vector[j] = d_vector[j + 1];
							d_vector[j + 1] = aux;
							wasSwapped = true;
						} else {
							if (d_vector[j].rides == d_vector[j + 1].rides) {
								if (d_vector[j].name > d_vector[j + 1].name) {
									driver aux = d_vector[j];
									d_vector[j] = d_vector[j + 1];
									d_vector[j + 1] = aux;
									wasSwapped = true;
								}
							}
						}
					}
					if (wasSwapped == false) {
						break;
					}
				} 
			}
		}

		void printRides(int nr, std::ofstream& fout) {
			this->sortByRides();
			if (nr < d_vector.size()) {
				for (int i = 0; i < nr; ++i) {
					fout<<d_vector[i].name<<":"<<d_vector[i].rides<<" ";
				}
				fout<<"\n";
			} else {
				if (nr >= d_vector.size()) {
					auto it = d_vector.begin();
					for (auto it = d_vector.begin(); it < d_vector.end(); ++it) {
						fout<<it->name<<":"<<it->rides<<" ";
					}
					fout<<"\n";
				}
			}
		}

		void changeDistance(std::string name, int d) {
			auto it = this->d_vector.begin();
			for (it = this->d_vector.begin(); it != this->d_vector.end(); ++it) {
	      		if (it->name == name) {
	      			// the element exists 
	        		it->changeDistance(d);
	      		}
	    	}
		}

		int getDistance(std::string name) {
			auto it = this->d_vector.begin();
			for (it = this->d_vector.begin(); it != this->d_vector.end(); ++it) {
	      		if (it->name == name) {
	      			// the element exists 
	        		return it->distance;
	      		}
	    	}
		}

		void printDriver(std::string name, std::ofstream& fout) {
			auto it = this->d_vector.begin();
			for (it = this->d_vector.begin(); it != this->d_vector.end(); ++it) {
	      		if (it->name == name) {
	      			fout<<it->name<<": "<<it->location<<" "<<it->rating<<" "<<
	      			it->rides<<" "<<it->distance<<" ";
	      			if (it->status) {
	      				fout<<"online\n";
	      			} else {
	      				fout<<"offline\n";
	      			}
	      		}
	    	}
		}

		std::vector<driver> getVector() {
			std::vector<driver> v;
			for (auto it = d_vector.begin(); it != d_vector.end(); it++) {
        		v.push_back(*it);
	        }
	        return v;
		}
};
#endif  // DRIVER_H_