#include "OpenAddressing.h"
#include "SeparateChaining.h"
#include "Sales.h"
#include <iostream>
#include <fstream>

using namespace std;

//first getKey combines rank and name
string getSalesRankName(Sales sales) {
    return to_string(sales.getRank()) + sales.getName();
}

//second getKey combines rank and platform then uses Hornerhash
string getSalesRankPlatform(Sales sales) {
    string key = to_string(sales.getRank()) + sales.getPlatform();
    unsigned long hashVal = 0;

    for (char letter : key) {
        hashVal = hashVal * 37 + letter;
    }
    return to_string(hashVal);
}

int main() {
    //Loads vgsales into vector and sizes to 1000
    vector<Sales> salesVec;
    loadFromFile("../vgsales.csv",salesVec);
    salesVec.resize(1000);

    //Creates SeperateChaining hash tables of different sizes for RankName and RankPlatform
    SeparateChaining<Sales> S1(1100);
    SeparateChaining<Sales> S2(1700);
    SeparateChaining<Sales> S3(2400);
    SeparateChaining<Sales> S4(2500);
    SeparateChaining<Sales> S5(3000);
    SeparateChaining<Sales> S6(1100);
    SeparateChaining<Sales> S7(1700);
    SeparateChaining<Sales> S8(2500);
    SeparateChaining<Sales> S9(2500);
    SeparateChaining<Sales> S10(3500);

    //Creates QuadraticProbing hash tables of different sizes for RankName and RankPlatform
    QuadraticProbing<Sales> Q1(1100);
    QuadraticProbing<Sales> Q2(1700);
    QuadraticProbing<Sales> Q3(2400);
    QuadraticProbing<Sales> Q4(2500);
    QuadraticProbing<Sales> Q5(3000);
    QuadraticProbing<Sales> Q6(1100);
    QuadraticProbing<Sales> Q7(1700);
    QuadraticProbing<Sales> Q8(2400);
    QuadraticProbing<Sales> Q9(2500);
    QuadraticProbing<Sales> Q10(3000);

    //Loops through salesVec to insert all entries into hash tables
    for (const Sales& game : salesVec) {
        //First 5 insert rank and name into SeparateChaining, last 5 insert rank and platform
        S1.insert(getSalesRankName(game),game);
        S2.insert(getSalesRankName(game),game);
        S3.insert(getSalesRankName(game),game);
        S4.insert(getSalesRankName(game),game);
        S5.insert(getSalesRankName(game),game);
        S6.insert(getSalesRankPlatform(game),game);
        S7.insert(getSalesRankPlatform(game),game);
        S8.insert(getSalesRankPlatform(game),game);
        S9.insert(getSalesRankPlatform(game),game);
        S10.insert(getSalesRankPlatform(game),game);

        //First 5 insert rank and  into QuadraticProbing, last 5 insert rank and platform
        Q1.insert(getSalesRankName(game),game);
        Q2.insert(getSalesRankName(game),game);
        Q3.insert(getSalesRankName(game),game);
        Q4.insert(getSalesRankName(game),game);
        Q5.insert(getSalesRankName(game),game);
        Q6.insert(getSalesRankPlatform(game),game);
        Q7.insert(getSalesRankPlatform(game),game);
        Q8.insert(getSalesRankPlatform(game),game);
        Q9.insert(getSalesRankPlatform(game),game);
        Q10.insert(getSalesRankPlatform(game),game);
    }

    //Outputs SeparateChaining results to sOut
    ofstream sOut("sOut.txt");

    sOut << "S1, 1100, RankName," << S1.getCollisions() << endl;
    sOut << "S2, 1700, RankName," << S2.getCollisions() << endl;
    sOut << "S3, 2400, RankName," << S3.getCollisions() << endl;
    sOut << "S4, 2500, RankName," << S4.getCollisions() << endl;
    sOut << "S5, 3000, RankName," << S5.getCollisions() << endl;
    sOut << "S6, 1100, RankPlatform," << S6.getCollisions() << endl;
    sOut << "S7, 1700, RankPlatform," << S7.getCollisions() << endl;
    sOut << "S8, 2400, RankPlatform," << S8.getCollisions() << endl;
    sOut << "S9, 2500, RankPlatform," << S9.getCollisions() << endl;
    sOut << "S10, 3000, RankPlatform," << S10.getCollisions() << endl;
    sOut.close();


    //Outputs QuadraticProbing results to qOut
    ofstream qOut("qOut.txt");

    qOut << "Q1, 1100, RankName," << Q1.getCollisions() << endl;
    qOut << "Q2, 1700, RankName," << Q2.getCollisions() << endl;
    qOut << "Q3, 2400, RankName," << Q3.getCollisions() << endl;
    qOut << "Q4, 2500, RankName," << Q4.getCollisions() << endl;
    qOut << "Q5, 3000, RankName," << Q5.getCollisions() << endl;
    qOut << "Q6, 1100, RankPlatform," << Q6.getCollisions() << endl;
    qOut << "Q7, 1700, RankPlatform," << Q7.getCollisions() << endl;
    qOut << "Q8, 2400, RankPlatform," << Q8.getCollisions() << endl;
    qOut << "Q9, 2500, RankPlatform," << Q9.getCollisions() << endl;
    qOut << "Q10, 3000, RankPlatform," << Q10.getCollisions() << endl;
    qOut.close();

    //Outputs QuadraticProbing table size
    cout << Q1.getTableSize() << endl;
    cout << Q2.getTableSize() << endl;
    cout << Q3.getTableSize() << endl;
    cout << Q4.getTableSize() << endl;
    cout << Q5.getTableSize() << endl;
    cout << Q6.getTableSize() << endl;
    cout << Q7.getTableSize() << endl;
    cout << Q8.getTableSize() << endl;
    cout << Q9.getTableSize() << endl;
    cout << Q10.getTableSize() << endl;

    return 0;
}
