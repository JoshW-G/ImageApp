#include "brightdialog.h"
#include "ui_brightdialog.h"

brightDialog::brightDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::brightDialog)
{
    ui->setupUi(this);
    ui->contSlider->setRange(0,101);
    ui->contSlider->setSingleStep(1);
    ui->brightSlider->setRange(-100,101);
    ui->brightSlider->setSingleStep(1);
    ui->contSlider->setSingleStep(1);
    ui->brightSlider->setTickPosition(QSlider::TickPosition());
    ui->contSpinBox->setRange(0.01,3.0);
    ui->brightSpinBox->setRange(-100,100);
    ui->contSpinBox->setSingleStep(0.01);
}

brightDialog::~brightDialog()
{
    delete ui;
}

int brightDialog::getBright() const
{
    return ui->brightSpinBox->value();
}

double brightDialog::getCont() const
{
    return ui->contSpinBox->value();
}





void brightDialog::on_okButton_clicked()
{
    accept();
}

void brightDialog::on_cancelButton_clicked()
{
    reject();
}

void brightDialog::on_contSlider_valueChanged(int value)
{
    double cont = (double)value/(100.0/3.0);
    ui->contSpinBox->setValue(cont);
}

void brightDialog::on_brightSlider_valueChanged(int value)
{
    ui->brightSpinBox->setValue(value);
}

void brightDialog::on_contSpinBox_valueChanged(double value)
{
    int cont = value *  (100.0/3.0);
    ui->contSlider->setValue(cont);
}

void brightDialog::on_brightSpinBox_valueChanged(int value)
{
    ui->brightSlider->setValue(value);
}
