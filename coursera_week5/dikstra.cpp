//
//  main.cpp
//  coursera_week5
//
//  Created by 安田洋介 on 11/14/15.
//  Copyright © 2015 安田洋介. All rights reserved.
//

# include "dikstra.h"

using namespace std;

vector<int> dikstra(set<int> node_set, vector<vector<pair<int, int> > > edges){
    vector<int> distances (node_set.size(), 1000000);
    distances[0] = 0;
    queue<int> node_queue;
    node_queue.push(*node_set.begin());
    node_set.erase(node_set.begin());
    while(!node_set.empty()){
        queue<int> new_queue;
        while(!node_queue.empty()){
            int from_node = node_queue.front();
            node_queue.pop();
            int current_distance = distances[from_node];
            for(int i=0; i<edges[from_node].size(); i++){
                pair<int, int> next_edge = edges[from_node][i];
                set<int>::iterator it = node_set.find(next_edge.first);
                if(it == node_set.end()){
                    continue;
                }else{
                    new_queue.push(next_edge.first);
                }
                if(distances[next_edge.first] > current_distance+next_edge.second){
                    distances[next_edge.first] = current_distance+next_edge.second;
                }
            }
            int min_distance = 1000000;
            int min_distance_node = edges.size();
            for(int i =0; i<distances.size(); i++){
                set<int>::iterator it = node_set.find(i);
                if(it != node_set.end() && distances[i] < min_distance){
                    min_distance=distances[i];
                    min_distance_node=i;
                }
            }
            node_set.erase(node_set.find(min_distance_node));
        }
        node_queue = new_queue;
    }
    return distances;
}

vector<int> exec_dikstra(string file_name){
    ifstream inFile(file_name);
    string line;
    int node_count = 0;;
    while (getline(inFile, line)){
        cout << line << endl;
        istringstream iss(line);
        int from;
        iss >> from;
        if(node_count < from){
            node_count = from;
        }
        string edge_data;
        while(iss >> edge_data){
            cout << edge_data << endl;
            stringstream lineStream(edge_data);
            string to_string;
            getline(lineStream, to_string, ',');
            int node = stoi(to_string);
            if(node_count < node){
                node_count = node;
            }
        }
    }
    inFile.close();
    
    vector<vector<pair<int, int> > > edges (node_count);

    ifstream secFile(file_name);
    while (getline(secFile, line)){
        cout << line << endl;
        istringstream iss(line);
        int from;
        iss >> from;
        string edge_data;
        while(iss >> edge_data){
            cout << edge_data << endl;
            stringstream lineStream(edge_data);
            string to_string;
            string distance_string;
            pair<int, int> to_pair;
            getline(lineStream, to_string, ',');
            to_pair.first = stoi(to_string) - 1;
            getline(lineStream, distance_string);
            to_pair.second = stoi(distance_string);
            edges[from - 1].push_back(to_pair);
        }
    }
    
    set<int> node_set;
    for(int i=0; i<node_count; i++){
        node_set.insert(i);
    }
    vector<int> distances = dikstra(node_set, edges);
    return distances;
}
