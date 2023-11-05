#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <map>

void datadefault(std::vector<std::string>& name, std::vector<int>& score);
void data_scelta(std::vector<std::string> name, std::vector<int> score, int grandezza);
void data_a_mano(std::vector<std::string> name, std::vector<int> score);
void print_versione_uno(const std::vector<std::string> name, const std::vector<int> score);
void print_versione_tre(const std::vector<std::string> name, const std::vector<int> score);
double media(std::vector<int>& score);
int smode(std::vector<int> score, const int size);
void findIn(std::vector<int> score, std::vector<std::string> name, int size, int target);

int main() {
    std::vector<std::string> name;
    std::vector<int> score;
    int scelto;
    std::cout << "Hello! Before beginning to analyze data you must choose a way to initialize your vector\n";
    std::cout << "1. Default values\n2. Random values\n3. User input\n";
    std::cout << "Your choice: ";
    std::cin >> scelto;

    switch (scelto) {
    case 1:
        datadefault(name, score);
        break;

    case 2:
        int size;
        std::cout << "Choose the size of the vector: ";
        std::cin >> size;
        data_scelta(name, score, size);
        break;

    case 3:
        data_a_mano(name, score);
        break;

    default:
        std::cout << "Oops! Seems like the values is wrong. Programm will be completed immediately after message!";
        break;
    }

    print_versione_uno(name, score);
    double media_aritm = media(score);
    std::cout << "Average of the scores equals: " << media_aritm << std::endl;
    int mode = smode(score, score.size());
    std::cout << "Mode equals: " << mode << std::endl;
    findIn(score, name, score.size(), mode);

    return 0;
}
// 
void datadefault(std::vector<std::string>& name, std::vector<int>& score) {
    name = { "Marco", "Lorenzo", "Fabrizio", "Paola", "Antonio", "Francesca", "Fabio", "Gianluca", "Rosario", "Guglielmo"};
    score = {100, 96, 37, 59, 59, 73, 45, 24, 73, 67};
}

void data_scelta(std::vector<std::string> name, std::vector<int> score, int grandezza) {
    std::cout << "Choose the size of the vector: ";
    std::cin >> grandezza;
    for (int i = 0; i < grandezza; i++) {
        score.push_back(rand() % 101);
    }
}

void data_a_mano(std::vector<std::string> name, std::vector<int> score) {
    int size;
    std::cout << "Choose the amount of the students: ";
    std::cin >> size;
    std::cout << "Alright! Now insert the name and the score for each student.\n";
    for (int i = 0; i < size; i++) {
        std::string nome;
        int voto;
        std::cout << "Student " << i + 1 << "'s name: ";
        std::cin >> nome;
        name.push_back(nome);
        std::cout << "Student " << i + 1 << "'s score: ";
        std::cin >> voto;
        score.push_back(voto);
    }
}


void print_versione_uno(const std::vector<std::string> name, const std::vector<int> score) {
    for (auto i : name)
        std::cout << i << "  ";
    std::cout << std::endl;

    for (auto j : score)
        std::cout << j << "       ";
    std::cout << std::endl;
}
void print_versione_tre(const std::vector<std::string> name, const std::vector<int> score) {
    for (int i = 0; i < name.size(); i++) {
        std::cout << name[i] << std::endl;
    }
    std::cout << std::endl;
    for (int j = 0; j < score.size(); j++) {
        std::cout << score[j] << std::endl;
    }
}

double media(std::vector<int>& score) {
    double sum = std::accumulate(score.begin(), score.end(), 0);
    double n = score.size();
    double media_aritmetica = sum / n;
    return media_aritmetica;
}

int smode(std::vector<int> score, const int size) {
    int maxVal = 0, maxCount = 0;

    for (int i = 0; i < size; i++) {     
        int count = 0;
        for (int j = 0; j < size; j++) {  
            if (score[j] == score[i])     
                count++;    
        }
        if (count > maxCount) {  
            maxCount = count;
            maxVal = score[i];
        }
        else if (maxCount == 1)
            maxVal = -1; 
    }
    return maxVal;
}

void findIn(std::vector<int> score, std::vector<std::string> name, int size, int target) {
    target = smode(score, size);
    std::cout << "Names corresponding to mode:" << std::endl;
    for (int i = 0; i < size; i++) {
        if (score[i] == target) {
            std::cout << name[i] << std::endl;
        }
    }
}