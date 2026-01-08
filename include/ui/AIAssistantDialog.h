#ifndef AIASSISTANTDIALOG_H
#define AIASSISTANTDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QGroupBox>
#include <QMap>
#include <QString>

/**
 * @brief Dialogue interactif d'assistant IA pour expliquer les réseaux de neurones
 */
class AIAssistantDialog : public QDialog {
    Q_OBJECT

public:
    explicit AIAssistantDialog(QWidget *parent = nullptr);
    ~AIAssistantDialog();

private slots:
    void onQuestionSelected();
    void onCategoryChanged(int index);

private:
    void setupUI();
    void initializeKnowledgeBase();
    void displayWelcomeMessage();
    void displayAnswer(const QString& question, const QString& answer);
    
    // UI Components
    QVBoxLayout* mainLayout_;
    QHBoxLayout* contentLayout_;
    
    QLabel* welcomeLabel_;
    QTextEdit* answerDisplay_;
    QListWidget* questionList_;
    QListWidget* categoryList_;
    
    QPushButton* closeButton_;
    
    // Base de connaissances
    QMap<QString, QMap<QString, QString>> knowledgeBase_; // Catégorie -> (Question -> Réponse)
    QStringList categories_;
};

#endif // AIASSISTANTDIALOG_H

