#ifndef FRIENDFORM_H
#define FRIENDFORM_H


#include <QFrame>

namespace Ui {
class FriendForm;
}

namespace ok::backend{
struct OrgStaff;
}

class FriendForm : public QFrame
{
    Q_OBJECT

public:
    explicit FriendForm(ok::backend::OrgStaff* staff, QWidget *parent = nullptr);
    ~FriendForm();


private:
    Ui::FriendForm *ui;
    QString username;
    ok::backend::OrgStaff* staff;

    signals:
      void onClicked(QString &username);
};

#endif // FRIENDFORM_H
