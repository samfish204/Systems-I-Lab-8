// Copyright 2020 Samuel Fisher
// lab8
// CSE278 - Section B
// Professor Vendome
// October 21, 2020
// This program creates a query and allows the user
// to supply sql commands to interact with a database.
#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

void interactive() {
    // Connect to database with: database, server, userID, password
    mysqlpp::Connection myDB("cse278", "localhost",
         "cse278", "S3rul3z");

    // Variable to build query string
    std::string qString;

    // Get user input for query
    while (std::getline(std::cin, qString) && qString != std::string("quit")) {
        // Create a query
        mysqlpp::Query query = myDB.query();
        query << qString;

        try {
            // Check query is correct
            query.parse();
            // Execute query
            mysqlpp::StoreQueryResult result = query.store();
            // Results is a 2D vector of mysqlpp::String objects.
            // Print the results.
            std::cout << "-----Query Result-----" << std::endl;
            for (size_t row = 0; (row < result.size()); row++) {
                for (size_t col = 0; (col < result[row].size()); col++) {
                    std::cout << "| " << result[row][col] << " ";
                }
                std::cout << "|" << std::endl;
            }
            std::cout << "------End Result------" << std::endl;
        } catch(mysqlpp::BadQuery e) {
            std::cerr << "Query: " << qString <<std::endl;
            std::cerr << "Query is not correct SQL syntax" <<std::endl;
        }
    }
}

/*
std::string generateLoadQuery(std::string& line){
    // Create base insert query string

    // Split file on commas

    // Start building query from split files (table name)

    // Strings to hold attributes and values

    // Build attribute and value strings

    // Form full query string

}

void loadData(std::string& path){
    // Open file stream

    // Connect to database with: database, server, userID, password


    // Some necessary variables for the file IO

    // Read file line-by-line
    while (/* reading lines */ //) {
        // Create query string from current line

        // Create mysql++ query
/*
        try{
            // Check query is correct

            // Execute Query
            std::cout << /* feedback it worked - format on assignment */;
/*        } catch(mysqlpp::BadQuery e) {
            std::cerr << "Query: " << queryStr<<std::endl;
            std::cerr << "Query is not correct SQL syntax" <<std::endl;
        }
    }

}
*/

int main(int argc, char *argv[]) {
    // Ensure arguments are specified
    if (argc < 2) {
        std::cerr << "Specify arguments" << std::endl;
        return 1;
    }

    std::string option = argv[1];

    if (option == std::string("-I")) {
        interactive();
    } else {
        std::cerr << "Invalid input" << std::endl;
        return 1;
    }

    // All done
    return 0;
}
