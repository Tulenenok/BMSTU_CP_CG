//
// Created by Nataliia Gurova on 26.11.2022.
//

#ifndef C_VERSION_MAINWINDOW_H
#define C_VERSION_MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "../connect/handle_buttons.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void fillScreen(int **screen_matrix);

private slots:
    void on_LoadButton_clicked();
    void on_DrawButton_clicked();
    void on_AddLightButton_clicked();

private:
    Ui::MainWindow *ui;

    QImage DataToQImage(int width, int height, int length, char *data);
};


#endif //C_VERSION_MAINWINDOW_H
