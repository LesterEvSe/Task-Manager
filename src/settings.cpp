#include "settings.hpp"
#include "ui_settings.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>

QString Settings::m_file_name = "Settings";


Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->fontSizeSpinBox->setRange(10, 50);
    ui->fontSizeSpinBox->setValue(get_font_size());
    set_styles();
}

void Settings::set_styles() {
    setStyleSheet(QString("font-size: %1pt;").arg(Settings::get_font_size()));
    auto set_icon = [](QPushButton *button, const QString &path){
        QIcon icon(path);
        int min = std::min(button->size().width(), button->size().height());

        button->setText("");
        button->setIcon(icon);
        button->setIconSize(QSize(min, min));
    };
    set_icon(ui->backButton, ":/res/return.png");
    set_icon(ui->saveButton, ":/res/save.png");
}

void Settings::init() {
    QFile file(m_file_name);

    // Debuging action
//    if (file.exists()) {
//        file.remove();
//        exit(2);
//    }

    if (file.exists()) return;
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << "Font Size: 25\n";
        file.close();
    }
}

Settings::~Settings() {
    delete ui;
}

void Settings::on_backButton_clicked() {
    reject();
}

void Settings::on_saveButton_clicked() {
    int font_size = ui->fontSizeSpinBox->value();
    QFile file(m_file_name);

    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream stream(&file);
        file.resize(0);

        stream << "Font Size: " << QString::number(font_size);
        file.close();
    }

    QMessageBox::information(this, "The changes have been saved",
                             "For the changes to take effect, restart the application");
    accept();
}

int Settings::get_font_size()
{
    QFile file(m_file_name);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        QStringList parts = stream.readLine().split(": ");

        int font_size = parts[1].toInt();
        file.close();
        return font_size;
    }
    return -1;
}
