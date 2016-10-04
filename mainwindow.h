#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <map>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    std::map<std::string, QAction*> actions;
    std::vector<QMenu *> menus;
private slots:
    //void newProject();
    //void openProject();
    //void saveProject();
    //void saveProjectAs();
    //void openPreferences();
    //void quitApp();

    //void undo();
    //void redo();
    //void cut();
    //void copy();
    //void paste();

    //void selectAll();
    //void selectNone();

    //void buildProject();

    //void about();
    //void documentation();
    //void tips();

};

#endif // MAINWINDOW_H
