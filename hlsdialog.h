#ifndef HLSDIALOG_H
#define HLSDIALOG_H

#include <QDialog>

namespace Ui {
class HLSDialog;
}

class HLSDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HLSDialog(QWidget *parent = nullptr);
    ~HLSDialog();

    int getHue() const;
    int getSat() const;
    int getLight() const;


private slots:
    void on_okButton_clicked();

    void on_hueSlider_valueChanged(int value);

    void on_satSlider_valueChanged(int value);

    void on_lightSlider_valueChanged(int value);

    void on_hueSpinBox_valueChanged(int arg1);

    void on_satSpinBox_valueChanged(int arg1);

    void on_lightSpinBox_valueChanged(int arg1);

    void on_cancelButton_clicked();

private:
    Ui::HLSDialog *ui;
};

#endif // HLSDIALOG_H
