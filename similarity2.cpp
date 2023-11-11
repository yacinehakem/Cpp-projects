#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

double calculerSimilarite(const std::string& contenu1, const std::string& contenu2) {
    // Calculer le nombre de caractères en commun entre les deux fichiers
    size_t tailleMin = std::min(contenu1.size(), contenu2.size());
    size_t caracteresCommuns = 0;

    for (size_t i = 0; i < tailleMin; ++i) {
        if (contenu1[i] == contenu2[i]) {
            ++caracteresCommuns;
        }
    }

    // Calculer le pourcentage de similarité
    double similarite = (static_cast<double>(caracteresCommuns) / std::max(contenu1.size(), contenu2.size())) * 100.0;

    return similarite;
}

int main() {
    // Déclaration des noms de fichiers
    std::string nomFichier1 = "fichier1.txt";
    std::string nomFichier2 = "fichier2.txt";

    // Lecture du premier fichier
    std::ifstream fichier1(nomFichier1);
    if (!fichier1.is_open()) {
        std::cerr << "Erreur lors de l'ouverture de " << nomFichier1 << std::endl;
        return 1;
    }

    std::string contenu1((std::istreambuf_iterator<char>(fichier1)), std::istreambuf_iterator<char>());
    fichier1.close();

    // Lecture du deuxième fichier
    std::ifstream fichier2(nomFichier2);
    if (!fichier2.is_open()) {
        std::cerr << "Erreur lors de l'ouverture de " << nomFichier2 << std::endl;
        return 1;
    }

    std::string contenu2((std::istreambuf_iterator<char>(fichier2)), std::istreambuf_iterator<char>());
    fichier2.close();

    // Calculer et afficher le pourcentage de similarité
    double similarite = calculerSimilarite(contenu1, contenu2);
    std::cout << "Pourcentage de similarite : " << similarite << "%" << std::endl;

    return 0;
}
