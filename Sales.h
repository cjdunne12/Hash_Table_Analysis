#ifndef SALES_H
#define SALES_H
#include <string>
#include <vector>
#include <fstream>

/*
 *Class Representing Videogame Sales in different regions of the world
 * Fields:
 *      Rank: Comparative Popularity Rank
 *      Name: Game name
 *      Platform: Release Platform
 *      Year: Release year
 *      Genre: Game genre
 *      Publisher: Game publisher
 *      NA_Sales: Number of sales made in North America in millions
 *      EU_Sales: Number of sales made in Europe in millions
 *      JP_Sales: Number of sales made in Japan in millions
 *      Other_Sales: Number of sales made in non NA, EU, JP countries in millions
 *      Global_Sales: Number of sales made globally in millions
 */
class Sales {
private:std::string name, platform, genre, publisher;
        int rank, year;
        double naSales, euSales, jpSales, otherSales, globalSales;

public:
        Sales() {
                name = "Default";
                platform = "Default";
                genre = "Default";
                publisher = "Default";
                rank = 0;
                year = 0;
                naSales= 0.0;
                euSales= 0.0;
                jpSales= 0.0;
                otherSales= 0.0;
                globalSales= 0.0;

        }
        Sales(int rank, int year,
              std::string name, std::string platform, std::string genre, std::string publisher,
              double naSales, double euSales, double jpSales, double otherSales, double globalSales) {
                this->rank = rank;
                this->year = year;
                this->name = name;
                this->platform = platform;
                this->genre = genre;
                this->publisher = publisher;
                this->naSales = naSales;
                this->euSales = euSales;
                this->jpSales = jpSales;
                this->otherSales = otherSales;
                this->globalSales = globalSales;
        }

        //Getters
        int getRank() const
        {
                return rank;
        }
        int getYear() const {
                return year;
        }
        std::string getName() const {
                return name;
        }
        std::string getPlatform() const {
                return platform;
        }
        std::string getGenre() const {
                return genre;
        }
        std::string getPublisher() const {
                return publisher;
        }
        double getNaSales() const {
                return naSales;
        }
        double getEuSales() const {
                return euSales;
        }
        double getJpSales() const {
                return jpSales;
        }
        double getOtherSales() const {
                return otherSales;
        }
        double getGlobalSales() const {
                return globalSales;
        }

        //Setters
        void setRank(int rank) {
                this->rank = rank;
        }
        void setYear(int year) {
                this->year = year;
        }
        void setName(std::string name) {
                this->name = name;
        }
        void setPlatform(std::string platform) {
                this->platform = platform;
        }
        void setGenre(std::string genre) {
                this->genre = genre;
        }
        void setPublisher(std::string publisher) {
                this->publisher = publisher;
        }
        void setNaSales(double naSales) {
                this->naSales = naSales;
        }
        void setEuSales(double euSales) {
                this->euSales = euSales;
        }
        void setJpSales(double jpSales) {
                this->jpSales = jpSales;
        }
        void setOtherSales(double otherSales) {
                this->otherSales = otherSales;
        }
        void setGlobalSales(double globalSales) {
                this->globalSales = globalSales;
        }


};

//Loads file
bool loadFromFile(std::string fn, std::vector<Sales>& objs) {
        std::ifstream fin;
        fin.open(fn);

        if (!fin) {
                return false;
        }

        std::string header = "";
        getline(fin, header);

        int rank, year;
        std::string name, platform, genre, publisher;
        double naSales, euSales, jpSales, otherSales, globalSales;
        char comma;

        while (fin && fin.peek() != EOF) {
                fin >> rank >> comma;
                getline(fin, name, ',');
                getline(fin, platform, ',');
                fin >> year;
                //Sometimes year is N/A
                if (!fin) {
                        year = 0000;
                        fin.clear();
                }
                fin >> comma;
                getline(fin, genre, ',');
                getline(fin, publisher, ',');
                fin >> naSales;
                fin >> comma;
                fin >> euSales;
                fin >> comma;
                fin >> jpSales;
                fin >> comma;
                fin >> otherSales;
                fin >> comma;
                fin >> globalSales;

                Sales game(rank, year, name, platform, genre, publisher,
                      naSales, euSales, jpSales, otherSales, globalSales);
                objs.push_back(game);
        }
        fin.close();
        return true;
}

//Totals up sales from each region for each game and prints it
void salesTotal(const std::vector<Sales>& objs) {
        double naTotal = 0.0;
        double euTotal = 0.0;
        double jpTotal = 0.0;
        double otherTotal = 0.0;
        double globalTotal = 0.0;

        for (const Sales& obj : objs) {
                naTotal += obj.getNaSales();
                euTotal += obj.getEuSales();
                jpTotal += obj.getJpSales();
                otherTotal += obj.getOtherSales();
                globalTotal += obj.getGlobalSales();
        }
        std::cout << "NA Total in millions: " << naTotal << std::endl;
        std::cout << "EU Total in millions: " << euTotal << std::endl;
        std::cout << "JP Total in millions: " << jpTotal << std::endl;
        std::cout << "Other Total in millions: " << otherTotal << std::endl;
        std::cout << "Global Total in millions: " << globalTotal << std::endl;
}

//Tests the getters, setters, and constructor
bool salesTest() {
        bool passed = true;
        Sales testObject = Sales();

        testObject.setRank(1);
        if (testObject.getRank() != 1) {
                std::cout << "Error in setRank" << std::endl;
                passed = false;
        }

        testObject.setYear(2000);
        if (testObject.getYear() != 2000) {
                std::cout << "Error in setYear" << std::endl;
                passed = false;
        }
        testObject.setName("Videogame");
        if (testObject.getName() != "Videogame") {
                std::cout << "Error in setName" << std::endl;
                passed = false;
        }
        testObject.setPlatform("PC");
        if (testObject.getPlatform() != "PC") {
                std::cout << "Error in setPlatform" << std::endl;
                passed = false;
        }
        testObject.setGenre("Adventure");
        if (testObject.getGenre() != "Adventure") {
                std::cout << "Error in setGenre" << std::endl;
                passed = false;
        }
        testObject.setPublisher("Sales");
        if (testObject.getPublisher() != "Sales") {
                std::cout << "Error in setPublisher" << std::endl;
                passed = false;
        }
        testObject.setNaSales(1.1);
        if (testObject.getNaSales() != 1.1) {
                std::cout << "Error in setNaSales" << std::endl;
                passed = false;
        }
        testObject.setEuSales(1.1);
        if (testObject.getEuSales() != 1.1) {
                std::cout << "Error in setEuSales" << std::endl;
                passed = false;
        }
        testObject.setJpSales(1.1);
        if (testObject.getJpSales() != 1.1) {
                std::cout << "Error in setJpSales" << std::endl;
                passed = false;
        }
        testObject.setOtherSales(1.1);
        if (testObject.getOtherSales() != 1.1) {
                std::cout << "Error in setOtherSales" << std::endl;
                passed = false;
        }
        testObject.setGlobalSales(1.1);
        if (testObject.getGlobalSales() != 1.1) {
                std::cout << "Error in setGlobalSales" << std::endl;
                passed = false;
        }

        Sales testObject2 = Sales(10, 2005, "Games", "Console", "Action","Company",
                2.0, 1.5, 3.1, .5, 7.1);

        if (testObject2.getRank() != 10 ||
            testObject2.getYear() != 2005 ||
            testObject2.getName() != "Games" ||
            testObject2.getPlatform() != "Console" ||
            testObject2.getGenre() != "Action" ||
            testObject2.getPublisher() != "Company" ||
            testObject2.getNaSales() != 2.0 ||
            testObject2.getEuSales() != 1.5 ||
            testObject2.getJpSales() != 3.1 ||
            testObject2.getOtherSales() != 0.5 ||
            testObject2.getGlobalSales() != 7.1)
        {
        std::cout << "Failed non default constructor test" << std::endl;
        passed = false;
        }

        return passed;
}
#endif