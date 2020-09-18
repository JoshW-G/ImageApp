#ifndef BRIGHTDIALOG_H
#define BRIGHTDIALOG_H

#include <QDialog>

namespace Ui {
class brightDialog;
}

class brightDialog : public QDialog
{
    Q_OBJECT

public:
    explicit brightDialog(QWidget *parent = nullptr);
    ~brightDialog();

    int getBright() const;
    double getCont() const;
private slots:

    void on_okButton_clicked();

    void on_cancelButton_clicked();

    void on_contSlider_valueChanged(int value);

    void on_brightSlider_valueChanged(int value);

    void on_contSpinBox_valueChanged(double arg1);

    void on_brightSpinBox_valueChanged(int arg1);

private:
    Ui::brightDialog *ui;
};

#endif // BRIGHTDIALOG_H
