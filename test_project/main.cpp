//
//  main.cpp
//  test_project
//
//  Created by 安田洋介 on 11/15/15.
//  Copyright © 2015 安田洋介. All rights reserved.
//
#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

#include "dikstra.h"

using namespace std;

TEST_CASE("dikstra"){
    int t_1_expect[] = {0, 8, 3, 6, 13};
    vector<int> test_1_expect (t_1_expect, t_1_expect + sizeof(t_1_expect)/sizeof(int));
    vector<int> result_test1 = exec_dikstra("test1.txt");
    for(int i=0; i<test_1_expect.size(); i++){
        REQUIRE(result_test1[i] == test_1_expect[i]);
    }
}