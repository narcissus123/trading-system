/**
 * @brief This class deals with the user login of the application and authenticating users.
 * @author Narges Haeri
 */

#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QAbstractItemModel>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QStringList>
#include <QDebug>
#include <QGridLayout>
#include <QString>
#include <QMessageBox>

class Authentication : public QDialog
{
    Q_OBJECT

public slots:
    void signIn();

public:

    explicit Authentication(QWidget *parent = nullptr);
    bool loggedin();

private:
    Authentication *ui;
    QLabel *userNameLabel;
    QLineEdit *userName;
    QLabel *passwordLabel;
    QLineEdit *password;
    QPushButton *SignInButt;

    struct User{
        std::string userName;
        std::string password;
        int id;
    };

    std::vector<User*> userList;
    bool loggedIn = false;
    bool clicked = false;
};

#endif // AUTHENTICATION_H
