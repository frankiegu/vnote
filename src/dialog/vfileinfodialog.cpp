#include <QtWidgets>
#include "vfileinfodialog.h"

VFileInfoDialog::VFileInfoDialog(const QString &title, const QString &info,
                                 const QString &defaultName,
                                 QWidget *parent)
    : QDialog(parent), infoLabel(NULL), title(title), info(info), defaultName(defaultName)
{
    setupUI();

    connect(nameEdit, &QLineEdit::textChanged, this, &VFileInfoDialog::enableOkButton);
    connect(okBtn, &QPushButton::clicked, this, &VFileInfoDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, this, &VFileInfoDialog::reject);

    enableOkButton();
}

void VFileInfoDialog::setupUI()
{
    if (!info.isEmpty()) {
        infoLabel = new QLabel(info);
    }
    nameLabel = new QLabel(tr("&Name"));
    nameEdit = new QLineEdit(defaultName);
    nameEdit->selectAll();
    nameLabel->setBuddy(nameEdit);

    okBtn = new QPushButton(tr("&OK"));
    okBtn->setDefault(true);
    cancelBtn = new QPushButton(tr("&Cancel"));

    QVBoxLayout *topLayout = new QVBoxLayout();
    if (infoLabel) {
        topLayout->addWidget(infoLabel);
    }
    topLayout->addWidget(nameLabel);
    topLayout->addWidget(nameEdit);

    QHBoxLayout *btmLayout = new QHBoxLayout();
    btmLayout->addStretch();
    btmLayout->addWidget(okBtn);
    btmLayout->addWidget(cancelBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(btmLayout);
    setLayout(mainLayout);

    setWindowTitle(title);
}

void VFileInfoDialog::enableOkButton()
{
    okBtn->setEnabled(!nameEdit->text().isEmpty());
}

QString VFileInfoDialog::getNameInput() const
{
    return nameEdit->text();
}