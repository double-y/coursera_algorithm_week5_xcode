//
//  dikstra.h
//  coursera_week5
//
//  Created by 安田洋介 on 11/15/15.
//  Copyright © 2015 安田洋介. All rights reserved.
//

#ifndef dikstra_h
#define dikstra_h

#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <tuple>
#include <sstream>
#include <string>

std::vector<int> dikstra(std::set<int> node_set, std::vector<std::vector<std::pair<int, int> > > edges);
std::vector<int> exec_dikstra(std::string file_name);

#endif /* dikstra_h */
