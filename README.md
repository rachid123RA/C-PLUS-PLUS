# NeuroUIT - Simulateur de Réseaux Neuronaux

**NeuroUIT** (Neuro + UI + Tool) est un simulateur complet de réseaux de neurones artificiels avec interface graphique, développé en C++ avec Qt.

## 🎯 Description

NeuroUIT permet de créer, entraîner, visualiser et analyser des réseaux de neurones multicouches de manière interactive. Le projet offre une plateforme pédagogique complète pour comprendre le fonctionnement des réseaux de neurones artificiels.

## ✨ Fonctionnalités

### Core
- ✅ Création et configuration de réseaux multicouches
- ✅ Support de 4 fonctions d'activation (Sigmoid, Tanh, ReLU, Linéaire)
- ✅ Chargement de datasets au format CSV
- ✅ Entraînement avec rétropropagation et momentum
- ✅ Visualisation interactive de l'architecture du réseau
- ✅ Graphique d'évolution de l'erreur en temps réel
- ✅ Sauvegarde/chargement de réseaux (.nui)
- ✅ Export des résultats

### Visualisation et Analyse
- ✅ Métriques de performance (Accuracy, Precision, Recall, F1-Score)
- ✅ Métriques de régression (MSE, MAE, R²)
- ✅ Matrice de confusion
- ✅ Matrice de corrélation
- ✅ Graphique prédictions vs valeurs réelles
- ✅ Statistiques détaillées du dataset
- ✅ Zoom interactif sur la visualisation
- ✅ Assistant IA interactif avec Q&A

## 🛠️ Technologies Utilisées

- **Langage** : C++17
- **Framework** : Qt 6.10.1 (Core, Widgets, Charts)
- **Compilateur** : MinGW 13.1.0
- **Plateforme** : Windows 10/11
- **Architecture** : MVC (Model-View-Controller)

## 📋 Prérequis

- **Qt 6.10.1** ou supérieur (Core, Widgets, Charts)
- **MinGW 13.1.0** ou compilateur C++17 compatible
- **Windows 10/11** (testé sur Windows)
- **Qt Creator** (recommandé pour le développement)

## 📁 Structure du Projet

```
NeuroUIT/
├── include/          # Headers
│   ├── core/        # Neuron, Layer, Network, ActivationFunction
│   ├── dataset/     # DatasetManager
│   ├── training/    # Trainer
│   ├── persistence/ # Sauvegarde/chargement
│   ├── ui/          # Interface graphique
│   └── controller/  # Contrôleur MVC
├── src/             # Implémentations
├── data/            # Datasets d'exemple
├── build/           # Fichiers de compilation
├── bin/             # Exécutables
└── NeuroUIT.pro     # Fichier projet Qt
```

## 🚀 Installation

1. Clonez le dépôt :
```bash
git clone https://github.com/rachid123RA/C-PLUS-PLUS.git
cd C-PLUS-PLUS/NeuroUIT---Simulateur-de-R-seaux-Neuronaux
```

2. Ouvrez le projet dans Qt Creator :
   - Ouvrez `NeuroUIT.pro`
   - Configurez le kit Qt (Qt 6.10.1 avec MinGW)
   - Compilez le projet

3. Exécutez l'application :
   - L'exécutable sera dans le dossier `bin/`

## 📖 Utilisation

### 1. Créer un réseau
- Menu → Nouveau réseau
- Définissez l'architecture (nombre de neurones par couche)
- Choisissez les fonctions d'activation

### 2. Charger un dataset
- Menu → Charger dataset
- Sélectionnez un fichier CSV
- Indiquez le nombre d'entrées et de sorties

### 3. Configurer l'entraînement
- Cliquez sur "Lancer"
- Configurez les paramètres (taux d'apprentissage, époques, etc.)

### 4. Visualiser les résultats
- Consultez les onglets : Résultats, Erreur, Métriques, Confusion, etc.

## 📊 Datasets d'Exemple

Le dossier `data/` contient plusieurs datasets pour tester :
- `XOR_dataset.csv` - Problème XOR (classification binaire)
- `AND_dataset.csv` - Problème AND
- `OR_dataset.csv` - Problème OR
- `linear_regression.csv` - Régression linéaire
- `sine_wave.csv` - Fonction sinusoïdale
- `binary_classification.csv` - Classification binaire

## 📝 Format des Données

### Dataset CSV
Format : `input1,input2,...,output1,output2,...`
- Première ligne optionnelle : en-têtes
- Colonnes numériques uniquement
- Pas de valeurs manquantes

Exemple :
```csv
x1,x2,y
0,0,0
0,1,1
1,0,1
1,1,0
```

### Fichier réseau (.nui)
Format propriétaire JSON contenant :
- Architecture (couches, neurones)
- Fonctions d'activation
- Poids des connexions

## 👥 Équipe

**Équipe NeuroUIT**
- Ait Aissa Rachid
- Benfaress Ziad
- Saliani Bouchaib
- Flahi Sara
- Bellihy Ibtissam

## 🎓 Contexte Académique

**Projet réalisé dans le cadre du :**
- Master Intelligence Artificielle et Objets Connectés
- Année Universitaire 2025/2026
- Université Ibn Tofail Kénitra
- Faculté des Sciences de Kénitra (FSK)

**Encadrement :**
- Pr. Mohamed Daoudi

## 📄 Licence

Projet académique - Université Ibn Tofail Kénitra

## 🤝 Contribution

Ce projet est un travail académique. Pour toute question ou suggestion, n'hésitez pas à ouvrir une issue.

## 📚 Documentation

Un rapport détaillé est disponible dans le fichier `rapport_neurouit.tex` (LaTeX).

## 🐛 Problèmes Connus

- Interface limitée à Windows (portabilité à améliorer)
- Support limité aux réseaux feedforward (pas de réseaux récurrents)

## 🔮 Améliorations Futures

- Support des réseaux récurrents (RNN, LSTM)
- Optimiseurs avancés (Adam, RMSprop)
- Techniques de régularisation (dropout, batch normalization)
- Support multi-plateformes (Linux, macOS)

## 📧 Contact

Pour toute question concernant ce projet, contactez l'équipe via GitHub.

---

**Développé avec ❤️ par l'équipe NeuroUIT**
