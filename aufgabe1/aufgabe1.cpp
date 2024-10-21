#include "aufgabe1.hpp"
#include <string>
#include <iostream>
#include <utility>
#include <fstream>

char complement(char const x){
    if (x == 'A'){
        return 'T';
    } else if (x == 'T'){
        return 'A';
    } else if (x == 'C'){
        return 'G';
    } else if (x == 'G'){
        return 'C';
    } else {
        std::cerr << "Wrong Input" << std::endl;
    }
    return ' ';
}

std::string reverseComplement(std::string const& input){
    std::string output = "";
    unsigned int n = input.length();
    for (unsigned int i = 0; i < n; ++i){
        output.push_back(complement(input[n-i-1]));
    }
    return output;
}

std::pair<std::string, std::string> readFasta(std::string const& in_file){
    std::ifstream file(in_file);
    if (!file.is_open()) {
        return std::pair<std::string, std::string>("","");
    }
    std::string line;
    
    std::getline(file, line);
    std::string meta = line.substr(1);
    
    std::string seq;
    while (std::getline(file, line)) {
        seq.append(line);
    }
    
    file.close();
    return std::pair<std::string, std::string>(meta,seq);
}

bool writeFasta(std::string const& out_file, std::string const& meta, std::string const& seq){
    std::ofstream file(out_file);
    if (!file.is_open()) {
        return false;
    }
    
    file << ">" << meta;
    for (unsigned int i = 0; i < seq.length(); ++i){
        if (i % 80 == 0){
            file << std::endl;
        }
        file << seq[i];
    }
    file << std::endl;
    
    file.close();
    return true;
}

bool reverseComplementFASTA(std::string const& input_file, std::string const& output_file){
    auto input_result = readFasta(input_file);
    auto meta = input_result.first;
    auto seq = input_result.second;
    if ((meta == "") and (seq == "")){
        return false;
    }

    auto seq2 = reverseComplement(seq);
    return writeFasta(output_file, meta, seq2);
}

