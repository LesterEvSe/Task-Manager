#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

private:
    Ui::Settings *ui;
    static QString m_file_name;

    void set_styles();

private slots:
    void on_backButton_clicked();
    void on_saveButton_clicked();

public:
    explicit Settings(QWidget *parent = nullptr);
    static void init();
    static int get_font_size();
    ~Settings();
};

#endif // SETTINGS_HPP
