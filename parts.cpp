// Project Identifier: 9B734EC0C043C5A836EA0EBE4BEFEA164490B2C7

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include <cmath>
#include <numeric>

// numeric_limits<double>::infinity()

// struct containing two integers
// same struct inlcudes the room
// we need a vector for this

// make a separate vector of structs of prim info (best distance, predecessor)
// always go from largest to smallest

// B & C
// need a vector of indices
// manipulate the order of the indeces into the vertex vector

// B
// add zero to the end like darden said

// C
// Start with part B
// Use MST in the promising function
// (Might  need extra branches to get estimates to the current partial sort? Or maybe we can just add the running total?



using namespace std;

struct Coords {
    int x;
    int y;
    char area;
};

struct Prim {
    double sq_distance = numeric_limits<double>::infinity();
    int prev = -1;
    bool k = false;
};

struct PartC {
    double sq_distance = numeric_limits<double>::infinity();
    // int prev = -1;
    bool k = false;
};

class Graphs {
    private:
    int num_vertices;
    vector<Coords> coords_vec;
    vector<Prim> prim_results;
    bool has_decon = false;
    bool has_lab = false;
    bool has_outer = false;
    vector<uint32_t> subtour;

    // Part C stuff
    vector<uint32_t> best_path;
    vector<uint32_t> curr_path;
    double best_dist = 0;
    double running_total = 0;
    vector<vector<double>> matrix;
    vector<PartC> partc_vec;
    vector<uint32_t> path;

    public:
    bool is_prim = false;
    bool is_KNN = false;

    void driver() {
        reading_input();
        if (is_prim) {
            running_prim();
            prim_output();
        }
        else if (is_KNN) {
            running_NInsert();
            // two_opt();
            N_output();
        }
        else {
            running_NInsert();
            // path.resize(coords_vec.size());
            best_path = path = subtour;
            double total = 0;

            // subtour = best_path;

            // get distance of fasttsp
            for (uint32_t i = 0; i < subtour.size() - 1; i++) {
                total += sqrt(calc_distance(coords_vec[subtour[i]], coords_vec[subtour[i + 1]]));
            }
            total += sqrt(calc_distance(coords_vec[subtour.front()], coords_vec[subtour.back()]));
            best_dist = total;

            partC_setup();
            // sets curr best to TSP

            genPerms(1);
            partC_output();

        }
    }

    void partC_setup() {
        path.resize(coords_vec.size());
        // iota(path.begin(), path.end(), 0);
        matrix.resize(coords_vec.size());
        for (uint32_t i = 0; i < coords_vec.size(); i++) {
            matrix[i].resize(coords_vec.size());
            for (uint32_t j = 0; j < coords_vec.size(); j++) {
                // if (i == j) {
                //     matrix[i][j] = 0;
                // // }
                // else {
                    matrix[i][j] = sqrt(calc_distance(coords_vec[i], coords_vec[j]));
                // }
            }

        }

    }

    void partC_output() {
        cout << fixed << setprecision(2);
        cout << best_dist << "\n";

        for (uint32_t p : best_path) {
            cout << p <<  " ";
        }

    }

    bool promising(uint32_t permLength) {
        prim_results.clear();
        prim_results.resize(coords_vec.size());
        double curr_len = 0;
        prim_results[permLength].sq_distance = 0;
        double temp_min1 = numeric_limits<double>::infinity();
        double temp_min2 = numeric_limits<double>::infinity();
        uint32_t idx1 = 0;
        uint32_t idx2 = permLength - 1;

        // need to do this to save time (IA Notes)
        if (path.size() - permLength < 5 ) {
            return true;
        }

        // Part A
        for (uint32_t j = permLength; j < path.size(); j++) {
            int use = -1;
            double minx = numeric_limits<double>::infinity();
            for (uint32_t k = permLength; k < path.size(); k++) {
                if (!prim_results[k].k && prim_results[k].sq_distance < minx) {
                    minx = prim_results[k].sq_distance;
                    use = static_cast<int>(k);
                }
            }
            // if (use == - 1) break;
            prim_results[static_cast<uint32_t>(use)].k = true;
            curr_len += prim_results[static_cast<uint32_t>(use)].sq_distance;

            // pruning
            // if (curr_len > best_dist) {
            //     return false;
            // }

            for (uint32_t i = permLength; i < path.size(); i++) {
                if (prim_results[i].k == false) {        
                    double temp = matrix[path[static_cast<uint32_t>(use)]][path[i]]; 
                    // calc_distance(coords_vec[static_cast<uint32_t>(use)], coords_vec[i]);
                    if (temp < prim_results[i].sq_distance) {
                        prim_results[i].sq_distance = temp;
                        // prim_results[i].prev = static_cast<int>(use);
                    }
                }
            }
        }
        // Part A code ends here 

        // get min endpoints estimate

        for (uint32_t i = permLength; i < path.size(); i++) {
            if (temp_min1 >= matrix[idx1][path[i]]) {
                temp_min1 = matrix[idx1][path[i]];
            }
            if (temp_min2 >= matrix[path[idx2]][path[i]]) {
                temp_min2 = matrix[path[idx2]][path[i]];
            }
        }

        // for (uint32_t i = permLength; i < path.size(); i++) {
        //     if (temp_min2 >= matrix[path[idx2]][path[i]]) {
        //         temp_min2 = matrix[path[idx2]][path[i]];
        //     }
        // }

        // cerr << fixed << showpoint << setprecision(2);
        // bool p;
        // if ((temp_min1 + curr_len + running_total + temp_min2) >= best_dist) {
        //     p = false;
        // }
        // else {
        //     p = true;
        // }

//         for (size_t i = 0; i < path.size(); ++i)
//         cerr << setw(2) << path[i] << ' ';
// cerr << setw(4) << permLength << setw(10) << running_total;
// cerr << setw(10) << temp_min1 << setw(10) << temp_min2;
// cerr << setw(10) << curr_len << setw(10) << temp_min1 + curr_len + running_total + temp_min2 << "  " << p << '\n';

        if ((temp_min1 + curr_len + running_total + temp_min2) >= best_dist) {
            return false;
        }

        return true;
    }


    void genPerms(uint32_t permLength) { 
        // fix matrix
        if (permLength == path.size()) {
        // Do something with the path
            // IA said we cant update running total here since we hit this 
            // point many times
            double temp = running_total + matrix[0][path.back()];
            if (temp < best_dist) {
                best_dist = temp;
                best_path = path;
            }
            return;
        }  // if ..complete path

        if (!promising(permLength)) {
            return;
        }  // if ..not promising



        for (uint32_t i = permLength; i < path.size(); ++i) {
            swap(path[permLength], path[i]);

                                        // new node       // prev node?
            running_total += matrix[path[permLength]][path[permLength - 1]]; // NOT SURE

            genPerms(permLength + 1);

            running_total -= matrix[path[permLength]][path[permLength - 1]]; // NOT SURE
            // think we need to get consecutive vals so this should work for length

            swap(path[permLength], path[i]);
        }  // for ..unpermuted elements
    }  // genPerms()


    void N_output() {
        cout << fixed << setprecision(2);
        double total = 0;
        for (uint32_t i = 0; i < subtour.size() - 1; i++) {
            total += sqrt(calc_distance(coords_vec[subtour[i]], coords_vec[subtour[i + 1]]));
        }
        total += sqrt(calc_distance(coords_vec[subtour.front()], coords_vec[subtour.back()]));
        
        cout << total << "\n";
        for (auto s : subtour) {
            cout << s << " ";
        }
    }

    void running_NInsert() {
        // pushing city at index zero into subtour
        subtour.push_back(0);
      
        // adding the first nearest neighbour into the subtour 
        uint32_t first = static_cast<uint32_t>(first_nearest_neighbour());
        subtour.push_back(first);

        // finding nn
        // if condition to check for -1 and static cast
        int n = nearest_neighbour(first);
        subtour.push_back(static_cast<uint32_t>(n));
        subtour.push_back(0);
        first = static_cast<uint32_t>(nearest_neighbour(first));
        n = nearest_neighbour(first);
        while (n != -1) {
            // uint32_t nn = static_cast<uint32_t>(n);
            // prim_results[static_cast<uint32_t>(nn)].k = true;
            uint32_t insert_idx = calc_nn_dist(static_cast<uint32_t>(n));
            subtour.insert(subtour.begin() + insert_idx, static_cast<uint32_t>(n));
      
            // restart 
            n = nearest_neighbour(static_cast<uint32_t>(n));
        }
      
        subtour.pop_back();
        // uint32_t nn = nearest_neighbour();
        // uint32_t insert_idx = calc_nn_dist(nn);
        // subtour.insert(subtour.begin()+ insert_idx, nn);

        
    } 

    uint32_t calc_nn_dist(uint32_t nn) {
        double min_dist = numeric_limits<double>::infinity();
        // int room1 = -1;
        int room2 = -1; 
        for (uint32_t i = 0; i < subtour.size() - 1; i++) {
            double temp = sqrt(calc_distance(coords_vec[subtour[i]], coords_vec[nn])) + 
                          sqrt(calc_distance(coords_vec[subtour[(i + 1)]], coords_vec[nn])) -
                          sqrt(calc_distance(coords_vec[subtour[i]], coords_vec[subtour[(i + 1)]]));
            if (temp < min_dist) {
                min_dist = temp;
                // room1 = i;
                room2 = static_cast<int>((i + 1));
            }
        }
        return static_cast<uint32_t>(room2);
    }

    int nearest_neighbour(uint32_t next) {
        // prim_results.clear();
        // prim_results.resize(coords_vec.size()); 
        // prim_results[next].sq_distance = 0;
        prim_results[next].k = true; 
        double min_dist = numeric_limits<double>::infinity();
        int minx = -1;
        for (uint32_t i = 0; i < prim_results.size(); i++) {
            if (prim_results[i].k == false) {
                double temp = calc_distance(coords_vec[next], coords_vec[i]);
                if (temp < prim_results[i].sq_distance) {
                    prim_results[i].sq_distance = temp;
                    // prim_results[i].prev = static_cast<int>(next);
                    // if (temp < min_dist) {
                    //     min_dist = temp;
                    //     minx = static_cast<int>(i);
                    // }
                }
                if (prim_results[i].sq_distance < min_dist) {
                    min_dist = prim_results[i].sq_distance;
                    // minx = (prim_results[i].prev);
                    if (minx == -1) {
                        minx = static_cast<int>(i);
                    }
                }
                // if (minx != -1 && temp < prim_results[static_cast<uint32_t>(minx)].sq_distance) {
                //     minx = static_cast<int>(i);
                // }
            }
        }
        return minx;
    }

    int first_nearest_neighbour() {
        // only for first city
        prim_results.resize(coords_vec.size()); 
        prim_results[0].sq_distance = 0;
        prim_results[0].k = true;
        double min_dist = numeric_limits<double>::infinity();
        int minx = -1;
        for (uint32_t i = 0; i < prim_results.size(); i++) {
            if (prim_results[i].k == false) {
                double temp = calc_distance(coords_vec[0], coords_vec[i]);
                prim_results[i].sq_distance = temp;
                // prim_results[i].prev = 0;
                if (temp < min_dist) {
                    min_dist = temp;
                    minx = static_cast<int>(i);
                    // if (minx == -1) {
                    //     minx = static_cast<int>(i);
                    // }
                }
                // if (minx != -1 && temp < prim_results[static_cast<uint32_t>(minx)].sq_distance) {
                //     minx = static_cast<int>(i);
                // }
            }
        }
        prim_results[static_cast<uint32_t>(minx)].k = true; // maybe comment this out?
        return minx;
    }

    void prim_output() {
        // setprecision(2);
        cout << fixed << setprecision(2);
        double sum = 0;
        for (Prim& p : prim_results) {
            if (p.prev != -1) {
            sum += sqrt(p.sq_distance); }
        }
        cout << sum << "\n";
        uint32_t i = 0;
        for (Prim& p : prim_results) {
            if (p.prev != -1) {
            if (p.prev < static_cast<int>(i)) {
                cout << p.prev << " " << i << "\n";
            }
            else {
                cout << i << " " << p.prev << "\n";
            }
            }
            i++;
        }
    }
    
    void running_prim() {
        prim_results.resize(coords_vec.size()); 
        prim_results[0].sq_distance = 0;
        for (uint32_t j = 0; j < coords_vec.size(); j++) {
            int use = -1;
            double minx = numeric_limits<double>::infinity();
            for (uint32_t k = 0; k < coords_vec.size(); k++) {
                if (!prim_results[k].k && prim_results[k].sq_distance < minx) {
                    minx = prim_results[k].sq_distance;
                    use = static_cast<int>(k);
                }
            }
            if (use == - 1) break;
            prim_results[static_cast<uint32_t>(use)].k = true;

            for (uint32_t i = 0; i < prim_results.size(); i++) {
                if (prim_results[i].k == false) {
                    if (!(coords_vec[static_cast<uint32_t>(use)].area == 'L' && coords_vec[i].area == 'O') &&
                        !(coords_vec[static_cast<uint32_t>(use)].area == 'O' && coords_vec[i].area == 'L')) {
                                
                        double temp = calc_distance(coords_vec[static_cast<uint32_t>(use)], coords_vec[i]);
                        
                            if (temp < prim_results[i].sq_distance) {
                                prim_results[i].sq_distance = temp;
                                prim_results[i].prev = static_cast<int>(use);
                            }
                        }
                    }
                }
        }

    }

    double calc_distance(Coords& c1, Coords& c2) {
        double dist = (static_cast<double>(c1.x - c2.x) * static_cast<double>(c1.x - c2.x)) 
                    + (static_cast<double>(c1.y - c2.y) * static_cast<double>(c1.y - c2.y));
        return dist;
    }

    void reading_input() {
        cin >> num_vertices >> ws;
        int coord;
        while (cin >> coord) {
            Coords coo;
            coo.x = coord;
            cin >> ws >> coord;
            coo.y = coord;

            room_check(coo);
            coords_vec.push_back(coo);
        }

        if (is_prim && has_outer && has_lab && !has_decon) {
            cerr << "Cannot construct MST\n";
            exit(1);
        }
    }

    void room_check(Coords& coo) {
        if (coo.x < 0 && coo.y < 0) {
            coo.area = 'L';
            has_lab = true;
            return;
        }
        else if ((coo.x == 0 && coo.y <= 0) || (coo.y == 0 && coo.x <= 0)) { 
            coo.area = 'D';
            has_decon = true;
            return;
        }
        else {
            coo.area = 'O';
            has_outer = true;
            return;
        }
    }


};

// running_total += matrix[0][path[path.size() - 1]];



