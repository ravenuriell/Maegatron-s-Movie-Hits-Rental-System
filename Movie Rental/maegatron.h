#ifndef MAEGATRON_H
#define MAEGATRON_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <vector>
#include <stack>
#include <deque>
#include <list>

class Maegatron {
private:
    struct VideoNode {
        int id;
        std::string title;
        std::string genre;
        std::string production;
        int copies;
    };

    struct CustomerNode {
        int cID;
        std::string name;
        std::string address;
    };

    struct CustomerRent {
        int vid_ID;
        int cust_ID;
    };

    int tempCode = 0;
    int tempCustomer = 0;

    CustomerNode cust;
    VideoNode mov;
    CustomerRent r;

    std::deque<CustomerNode> customer;
    std::list<VideoNode> vid;
    std::stack<CustomerRent> rent;
    std::vector<CustomerRent> stk;

public:
    void videoIDGenerate();
    void customerIDGenerate();

    void insertMovie();
    void vidDetails();
    void displayList();
    void availability();
    void vidSave();
    void vidLoad();

    void newCustomer();
    void custDetails();
    void custRentedList();
    void custSave();
    void custLoad();

    void vidRent();
    void save_vidRent();
    void load_vidRent();
    void returnVid();
};

#endif // MAEGATRON_H
