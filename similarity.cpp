#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <cmath>
#include <algorithm>

double calculerSimilarite(const std::unordered_map<std::string, int>& vecteur1, const std::unordered_map<std::string, int>& vecteur2) {
    double produitScalaire = 0.0;
    double normeVecteur1 = 0.0;
    double normeVecteur2 = 0.0;

    // Calcul du produit scalaire
    for (const auto& paire : vecteur1) {
        if (vecteur2.count(paire.first) > 0) {
            produitScalaire += paire.second * vecteur2.at(paire.first);
        }
        normeVecteur1 += std::pow(paire.second, 2);
    }

    for (const auto& paire : vecteur2) {
        normeVecteur2 += std::pow(paire.second, 2);
    }

    // Calcul de la norme euclidienne
    normeVecteur1 = std::sqrt(normeVecteur1);
    normeVecteur2 = std::sqrt(normeVecteur2);

    // Calcul de la similarité normalisée
    double similarite = produitScalaire / (normeVecteur1 * normeVecteur2);

    return similarite;
}

std::unordered_map<std::string, int> construireVecteur(const std::string& contenu) {
    std::unordered_map<std::string, int> vecteur;
    std::istringstream iss(contenu);
    std::string mot;

    while (iss >> mot) {
        // Ignorer la ponctuation et mettre tous les mots en minuscules (à des fins de simplification)
        std::transform(mot.begin(), mot.end(), mot.begin(), ::tolower);
        mot.erase(std::remove_if(mot.begin(), mot.end(), ::ispunct), mot.end());

        // Mettre à jour le vecteur
        vecteur[mot]++;
    }

    return vecteur;
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

    // Construire les vecteurs pour les deux fichiers
    std::unordered_map<std::string, int> vecteur1 = construireVecteur(contenu1);
    std::unordered_map<std::string, int> vecteur2 = construireVecteur(contenu2);

    // Calculer et afficher le pourcentage de similarité
    double similarite = calculerSimilarite(vecteur1, vecteur2);
    similarite *= 100.0; // Convertir en pourcentage
    std::cout << "Pourcentage de similarite : " << similarite << "%" << std::endl;

    return 0;
}
