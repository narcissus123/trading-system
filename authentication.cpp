#include "authentication.h"
#include "mainwindow.h"

/**
 * @brief Creates the login popup window.
 * @author Narges Haeri
 * @param parent Pointer to our main window application
 */

Authentication::Authentication(QWidget *parent):QDialog(parent){

    // add admin user
    User *admin = new User({"admin", "admin"});
    this->userList.push_back(admin);

    //set up the window
    setModal( true );
    QGridLayout *formGridLayout = new QGridLayout(this);
    Authentication::setWindowTitle("Login Window");
    Authentication::resize(400, 300);
    Authentication::setStyleSheet("QMainWindow{background-color: #fff;}");

    //This section asks for username from user to login
    userNameLabel = new QLabel("UserName:", this);
    userNameLabel->setGeometry(10, 20, 85, 33);
    userNameLabel->setStyleSheet("QLabel{font-size: 20px;font-family: Arial;color: rgb(38,56,76);}");

    userName = new QLineEdit(this);
    userName->setAlignment(Qt::AlignLeft);
    userName->setStyleSheet("QLineEdit{font-size: 20px;font-family: Arial;color: rgb(38,56,76);border-radius: 2%;border: 1px solid rgba(181, 141, 38, 0.733);}");

     //This section asks for password from user to login
    passwordLabel = new QLabel("Password:", this);
    passwordLabel->setStyleSheet("QLabel{font-size: 20px;font-family: Arial;color: rgb(38,56,76);}");

    password = new QLineEdit(this);
    password->setAlignment(Qt::AlignLeft);
    password->setStyleSheet("QLineEdit{font-size: 20px;font-family: Arial;color: rgb(38,56,76);border-radius: 2%;border: 1px solid rgba(181, 141, 38, 0.733);}");

    //SignIn button
    SignInButt = new QPushButton("SignIn", this);
    SignInButt->setStyleSheet("QPushButton{font-size: 14px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);border-radius: 5%;}");
    SignInButt->setStyleSheet("QPushButton{font-size: 14px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);border-radius: 5%;}");

     formGridLayout->addWidget( userNameLabel, 0, 0 );
     formGridLayout->addWidget( userName, 0, 1 );
     formGridLayout->addWidget( passwordLabel, 1, 0 );
     formGridLayout->addWidget( password, 1, 1 );
     formGridLayout->addWidget( SignInButt, 3, 1, 1, 2 );
     setLayout( formGridLayout );

     connect( SignInButt, SIGNAL (clicked()), this, SLOT (signIn()));

}

/**
 * @brief Authetnicates the user on sign in or asks to enter credentials again.
 * @author Narges Haeri
 */

//This slot will sign in the user after the user clicked sign in button
void Authentication::signIn(){

    std::string userNameInput = userName->text().toStdString();          //getting the username from input widget
    std::string passwordInput = password->text().toStdString();          //getting the password from input widget

    bool userfound = false;

    //checks if user previously signed in
    for(int i=0; i < (int)(this->userList.size()); i++){
        if( userList[i]->userName == userNameInput && userList[i]->password == passwordInput){
            userfound = true;
            this->loggedIn = true;
            userName->clear();
            password->clear();
            close();
        }
    }

    // If user not found then give error message and user can enter credentials again.
    if (!userfound){

        if(userNameInput.empty() || passwordInput.empty()){
            QMessageBox::information(this, "Empty field", "ERROR: All fields are required.");
        }
        else{
            QMessageBox::information(this, "User not found", "ERROR: Incorrect credentials. Please re-enter your credentials");
        }
    }

}

/**
 * @brief Gets the loggedin varaible. True is uccess, False is failure.
 * @author Narges Haeri
 */

bool Authentication::loggedin() {
    return this->loggedIn;
}
