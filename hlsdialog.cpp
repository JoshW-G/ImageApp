#include "hlsdialog.h"
#include "ui_hlsdialog.h"

HLSDialog::HLSDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HLSDialog)
{
    ui->setupUi(this);
    ui->hueSlider->setRange(0,180);
    ui->hueSlider->setSingleStep(1);
    ui->satSlider->setRange(0,100);
    ui->satSlider->setSingleStep(1);
    ui->lightSlider->setRange(0,100);
    ui->lightSlider->setSingleStep(1);

    ui->hueSpinBox->setRange(0,180);
    ui->satSpinBox->setRange(0,100);
    ui->lightSpinBox->setRange(0,100);

}
HLSDialog::~HLSDialog()
{
    delete ui;
}

int HLSDialog::getHue() const{
    return  ui->hueSpinBox->value();
}

int HLSDialog::getSat() const
{
    return  ui->satSpinBox->value();
}

int HLSDialog::getLight() const
{
    return  ui->lightSpinBox->value();
}


void HLSDialog::on_okButton_clicked()
{
    accept();
}
void HLSDialog::on_cancelButton_clicked()
{
    reject();
}
void HLSDialog::on_hueSlider_valueChanged(int value)
{
    ui->hueSpinBox->setValue(value);
}

void HLSDialog::on_satSlider_valueChanged(int value)
{
    ui->satSpinBox->setValue(value);
}

void HLSDialog::on_lightSlider_valueChanged(int value)
{
    ui->lightSpinBox->setValue(value);
}

void HLSDialog::on_hueSpinBox_valueChanged(int arg1)
{
    ui->hueSlider->setValue(arg1);
}

void HLSDialog::on_satSpinBox_valueChanged(int arg1)
{
    ui->satSlider->setValue(arg1);
}

void HLSDialog::on_lightSpinBox_valueChanged(int arg1)
{
    ui->lightSlider->setValue(arg1);
}


