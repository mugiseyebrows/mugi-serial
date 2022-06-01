#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QSerialPort;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void updateButtons();
protected slots:
    void onReadyRead();

    void on_open_clicked();

    void on_close_clicked();

private slots:
    void on_clean_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort* m_port = nullptr;
};
#endif // MAINWINDOW_H
