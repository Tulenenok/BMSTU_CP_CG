//
// Created by Nataliia Gurova on 26.11.2022.
//

#ifndef C_VERSION_MAINWINDOW_H
#define C_VERSION_MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "../connect/handle_buttons.h"
#include "../server/screen_t.h"
#include "../server/triangle_t.h"
#include "../server/light_source.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void fillScreen();

private slots:
    void on_LoadButton_clicked();
    void on_DrawButton_clicked();
    void on_AddLightButton_clicked();

private:
    Ui::MainWindow *ui;

    screen_t *screen_matrix;
    std::vector<triangle_t*> polygons;
    std::vector<light_source_t*> light_sources;
};


#endif //C_VERSION_MAINWINDOW_H
