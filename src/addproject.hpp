#ifndef ADDPROJECT_HPP
#define ADDPROJECT_HPP

#include <QDialog>
#include <QString>

namespace Ui {
class AddProject;
}

class AddProject : public QDialog
{
    Q_OBJECT
private:
    Ui::AddProject *ui;

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

public:
    explicit AddProject(QWidget *parent = nullptr);
    ~AddProject();

signals:
    void textEntered(QString text);
};

#endif // ADDPROJECT_HPP
