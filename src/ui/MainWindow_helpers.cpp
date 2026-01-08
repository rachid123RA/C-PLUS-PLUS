// Fonctions helper pour MainWindow
#include "ui/MainWindow.h"
#include "ui/AIAssistantDialog.h"
#include <QMessageBox>
#include <QTimer>
#include <QApplication>

void MainWindow::applyTheme(bool darkMode) {
    darkMode_ = darkMode;
    
    if (darkMode) {
        // Mode sombre
        setStyleSheet(
            "QMainWindow { background-color: #1e1e1e; color: #ffffff; }"
            "QWidget { background-color: #1e1e1e; color: #ffffff; }"
            "QPushButton { background-color: #2d2d2d; color: #ffffff; border: 1px solid #404040; border-radius: 5px; padding: 5px; }"
            "QPushButton:hover { background-color: #3d3d3d; }"
            "QPushButton:pressed { background-color: #2d2d2d; }"
            "QPushButton:disabled { background-color: #1a1a1a; color: #666666; }"
            "QGroupBox { border: 1px solid #404040; border-radius: 5px; margin-top: 10px; padding-top: 10px; }"
            "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px; }"
            "QTextEdit, QPlainTextEdit { background-color: #252525; color: #ffffff; border: 1px solid #404040; border-radius: 3px; }"
            "QTabWidget::pane { border: 1px solid #404040; background-color: #252525; }"
            "QTabBar::tab { background-color: #2d2d2d; color: #ffffff; padding: 8px 20px; border: 1px solid #404040; }"
            "QTabBar::tab:selected { background-color: #0078d4; }"
            "QTabBar::tab:hover { background-color: #3d3d3d; }"
            "QLabel { color: #ffffff; }"
            "QStatusBar { background-color: #0078d4; color: #ffffff; }"
            "QProgressBar { border: 1px solid #404040; border-radius: 3px; background-color: #252525; text-align: center; }"
            "QProgressBar::chunk { background-color: #0078d4; }"
            "QMenuBar { background-color: #1e1e1e; color: #ffffff; }"
            "QMenuBar::item:selected { background-color: #0078d4; }"
            "QMenu { background-color: #2d2d2d; color: #ffffff; border: 1px solid #404040; }"
            "QMenu::item:selected { background-color: #0078d4; }"
            "QToolBar { background-color: #252525; border: none; }"
        );
    } else {
        // Mode clair
        setStyleSheet(
            "QMainWindow { background-color: #f5f5f5; }"
            "QPushButton { background-color: #ffffff; border: 1px solid #cccccc; border-radius: 5px; padding: 5px; }"
            "QPushButton:hover { background-color: #e8e8e8; }"
            "QPushButton:pressed { background-color: #d0d0d0; }"
            "QGroupBox { border: 1px solid #cccccc; border-radius: 5px; margin-top: 10px; padding-top: 10px; }"
            "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px; }"
            "QTextEdit, QPlainTextEdit { background-color: #ffffff; border: 1px solid #cccccc; border-radius: 3px; }"
            "QTabWidget::pane { border: 1px solid #cccccc; background-color: #ffffff; }"
            "QTabBar::tab { background-color: #e8e8e8; padding: 8px 20px; border: 1px solid #cccccc; }"
            "QTabBar::tab:selected { background-color: #2196F3; color: white; }"
            "QTabBar::tab:hover { background-color: #f0f0f0; }"
            "QStatusBar { background-color: #2196F3; color: white; }"
            "QProgressBar { border: 1px solid #cccccc; border-radius: 3px; background-color: #ffffff; text-align: center; }"
            "QProgressBar::chunk { background-color: #2196F3; }"
        );
    }
}

void MainWindow::showNotification(const QString& message, bool isError) {
    QMessageBox msgBox(this);
    msgBox.setText(message);
    msgBox.setIcon(isError ? QMessageBox::Warning : QMessageBox::Information);
    msgBox.setWindowTitle(isError ? "Erreur" : "Information");
    msgBox.exec();
}

void MainWindow::onThemeChanged() {
    // Cette fonction est appelée depuis le menu
    // Le thème est déjà changé via les actions connectées
}

void MainWindow::onShowWizard() {
    // Ouvrir le dialogue d'assistant IA interactif
    AIAssistantDialog dialog(this);
    dialog.exec();
}

void MainWindow::onToggleFullScreen() {
    if (isFullScreen()) {
        showNormal();
    } else {
        showFullScreen();
    }
}

