#ifndef NETWORKVISUALIZER_H
#define NETWORKVISUALIZER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPoint>
#include <memory>

namespace NeuroUIT {
    class Network;
}

/**
 * @brief Widget pour visualiser graphiquement un réseau de neurones
 */
class NetworkVisualizer : public QWidget {
    Q_OBJECT

public:
    explicit NetworkVisualizer(QWidget *parent = nullptr);
    
    /**
     * @brief Met à jour le réseau à visualiser
     */
    void updateNetwork(std::shared_ptr<NeuroUIT::Network> network);
    
    /**
     * @brief Augmente le facteur de zoom
     */
    void zoomIn();
    
    /**
     * @brief Diminue le facteur de zoom
     */
    void zoomOut();
    
    /**
     * @brief Réinitialise le zoom à la valeur par défaut
     */
    void resetZoom();

public slots:
    void onZoomIn();
    void onZoomOut();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void drawNetwork(QPainter& painter);
    
    std::shared_ptr<NeuroUIT::Network> network_;
    
    // Paramètres de visualisation de base
    static constexpr int BASE_NODE_RADIUS = 15;
    static constexpr int BASE_LAYER_SPACING = 200;
    static constexpr int BASE_NODE_SPACING = 40;
    
    // Facteur de zoom (1.0 = taille normale)
    double zoomFactor_;
    
    // Calculer les paramètres de visualisation basés sur le zoom
    int getNodeRadius() const { return static_cast<int>(BASE_NODE_RADIUS * zoomFactor_); }
    int getLayerSpacing() const { return static_cast<int>(BASE_LAYER_SPACING * zoomFactor_); }
    int getNodeSpacing() const { return static_cast<int>(BASE_NODE_SPACING * zoomFactor_); }
};

#endif // NETWORKVISUALIZER_H

