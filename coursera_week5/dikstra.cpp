//
//  main.cpp
//  coursera_week5
//
//  Created by 安田洋介 on 11/14/15.
//  Copyright © 2015 安田洋介. All rights reserved.
//

# include "dikstra.h"

using namespace std;

class comparator //Determines priority for priority queue (shortest edge comes first)
{
public:
    bool operator()(pair<int,int> &a1, pair<int,int> &a2)
    {
        return a1.second>a2.second; //sorting on basis of edge weights
    }
};

vector<int> dikstra(set<int> node_set, vector<vector<pair<int, int> > > edges){
    vector<int> distances (node_set.size(), 1000000);
    priority_queue<int, vector<pair<int, int> >, comparator > min_heap;
    
    distances[0] = 0;
    pair<int, int> first_pair (0, 0);
    min_heap.push(first_pair);

    while(node_set.size() != 0){
        
        pair<int, int> from = min_heap.top();
        min_heap.pop();
        int from_node = from.first;
        int distance = from.second;
        
        set<int>::iterator it = node_set.find(from_node);
        if(it==node_set.end()){
            continue;
        }else{
            node_set.erase(node_set.find(from_node));
        }
        
        for(int i=0; i<edges[from_node].size(); i++){
            int target_node = edges[from_node][i].first;
            int length = edges[from_node][i].second;
            set<int>::iterator it = node_set.find(target_node);
            if(it!=node_set.end() && distances[target_node] > distance + length){
                distances[target_node] = distance + length;
                pair<int, int> new_pair (target_node, distance+length);
                min_heap.push(new_pair);
            }
        }

    }
    return distances;
}

vector<int> exec_dikstra(string file_name){
    ifstream inFile(file_name);
    string line;
    int node_count = 0;;
    while (getline(inFile, line)){
        istringstream iss(line);
        int from;
        iss >> from;
        if(node_count < from){
            node_count = from;
        }
        string edge_data;
        while(iss >> edge_data){
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
        istringstream iss(line);
        int from;
        iss >> from;
        string edge_data;
        while(iss >> edge_data){
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
