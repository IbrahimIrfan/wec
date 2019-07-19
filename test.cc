#include <QInputDialog>
#include <QString>
#include <iostream>

int main() { 
	bool ok;
	QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("User name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
	if (ok && !text.isEmpty())
        std::cout << text.toStdString() << std::endl;
}