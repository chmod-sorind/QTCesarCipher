#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioButton_encrypt_clicked()
{
    ui->ed_button->setText("Encrypt");
}

void MainWindow::on_radioButton_decrypt_clicked()
{
    ui->ed_button->setText("Decrypt");
}

static std::string encrypt( int k, std::string m )
{
        std::string msg;														// Define an empty string which will later contain the encripted message.
        for (int i = 0; m[i]; ++i)                                              // Iterate through the characters of the message.
        {
            /* Calculate the new ascii value by applying the encryptionKey to the caracter's ascii original value
                and then append the new character to the encriptedMessage string.
            */
            msg.push_back(static_cast<char>(static_cast<int>(m[i]) + k));
        }
        return msg;
}

static std::string decrypt( int k, std::string m )
{
        std::string msg;														// Define an empty string which will later contain the encripted message.
        for (int i = 0; m[i]; ++i)                                              // Iterate through the characters of the message.
        {
            /* Calculate the new ascii value by applying the encryptionKey to the caracter's ascii original value
                and then append the new character to the encriptedMessage string.
            */
            msg.push_back(static_cast<char>(static_cast<int>(m[i]) - k));
        }
        return msg;
}


void MainWindow::on_ed_button_clicked()
{
    if (ui->lineEdit_encryption_key->text() != NULL)
    {
        ui->label_key->setText("<font color=black>Encryption Key:</font>");
        if (ui->radioButton_encrypt->isChecked())
        {
            std::string ks = ui->lineEdit_encryption_key->text().toStdString();
            int key = atoi(ks.c_str());
            std::string message = ui->plainTextEdit_insrted->toPlainText().toStdString();
            std::string encryptedMessage = encrypt(key, message);
            ui->plainTextEdit_processed->clear();
            QString eMsg = QString::fromStdString(encryptedMessage);
            ui->plainTextEdit_processed->appendPlainText(eMsg);
        }
        else if (ui->radioButton_decrypt->isChecked())
        {
            std::string ks = ui->lineEdit_encryption_key->text().toStdString();
            int key = atoi(ks.c_str());
            std::string message = ui->plainTextEdit_insrted->toPlainText().toStdString();
            std::string encryptedMessage = decrypt(key, message);
            ui->plainTextEdit_processed->clear();
            QString eMsg = QString::fromStdString(encryptedMessage);
            ui->plainTextEdit_processed->appendPlainText(eMsg);
        }
    }
    else
    {
        ui->label_key->setText("<font color=red>Encryption Key:</font>");
    }
}
