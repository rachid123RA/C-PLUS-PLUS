#include "ui/AIAssistantDialog.h"
#include <QScrollArea>
#include <QGroupBox>
#include <QFont>
#include <QFontMetrics>
#include <QSizePolicy>

AIAssistantDialog::AIAssistantDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("🧙 Assistant IA - Guide des Réseaux de Neurones");
    setMinimumSize(900, 700);
    resize(1000, 750);
    
    setupUI();
    initializeKnowledgeBase();
    displayWelcomeMessage();
}

AIAssistantDialog::~AIAssistantDialog() {
}

void AIAssistantDialog::setupUI() {
    mainLayout_ = new QVBoxLayout(this);
    mainLayout_->setSpacing(15);
    mainLayout_->setContentsMargins(20, 20, 20, 20);
    
    // En-tête avec message de bienvenue
    QGroupBox* headerBox = new QGroupBox;
    QVBoxLayout* headerLayout = new QVBoxLayout(headerBox);
    headerLayout->setContentsMargins(15, 15, 15, 15);
    
    welcomeLabel_ = new QLabel;
    welcomeLabel_->setWordWrap(true);
    welcomeLabel_->setStyleSheet(
        "QLabel { "
        "font-size: 14pt; "
        "font-weight: bold; "
        "color: #2196F3; "
        "padding: 10px; "
        "background-color: #E3F2FD; "
        "border-radius: 8px; "
        "}"
    );
    headerLayout->addWidget(welcomeLabel_);
    mainLayout_->addWidget(headerBox);
    
    // Layout horizontal pour le contenu principal
    contentLayout_ = new QHBoxLayout;
    contentLayout_->setSpacing(15);
    
    // Panneau gauche : Catégories et Questions
    QVBoxLayout* leftLayout = new QVBoxLayout;
    leftLayout->setSpacing(10);
    
    QLabel* categoryLabel = new QLabel("📚 Catégories :");
    categoryLabel->setStyleSheet("font-weight: bold; font-size: 11pt; color: #424242;");
    leftLayout->addWidget(categoryLabel);
    
    categoryList_ = new QListWidget;
    categoryList_->setMaximumWidth(200);
    categoryList_->setStyleSheet(
        "QListWidget { "
        "border: 2px solid #BDBDBD; "
        "border-radius: 5px; "
        "background-color: #FAFAFA; "
        "padding: 5px; "
        "}"
        "QListWidget::item { "
        "padding: 8px; "
        "border-radius: 3px; "
        "margin: 2px; "
        "}"
        "QListWidget::item:selected { "
        "background-color: #2196F3; "
        "color: white; "
        "}"
        "QListWidget::item:hover { "
        "background-color: #E3F2FD; "
        "}"
    );
    leftLayout->addWidget(categoryList_);
    
    QLabel* questionLabel = new QLabel("❓ Questions :");
    questionLabel->setStyleSheet("font-weight: bold; font-size: 11pt; color: #424242; margin-top: 10px;");
    leftLayout->addWidget(questionLabel);
    
    questionList_ = new QListWidget;
    questionList_->setStyleSheet(
        "QListWidget { "
        "border: 2px solid #BDBDBD; "
        "border-radius: 5px; "
        "background-color: #FAFAFA; "
        "padding: 5px; "
        "}"
        "QListWidget::item { "
        "padding: 10px; "
        "border-radius: 3px; "
        "margin: 2px; "
        "min-height: 40px; "
        "}"
        "QListWidget::item:selected { "
        "background-color: #4CAF50; "
        "color: white; "
        "}"
        "QListWidget::item:hover { "
        "background-color: #C8E6C9; "
        "}"
    );
    leftLayout->addWidget(questionList_);
    
    contentLayout_->addLayout(leftLayout, 1);
    
    // Panneau droit : Réponses
    QVBoxLayout* rightLayout = new QVBoxLayout;
    
    QLabel* answerLabel = new QLabel("💡 Réponse détaillée :");
    answerLabel->setStyleSheet("font-weight: bold; font-size: 11pt; color: #424242;");
    rightLayout->addWidget(answerLabel);
    
    answerDisplay_ = new QTextEdit;
    answerDisplay_->setReadOnly(true);
    answerDisplay_->setStyleSheet(
        "QTextEdit { "
        "border: 2px solid #BDBDBD; "
        "border-radius: 5px; "
        "background-color: #FFFFFF; "
        "padding: 15px; "
        "font-size: 11pt; "
        "line-height: 1.6; "
        "}"
    );
    rightLayout->addWidget(answerDisplay_, 2);
    
    contentLayout_->addLayout(rightLayout, 2);
    
    mainLayout_->addLayout(contentLayout_, 1);
    
    // Bouton de fermeture
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    
    closeButton_ = new QPushButton("Fermer");
    closeButton_->setStyleSheet(
        "QPushButton { "
        "background-color: #2196F3; "
        "color: white; "
        "font-weight: bold; "
        "font-size: 11pt; "
        "padding: 10px 30px; "
        "border: none; "
        "border-radius: 5px; "
        "}"
        "QPushButton:hover { "
        "background-color: #1976D2; "
        "}"
        "QPushButton:pressed { "
        "background-color: #0D47A1; "
        "}"
    );
    buttonLayout->addWidget(closeButton_);
    mainLayout_->addLayout(buttonLayout);
    
    // Connexions
    connect(categoryList_, &QListWidget::currentRowChanged, this, &AIAssistantDialog::onCategoryChanged);
    connect(questionList_, &QListWidget::itemClicked, this, &AIAssistantDialog::onQuestionSelected);
    connect(closeButton_, &QPushButton::clicked, this, &QDialog::accept);
}

void AIAssistantDialog::initializeKnowledgeBase() {
    // Catégorie 1: Introduction et Bienvenue
    categories_ << "Introduction" << "Fonctionnement" << "Architecture" << "Dataset" 
                << "Entraînement" << "Paramètres" << "Métriques" << "Conseils";
    
    QMap<QString, QString> intro;
    intro["Qu'est-ce qu'un réseau de neurones ?"] = 
        "Un réseau de neurones est un modèle informatique inspiré du fonctionnement du cerveau humain.\n\n"
        "🔹 **Composants principaux :**\n"
        "• **Neurones** : Unités de calcul qui reçoivent des entrées, les traitent et produisent une sortie\n"
        "• **Connexions** : Liens entre les neurones avec des poids (weights) qui déterminent l'importance de chaque connexion\n"
        "• **Couches** : Groupes de neurones organisés en couches (entrée, cachées, sortie)\n\n"
        "🔹 **Fonctionnement :**\n"
        "Les données entrent par la couche d'entrée, sont traitées par les couches cachées, et produisent un résultat à la sortie. "
        "Le réseau apprend en ajustant les poids des connexions pendant l'entraînement.\n\n"
        "🔹 **Applications :**\n"
        "Reconnaissance d'images, traitement du langage naturel, prédictions, classification, etc.";
    
    intro["Pourquoi utiliser un réseau de neurones ?"] = 
        "Les réseaux de neurones sont particulièrement utiles pour :\n\n"
        "✅ **Reconnaissance de patterns complexes** : Ils peuvent identifier des motifs que les algorithmes traditionnels ne peuvent pas détecter\n\n"
        "✅ **Apprentissage automatique** : Ils apprennent à partir d'exemples sans programmation explicite de chaque règle\n\n"
        "✅ **Généralisation** : Une fois entraînés, ils peuvent traiter de nouvelles données similaires\n\n"
        "✅ **Tolérance au bruit** : Ils peuvent fonctionner même avec des données imparfaites ou incomplètes\n\n"
        "✅ **Non-linéarité** : Ils peuvent modéliser des relations complexes et non-linéaires entre les données";
    
    knowledgeBase_["Introduction"] = intro;
    
    // Catégorie 2: Fonctionnement
    QMap<QString, QString> fonctionnement;
    fonctionnement["Comment fonctionne un réseau de neurones ?"] = 
        "Le fonctionnement d'un réseau de neurones se déroule en plusieurs étapes :\n\n"
        "**1. Propagation avant (Forward Propagation) :**\n"
        "   • Les données d'entrée sont présentées à la couche d'entrée\n"
        "   • Chaque neurone calcule : somme pondérée des entrées × poids + biais\n"
        "   • Une fonction d'activation transforme cette somme (ex: sigmoïde, ReLU)\n"
        "   • Le résultat est transmis à la couche suivante\n"
        "   • Ce processus se répète jusqu'à la couche de sortie\n\n"
        "**2. Calcul de l'erreur :**\n"
        "   • La sortie du réseau est comparée à la valeur attendue\n"
        "   • L'erreur est calculée (ex: erreur quadratique moyenne)\n\n"
        "**3. Rétropropagation (Backpropagation) :**\n"
        "   • L'erreur est propagée en arrière à travers le réseau\n"
        "   • Les poids sont ajustés pour réduire l'erreur\n"
        "   • Le taux d'apprentissage détermine l'amplitude des ajustements\n\n"
        "**4. Répétition :**\n"
        "   • Ce cycle se répète pour chaque échantillon d'entraînement\n"
        "   • Le réseau s'améliore progressivement";
    
    fonctionnement["Qu'est-ce qu'une fonction d'activation ?"] = 
        "Une fonction d'activation détermine la sortie d'un neurone en fonction de sa somme pondérée.\n\n"
        "**Rôle principal :**\n"
        "• Introduire la non-linéarité dans le réseau\n"
        "• Permettre au réseau d'apprendre des patterns complexes\n"
        "• Limiter la sortie à une plage spécifique\n\n"
        "**Types courants :**\n\n"
        "🔹 **Sigmoïde** :\n"
        "   • Plage : [0, 1]\n"
        "   • Utilisée pour : classification binaire, couches de sortie\n"
        "   • Avantage : sortie lisse et différentiable\n\n"
        "🔹 **ReLU (Rectified Linear Unit) :**\n"
        "   • Plage : [0, +∞[\n"
        "   • Utilisée pour : couches cachées\n"
        "   • Avantage : calcul rapide, évite le problème de gradient qui disparaît\n\n"
        "🔹 **Tanh** :\n"
        "   • Plage : [-1, 1]\n"
        "   • Utilisée pour : normalisation centrée\n\n"
        "🔹 **Linéaire** :\n"
        "   • Pas de transformation\n"
        "   • Utilisée pour : régression";
    
    fonctionnement["Qu'est-ce que la rétropropagation ?"] = 
        "La rétropropagation (backpropagation) est l'algorithme d'apprentissage qui permet au réseau d'ajuster ses poids.\n\n"
        "**Principe :**\n"
        "1. **Propagation avant** : Calculer la sortie du réseau\n"
        "2. **Calcul de l'erreur** : Comparer la sortie avec la valeur attendue\n"
        "3. **Propagation arrière** : Propager l'erreur de la sortie vers l'entrée\n"
        "4. **Mise à jour des poids** : Ajuster chaque poids proportionnellement à sa contribution à l'erreur\n\n"
        "**Formule de mise à jour :**\n"
        "Nouveau_poids = Ancien_poids - (Taux_apprentissage × Gradient_erreur)\n\n"
        "**Avantages :**\n"
        "• Efficace pour les réseaux multicouches\n"
        "• Permet d'apprendre des représentations complexes\n"
        "• Calcul automatique des gradients\n\n"
        "**Note :** C'est grâce à la rétropropagation que les réseaux de neurones peuvent apprendre efficacement !";
    
    knowledgeBase_["Fonctionnement"] = fonctionnement;
    
    // Catégorie 3: Architecture
    QMap<QString, QString> architecture;
    architecture["Qu'est-ce qu'une couche dans un réseau de neurones ?"] = 
        "Une couche est un groupe de neurones qui traitent les données en parallèle.\n\n"
        "**Types de couches :**\n\n"
        "🔹 **Couche d'entrée (Input Layer) :**\n"
        "   • Première couche du réseau\n"
        "   • Reçoit les données brutes\n"
        "   • Nombre de neurones = nombre de caractéristiques d'entrée\n"
        "   • Exemple : 2 neurones pour 2 entrées (X, Y)\n\n"
        "🔹 **Couches cachées (Hidden Layers) :**\n"
        "   • Couches intermédiaires entre l'entrée et la sortie\n"
        "   • Effectuent les transformations complexes\n"
        "   • Plus il y a de couches, plus le réseau peut apprendre de patterns complexes\n"
        "   • Exemple : 2 neurones dans une couche cachée\n\n"
        "🔹 **Couche de sortie (Output Layer) :**\n"
        "   • Dernière couche du réseau\n"
        "   • Produit le résultat final\n"
        "   • Nombre de neurones = nombre de sorties attendues\n"
        "   • Exemple : 1 neurone pour une sortie binaire\n\n"
        "**Exemple d'architecture : 2-2-1**\n"
        "   • 2 neurones d'entrée\n"
        "   • 2 neurones dans la couche cachée\n"
        "   • 1 neurone de sortie";
    
    architecture["Comment choisir l'architecture d'un réseau ?"] = 
        "Le choix de l'architecture dépend de votre problème et de vos données.\n\n"
        "**Couche d'entrée :**\n"
        "• Nombre de neurones = nombre de caractéristiques dans vos données\n"
        "• Exemple : 2 entrées (X, Y) → 2 neurones\n\n"
        "**Couches cachées :**\n"
        "• **Profondeur** (nombre de couches) :\n"
        "  - Problèmes simples : 1-2 couches\n"
        "  - Problèmes complexes : 3+ couches (réseaux profonds)\n"
        "• **Largeur** (neurones par couche) :\n"
        "  - Commencez avec 2-3 fois le nombre d'entrées\n"
        "  - Ajustez selon les performances\n"
        "  - Trop de neurones → surapprentissage\n"
        "  - Trop peu → sous-apprentissage\n\n"
        "**Couche de sortie :**\n"
        "• Classification binaire : 1 neurone\n"
        "• Classification multi-classes : nombre de classes\n"
        "• Régression : 1 neurone (ou plusieurs pour plusieurs sorties)\n\n"
        "**Règles générales :**\n"
        "✅ Commencez simple (ex: 2-2-1 pour XOR)\n"
        "✅ Augmentez progressivement si nécessaire\n"
        "✅ Testez différentes architectures\n"
        "✅ Évitez les réseaux trop complexes pour de petits datasets";
    
    architecture["Qu'est-ce qu'un neurone ?"] = 
        "Un neurone est l'unité de base d'un réseau de neurones.\n\n"
        "**Structure d'un neurone :**\n\n"
        "1. **Entrées (Inputs)** :\n"
        "   • Reçoit des valeurs des neurones de la couche précédente\n"
        "   • Chaque entrée a un poids associé\n\n"
        "2. **Calcul de la somme pondérée :**\n"
        "   Somme = (Entrée₁ × Poids₁) + (Entrée₂ × Poids₂) + ... + Biais\n\n"
        "3. **Fonction d'activation :**\n"
        "   Sortie = Activation(Somme)\n"
        "   • Transforme la somme en sortie du neurone\n"
        "   • Exemples : sigmoïde, ReLU, tanh\n\n"
        "4. **Sortie :**\n"
        "   • La valeur calculée est transmise aux neurones de la couche suivante\n\n"
        "**Analogie :**\n"
        "Imaginez un neurone comme un petit processeur qui :\n"
        "• Reçoit des signaux (entrées)\n"
        "• Les pondère selon leur importance (poids)\n"
        "• Les combine et les transforme (fonction d'activation)\n"
        "• Produit un signal de sortie";
    
    knowledgeBase_["Architecture"] = architecture;
    
    // Catégorie 4: Dataset
    QMap<QString, QString> dataset;
    dataset["Qu'est-ce qu'un dataset ?"] = 
        "Un dataset (jeu de données) est une collection d'exemples utilisés pour entraîner et tester le réseau.\n\n"
        "**Composition :**\n"
        "• **Entrées (Features)** : Les données que vous donnez au réseau\n"
        "• **Sorties (Labels/Targets)** : Les résultats attendus\n\n"
        "**Format dans NeuroUIT :**\n"
        "Le dataset doit être au format CSV avec :\n"
        "• Colonnes d'entrées suivies de colonnes de sortie\n"
        "• Exemple : X, Y, Résultat\n"
        "• Chaque ligne = un échantillon d'entraînement\n\n"
        "**Exemple de dataset XOR :**\n"
        "0, 0, 0\n"
        "0, 1, 1\n"
        "1, 0, 1\n"
        "1, 1, 0\n\n"
        "Ici : 2 entrées (X, Y) et 1 sortie (Résultat)\n\n"
        "**Types de datasets :**\n"
        "• **Classification** : Prédire une catégorie (ex: 0 ou 1)\n"
        "• **Régression** : Prédire une valeur numérique continue";
    
    dataset["Comment préparer un dataset ?"] = 
        "La préparation du dataset est cruciale pour un bon apprentissage.\n\n"
        "**Étapes de préparation :**\n\n"
        "1. **Collecte des données :**\n"
        "   • Rassemblez suffisamment d'exemples\n"
        "   • Assurez-vous que les données sont représentatives\n\n"
        "2. **Format CSV :**\n"
        "   • Format : Entrée1, Entrée2, ..., Sortie1, Sortie2, ...\n"
        "   • Pas d'en-tête (ou cochez 'Avec en-tête' si présent)\n"
        "   • Séparateur : virgule\n\n"
        "3. **Normalisation (optionnel mais recommandé) :**\n"
        "   • Mettez les valeurs sur une échelle similaire\n"
        "   • Exemple : [0, 1] ou [-1, 1]\n"
        "   • Améliore la convergence de l'apprentissage\n\n"
        "4. **Division des données :**\n"
        "   • Entraînement : 70-80% des données\n"
        "   • Test : 20-30% des données\n\n"
        "**Conseils :**\n"
        "✅ Plus de données = généralement meilleur\n"
        "✅ Évitez les données bruitées ou erronées\n"
        "✅ Assurez-vous que les entrées et sorties correspondent";
    
    dataset["Quels datasets sont fournis avec NeuroUIT ?"] = 
        "NeuroUIT inclut plusieurs datasets d'exemple pour vous aider à démarrer :\n\n"
        "**Datasets de classification :**\n"
        "• **XOR_dataset.csv** : Porte logique XOR (2 entrées, 1 sortie)\n"
        "• **AND_dataset.csv** : Porte logique AND\n"
        "• **OR_dataset.csv** : Porte logique OR\n"
        "• **binary_classification.csv** : Classification binaire générale\n\n"
        "**Datasets de régression :**\n"
        "• **linear_regression.csv** : Régression linéaire simple\n"
        "• **sine_wave.csv** : Approximation de fonction sinusoïdale\n\n"
        "**Recommandations :**\n"
        "🎯 **Pour débuter** : Commencez avec XOR_dataset.csv\n"
        "   • Architecture recommandée : 2-2-1\n"
        "   • Simple à comprendre et visualiser\n\n"
        "🎯 **Pour tester** : Essayez binary_classification.csv\n"
        "   • Plus complexe que XOR\n"
        "   • Bon pour tester différentes architectures";
    
    knowledgeBase_["Dataset"] = dataset;
    
    // Catégorie 5: Entraînement
    QMap<QString, QString> entrainement;
    entrainement["Qu'est-ce que l'entraînement d'un réseau ?"] = 
        "L'entraînement est le processus par lequel le réseau apprend à résoudre un problème.\n\n"
        "**Processus d'entraînement :**\n\n"
        "1. **Initialisation :**\n"
        "   • Les poids sont initialisés aléatoirement (petites valeurs)\n"
        "   • Les biais sont généralement initialisés à 0\n\n"
        "2. **Itération sur les échantillons :**\n"
        "   Pour chaque échantillon du dataset :\n"
        "   a) Propagation avant : calculer la sortie\n"
        "   b) Calculer l'erreur\n"
        "   c) Rétropropagation : ajuster les poids\n\n"
        "3. **Époques :**\n"
        "   • Une époque = un passage complet sur tout le dataset\n"
        "   • Le réseau s'améliore à chaque époque\n"
        "   • Généralement, plusieurs époques sont nécessaires\n\n"
        "4. **Arrêt :**\n"
        "   • Quand l'erreur est suffisamment faible\n"
        "   • Ou après un nombre d'époques défini\n"
        "   • Ou si l'erreur ne diminue plus (convergence)\n\n"
        "**Objectif :**\n"
        "Trouver les poids optimaux qui minimisent l'erreur entre les prédictions et les valeurs réelles.";
    
    entrainement["Qu'est-ce qu'une époque (epoch) ?"] = 
        "Une époque (epoch) est un cycle complet d'entraînement sur tout le dataset.\n\n"
        "**Définition :**\n"
        "• Le réseau voit tous les échantillons d'entraînement une fois\n"
        "• Les poids sont mis à jour pour chaque échantillon\n"
        "• L'erreur moyenne est calculée à la fin de l'époque\n\n"
        "**Exemple :**\n"
        "Si vous avez 100 échantillons et 50 époques :\n"
        "• Le réseau verra chaque échantillon 50 fois\n"
        "• Total : 5000 itérations d'apprentissage\n\n"
        "**Nombre d'époques :**\n"
        "• **Trop peu** : Le réseau n'apprend pas suffisamment\n"
        "• **Trop beaucoup** : Risque de surapprentissage (overfitting)\n"
        "• **Recommandation** : Commencez avec 100-500 époques\n\n"
        "**Observation :**\n"
        "Regardez la courbe d'erreur :\n"
        "• Si elle diminue encore → continuez\n"
        "• Si elle stagne → arrêtez ou ajustez les paramètres";
    
    entrainement["Qu'est-ce que le surapprentissage (overfitting) ?"] = 
        "Le surapprentissage se produit quand le réseau mémorise les données d'entraînement au lieu d'apprendre à généraliser.\n\n"
        "**Symptômes :**\n"
        "• Erreur d'entraînement très faible\n"
        "• Erreur de test élevée\n"
        "• Le réseau fonctionne bien sur les données vues, mal sur les nouvelles\n\n"
        "**Causes :**\n"
        "• Réseau trop complexe pour la quantité de données\n"
        "• Trop d'époques d'entraînement\n"
        "• Dataset trop petit\n\n"
        "**Solutions :**\n"
        "✅ Réduire la complexité du réseau (moins de neurones/couches)\n"
        "✅ Augmenter la taille du dataset\n"
        "✅ Arrêter l'entraînement plus tôt (early stopping)\n"
        "✅ Utiliser la régularisation\n"
        "✅ Augmenter le batch size\n\n"
        "**Comment détecter :**\n"
        "Comparez l'erreur d'entraînement et l'erreur de test. Si l'écart est grand, c'est probablement du surapprentissage.";
    
    knowledgeBase_["Entraînement"] = entrainement;
    
    // Catégorie 6: Paramètres
    QMap<QString, QString> parametres;
    parametres["Qu'est-ce que le taux d'apprentissage (learning rate) ?"] = 
        "Le taux d'apprentissage contrôle la vitesse à laquelle le réseau apprend.\n\n"
        "**Définition :**\n"
        "C'est un facteur qui détermine l'amplitude des ajustements des poids à chaque étape d'apprentissage.\n\n"
        "**Valeurs typiques :**\n"
        "• **Petit (0.001 - 0.01)** : Apprentissage lent mais stable\n"
        "• **Moyen (0.01 - 0.1)** : Bon compromis (recommandé pour débuter)\n"
        "• **Grand (> 0.1)** : Apprentissage rapide mais peut être instable\n\n"
        "**Effets :**\n\n"
        "🔹 **Taux trop petit :**\n"
        "   • Apprentissage très lent\n"
        "   • Peut rester bloqué dans un minimum local\n"
        "   • Nécessite beaucoup d'époques\n\n"
        "🔹 **Taux trop grand :**\n"
        "   • Apprentissage instable\n"
        "   • L'erreur peut osciller ou augmenter\n"
        "   • Peut ne pas converger\n\n"
        "🔹 **Taux optimal :**\n"
        "   • L'erreur diminue régulièrement\n"
        "   • Convergence stable\n"
        "   • Bon équilibre vitesse/stabilité\n\n"
        "**Recommandation :**\n"
        "Commencez avec 0.01 et ajustez selon les résultats. Observez la courbe d'erreur pour trouver le bon taux.";
    
    parametres["Qu'est-ce que le batch size ?"] = 
        "Le batch size est le nombre d'échantillons traités avant de mettre à jour les poids.\n\n"
        "**Modes d'entraînement :**\n\n"
        "🔹 **Batch size = 1 (Online Learning) :**\n"
        "   • Mise à jour après chaque échantillon\n"
        "   • Plus de mises à jour, apprentissage plus rapide\n"
        "   • Peut être plus instable\n"
        "   • Bon pour les petits datasets\n\n"
        "🔹 **Batch size = N (Mini-batch) :**\n"
        "   • Mise à jour après N échantillons\n"
        "   • Plus stable, moyenne des gradients\n"
        "   • Bon compromis\n"
        "   • Recommandé pour la plupart des cas\n\n"
        "🔹 **Batch size = Taille du dataset (Full batch) :**\n"
        "   • Mise à jour après avoir vu tout le dataset\n"
        "   • Très stable mais lent\n"
        "   • Nécessite beaucoup de mémoire\n\n"
        "**Recommandation :**\n"
        "Pour débuter, utilisez batch size = 1 (comme dans les exemples XOR). "
        "Pour des datasets plus grands, essayez 8, 16, ou 32.";
    
    parametres["Qu'est-ce que le momentum ?"] = 
        "Le momentum aide le réseau à converger plus rapidement en conservant une partie de la direction précédente.\n\n"
        "**Principe :**\n"
        "Au lieu de se déplacer uniquement selon le gradient actuel, le réseau conserve une \"inertie\" des mises à jour précédentes.\n\n"
        "**Avantages :**\n"
        "✅ Convergence plus rapide\n"
        "✅ Aide à échapper aux minima locaux\n"
        "✅ Réduit les oscillations\n"
        "✅ Améliore la stabilité de l'apprentissage\n\n"
        "**Valeurs typiques :**\n"
        "• **0.0** : Pas de momentum (désactivé)\n"
        "• **0.5 - 0.9** : Momentum modéré à fort\n"
        "• **0.9** : Valeur couramment utilisée\n\n"
        "**Quand l'utiliser :**\n"
        "• Pour accélérer l'apprentissage\n"
        "• Quand l'apprentissage oscille\n"
        "• Pour des problèmes complexes\n\n"
        "**Note :**\n"
        "Pour débuter, vous pouvez laisser le momentum à 0. Activez-le si l'apprentissage est trop lent ou instable.";
    
    parametres["Qu'est-ce que le mélange (shuffle) ?"] = 
        "Le mélange (shuffle) réorganise aléatoirement l'ordre des échantillons à chaque époque.\n\n"
        "**Pourquoi c'est important :**\n\n"
        "✅ **Évite le biais d'ordre :**\n"
        "   • Sans shuffle, le réseau peut apprendre l'ordre des données plutôt que les patterns\n"
        "   • Le mélange force le réseau à apprendre les vraies relations\n\n"
        "✅ **Améliore la généralisation :**\n"
        "   • Le réseau voit les données dans différents contextes\n"
        "   • Meilleure capacité à généraliser\n\n"
        "✅ **Convergence plus stable :**\n"
        "   • Réduit les oscillations dans l'apprentissage\n"
        "   • Courbe d'erreur plus lisse\n\n"
        "**Recommandation :**\n"
        "Activez toujours le shuffle (Oui) sauf si vous avez une raison spécifique de le désactiver. "
        "C'est une bonne pratique standard en apprentissage automatique.";
    
    knowledgeBase_["Paramètres"] = parametres;
    
    // Catégorie 7: Métriques
    QMap<QString, QString> metriques;
    metriques["Quelles métriques sont utilisées pour évaluer un réseau ?"] = 
        "Plusieurs métriques permettent d'évaluer la performance d'un réseau de neurones.\n\n"
        "**Pour la Classification :**\n\n"
        "🔹 **Précision (Accuracy) :**\n"
        "   • Pourcentage de prédictions correctes\n"
        "   • Formule : (Prédictions correctes) / (Total)\n"
        "   • Exemple : 90% = 90 prédictions correctes sur 100\n\n"
        "🔹 **Précision (Precision) :**\n"
        "   • Pour les prédictions positives, combien sont vraiment positives\n"
        "   • Formule : Vrais Positifs / (Vrais Positifs + Faux Positifs)\n\n"
        "🔹 **Rappel (Recall) :**\n"
        "   • Parmi les vrais positifs, combien sont détectés\n"
        "   • Formule : Vrais Positifs / (Vrais Positifs + Faux Négatifs)\n\n"
        "🔹 **Score F1 :**\n"
        "   • Moyenne harmonique de précision et rappel\n"
        "   • Bonne mesure d'équilibre\n"
        "   • Formule : 2 × (Précision × Rappel) / (Précision + Rappel)\n\n"
        "**Pour la Régression :**\n\n"
        "🔹 **MSE (Erreur Quadratique Moyenne) :**\n"
        "   • Mesure l'erreur moyenne au carré\n"
        "   • Plus petit = mieux\n\n"
        "🔹 **MAE (Erreur Absolue Moyenne) :**\n"
        "   • Erreur moyenne en valeur absolue\n"
        "   • Plus facile à interpréter que MSE\n\n"
        "🔹 **R² (Coefficient de Détermination) :**\n"
        "   • Mesure la qualité de l'ajustement\n"
        "   • Plage : 0 à 1 (1 = parfait)";
    
    metriques["Comment interpréter la courbe d'erreur ?"] = 
        "La courbe d'erreur montre l'évolution de l'erreur pendant l'entraînement.\n\n"
        "**Courbes typiques :**\n\n"
        "📉 **Courbe décroissante régulière :**\n"
        "   • ✅ Bon signe ! Le réseau apprend correctement\n"
        "   • L'erreur diminue progressivement\n"
        "   • Continuez l'entraînement\n\n"
        "📊 **Courbe qui stagne :**\n"
        "   • Le réseau a atteint sa limite\n"
        "   • Solutions : augmenter le taux d'apprentissage, changer l'architecture, ou arrêter\n\n"
        "📈 **Courbe qui augmente :**\n"
        "   • ⚠️ Problème ! Taux d'apprentissage trop élevé\n"
        "   • Réduisez le taux d'apprentissage\n\n"
        "🌊 **Courbe oscillante :**\n"
        "   • Taux d'apprentissage trop élevé ou batch size trop petit\n"
        "   • Réduisez le taux d'apprentissage ou augmentez le batch size\n\n"
        "**Objectif :**\n"
        "Une courbe qui descend régulièrement vers une valeur faible et stable indique un bon apprentissage.";
    
    metriques["Qu'est-ce qu'une matrice de confusion ?"] = 
        "La matrice de confusion est un tableau qui montre la performance d'un modèle de classification.\n\n"
        "**Structure :**\n"
        "Prédit / Réel     Classe 0    Classe 1\n"
        "Classe 0          VN          FP\n"
        "Classe 1          FN          VP\n\n"
        "**Terminologie :**\n\n"
        "🔹 **VP (Vrais Positifs)** : Correctement prédit comme positif\n"
        "🔹 **VN (Vrais Négatifs)** : Correctement prédit comme négatif\n"
        "🔹 **FP (Faux Positifs)** : Incorrectement prédit comme positif\n"
        "🔹 **FN (Faux Négatifs)** : Incorrectement prédit comme négatif\n\n"
        "**Interprétation :**\n"
        "• **Diagonale principale** : Prédictions correctes\n"
        "• **Hors diagonale** : Erreurs de classification\n\n"
        "**Exemple :**\n"
        "Si vous avez 100 échantillons :\n"
        "• 80 VP + 15 VN = 95 corrects\n"
        "• 3 FP + 2 FN = 5 erreurs\n"
        "• Précision = 95%\n\n"
        "**Utilité :**\n"
        "Permet d'identifier quels types d'erreurs le modèle fait le plus souvent.";
    
    knowledgeBase_["Métriques"] = metriques;
    
    // Catégorie 8: Conseils
    QMap<QString, QString> conseils;
    conseils["Comment bien débuter avec NeuroUIT ?"] = 
        "Voici un guide pas à pas pour bien commencer :\n\n"
        "**Étape 1 : Créer un réseau simple**\n"
        "   • Cliquez sur 'Nouveau réseau'\n"
        "   • Architecture recommandée : 2-2-1\n"
        "   • Fonction d'activation : Sigmoïde pour les deux couches\n\n"
        "**Étape 2 : Charger un dataset d'exemple**\n"
        "   • Cliquez sur 'Charger dataset'\n"
        "   • Sélectionnez 'XOR_dataset.csv'\n"
        "   • Configurez : 2 entrées, 1 sortie, pas d'en-tête\n\n"
        "**Étape 3 : Configurer l'entraînement**\n"
        "   • Taux d'apprentissage : 0.01\n"
        "   • Époques : 100\n"
        "   • Batch size : 1\n"
        "   • Momentum : 0\n"
        "   • Mélanger : Oui\n\n"
        "**Étape 4 : Lancer l'entraînement**\n"
        "   • Cliquez sur 'Lancer'\n"
        "   • Observez la courbe d'erreur qui diminue\n"
        "   • Attendez la fin de l'entraînement\n\n"
        "**Étape 5 : Tester le réseau**\n"
        "   • Cliquez sur 'Tester'\n"
        "   • Consultez les métriques et résultats\n"
        "   • Vérifiez la matrice de confusion\n\n"
        "**Conseils :**\n"
        "✅ Commencez simple, complexifiez progressivement\n"
        "✅ Observez toujours la courbe d'erreur\n"
        "✅ Testez différentes configurations\n"
        "✅ Utilisez l'assistant IA pour comprendre les concepts";
    
    conseils["Quels sont les problèmes courants et leurs solutions ?"] = 
        "Voici les problèmes fréquents et comment les résoudre :\n\n"
        "**Problème 1 : L'erreur ne diminue pas**\n"
        "🔧 Solutions :\n"
        "   • Augmentez le taux d'apprentissage (essayez 0.1)\n"
        "   • Vérifiez que le dataset est correct\n"
        "   • Augmentez le nombre d'époques\n"
        "   • Vérifiez l'architecture (assez de neurones ?)\n\n"
        "**Problème 2 : L'erreur oscille**\n"
        "🔧 Solutions :\n"
        "   • Réduisez le taux d'apprentissage\n"
        "   • Augmentez le batch size\n"
        "   • Activez le momentum (0.5-0.9)\n\n"
        "**Problème 3 : Précision faible**\n"
        "🔧 Solutions :\n"
        "   • Augmentez le nombre de neurones/couches\n"
        "   • Entraînez plus longtemps\n"
        "   • Vérifiez la qualité du dataset\n"
        "   • Essayez différentes fonctions d'activation\n\n"
        "**Problème 4 : Surapprentissage**\n"
        "🔧 Solutions :\n"
        "   • Réduisez la complexité du réseau\n"
        "   • Augmentez la taille du dataset\n"
        "   • Arrêtez l'entraînement plus tôt\n\n"
        "**Problème 5 : Le réseau ne converge pas**\n"
        "🔧 Solutions :\n"
        "   • Normalisez les données d'entrée\n"
        "   • Réinitialisez les poids (recréez le réseau)\n"
        "   • Vérifiez que le problème est bien formulé";
    
    conseils["Quelles sont les bonnes pratiques ?"] = 
        "Voici les meilleures pratiques pour utiliser NeuroUIT efficacement :\n\n"
        "**1. Commencez simple**\n"
        "   ✅ Utilisez des architectures simples au début\n"
        "   ✅ Testez avec des datasets d'exemple\n"
        "   ✅ Comprenez les bases avant de complexifier\n\n"
        "**2. Observez les métriques**\n"
        "   ✅ Surveillez la courbe d'erreur pendant l'entraînement\n"
        "   ✅ Analysez les métriques après le test\n"
        "   ✅ Utilisez la matrice de confusion pour comprendre les erreurs\n\n"
        "**3. Expérimentez**\n"
        "   ✅ Testez différentes architectures\n"
        "   ✅ Variez les paramètres d'entraînement\n"
        "   ✅ Comparez les résultats\n\n"
        "**4. Préparation des données**\n"
        "   ✅ Normalisez vos données si nécessaire\n"
        "   ✅ Vérifiez la qualité du dataset\n"
        "   ✅ Assurez-vous que le format CSV est correct\n\n"
        "**5. Documentation**\n"
        "   ✅ Utilisez l'assistant IA pour comprendre les concepts\n"
        "   ✅ Consultez les exemples de datasets fournis\n"
        "   ✅ Lisez les messages d'erreur pour déboguer\n\n"
        "**6. Itération**\n"
        "   ✅ Améliorez progressivement\n"
        "   ✅ Documentez vos expériences\n"
        "   ✅ Apprenez de chaque tentative";
    
    knowledgeBase_["Conseils"] = conseils;
    
    // Remplir la liste des catégories
    categoryList_->addItems(categories_);
    categoryList_->setCurrentRow(0);
}

void AIAssistantDialog::displayWelcomeMessage() {
    QString welcome = 
        "🧙 Bienvenue dans l'Assistant IA de NeuroUIT !\n\n"
        "Je suis là pour vous aider à comprendre les réseaux de neurones et à utiliser cette application efficacement.\n\n"
        "📚 **Comment utiliser cet assistant :**\n"
        "1. Sélectionnez une catégorie dans la liste de gauche\n"
        "2. Choisissez une question qui vous intéresse\n"
        "3. Lisez la réponse détaillée à droite\n\n"
        "💡 **Conseil :** Commencez par la catégorie 'Introduction' si vous êtes nouveau dans le domaine des réseaux de neurones.\n\n"
        "N'hésitez pas à explorer toutes les catégories pour une compréhension complète !";
    
    answerDisplay_->setText(welcome);
    answerDisplay_->setStyleSheet(
        "QTextEdit { "
        "border: 2px solid #2196F3; "
        "border-radius: 5px; "
        "background-color: #E3F2FD; "
        "padding: 15px; "
        "font-size: 11pt; "
        "line-height: 1.6; "
        "}"
    );
}

void AIAssistantDialog::onCategoryChanged(int index) {
    if (index < 0 || index >= categories_.size()) return;
    
    QString category = categories_[index];
    questionList_->clear();
    
    if (knowledgeBase_.contains(category)) {
        const QMap<QString, QString>& questions = knowledgeBase_[category];
        QStringList questionList = questions.keys();
        questionList_->addItems(questionList);
    }
    
    // Réafficher le message de bienvenue
    if (index == 0) {
        displayWelcomeMessage();
    } else {
        answerDisplay_->setText("Sélectionnez une question dans la liste pour voir la réponse détaillée.");
        answerDisplay_->setStyleSheet(
            "QTextEdit { "
            "border: 2px solid #BDBDBD; "
            "border-radius: 5px; "
            "background-color: #FFFFFF; "
            "padding: 15px; "
            "font-size: 11pt; "
            "line-height: 1.6; "
            "}"
        );
    }
}

void AIAssistantDialog::onQuestionSelected() {
    QListWidgetItem* item = questionList_->currentItem();
    if (!item) return;
    
    QString question = item->text();
    int categoryIndex = categoryList_->currentRow();
    
    if (categoryIndex < 0 || categoryIndex >= categories_.size()) return;
    
    QString category = categories_[categoryIndex];
    
    if (knowledgeBase_.contains(category) && knowledgeBase_[category].contains(question)) {
        QString answer = knowledgeBase_[category][question];
        displayAnswer(question, answer);
    }
}

void AIAssistantDialog::displayAnswer(const QString& question, const QString& answer) {
    QString formattedText = answer;
    
    // Convertir les marqueurs **texte** en <b>texte</b> de manière simple
    int startPos = 0;
    while ((startPos = formattedText.indexOf("**", startPos)) != -1) {
        int endPos = formattedText.indexOf("**", startPos + 2);
        if (endPos != -1) {
            QString boldText = formattedText.mid(startPos + 2, endPos - startPos - 2);
            formattedText.replace(startPos, endPos - startPos + 2, "<b>" + boldText + "</b>");
            startPos += boldText.length() + 7; // Longueur de <b></b>
        } else {
            break;
        }
    }
    
    // Convertir les sauts de ligne
    formattedText.replace("\n\n", "<br><br>");
    formattedText.replace("\n", "<br>");
    
    // Encapsuler dans HTML
    QString html = QString(
        "<div style='margin-bottom: 15px;'>"
        "<h2 style='color: #2196F3; margin-bottom: 10px;'>%1</h2>"
        "</div>"
        "<div style='line-height: 1.8; color: #424242;'>"
        "%2"
        "</div>"
    ).arg(question.toHtmlEscaped(), formattedText);
    
    answerDisplay_->setHtml(html);
    answerDisplay_->setStyleSheet(
        "QTextEdit { "
        "border: 2px solid #4CAF50; "
        "border-radius: 5px; "
        "background-color: #FFFFFF; "
        "padding: 15px; "
        "font-size: 11pt; "
        "line-height: 1.6; "
        "}"
    );
}

