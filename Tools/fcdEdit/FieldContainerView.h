/****************************************************************************
** Form interface generated from reading ui file 'FieldContainerView.ui'
**
** Created: Wed Apr 4 11:43:38 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FIELDCONTAINERVIEW_H
#define FIELDCONTAINERVIEW_H

#include <qvariant.h>
#include <qdialog.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QComboBox;
class QFrame;
class QGroupBox;
class QLabel;
class QLineEdit;
class QListBox;
class QListBoxItem;
class QMultiLineEdit;
class QPushButton;

class FieldContainerView : public QDialog
{ 
    Q_OBJECT

public:
    FieldContainerView( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~FieldContainerView();

    QGroupBox* GroupBox1;
    QGroupBox* GroupBox17;
    QLabel* TextLabel2;
    QLabel* TextLabel3;
    QLabel* TextLabel1;
    QLineEdit* nodeParentInput;
    QLineEdit* nodeNameInput;
    QLineEdit* nodeLibraryInput;
    QLabel* TextLabel1_4;
    QLabel* TextLabel1_5;
    QComboBox* pointerFieldTypesCombo;
    QComboBox* structureCombo;
    QGroupBox* GroupBox7;
    QMultiLineEdit* nodeDescriptionInput;
    QGroupBox* GroupBox3;
    QListBox* partListBox;
    QFrame* partFrame;
    QLabel* TextLabel3_2;
    QComboBox* partTypeCombo;
    QLabel* TextLabel2_2;
    QLabel* TextLabel1_2;
    QLabel* TextLabel5;
    QLineEdit* partDescriptionInput;
    QLabel* TextLabel4_2;
    QComboBox* partCardinalityCombo;
    QLineEdit* partNameInput;
    QLabel* TextLabel2_3;
    QLabel* TextLabel1_3;
    QLabel* TextLabel3_3;
    QComboBox* partAccessCombo;
    QComboBox* partVisibilityCombo;
    QLineEdit* partIncludeInput;
    QLineEdit* partDefaultValueInput;
    QPushButton* newPart;
    QPushButton* deletePart;
    QPushButton* clonePart;
    QPushButton* upPart;
    QPushButton* downPart;
    QPushButton* writeNodeCode;
    QPushButton* writeProcCode;
    QPushButton* saveAs;
    QPushButton* load;
    QPushButton* save;
    QPushButton* PushButton15;
    QPushButton* PushButton16;
    QPushButton* loadParent;
    QPushButton* PushButton14;
    QPushButton* about;
    QPushButton* exit;

public slots:
    virtual void aboutSlot();
    virtual void activePartChanged(int);
    virtual void clonePartSlot();
    virtual void deletePartSlot();
    virtual void downPartSlot();
    virtual void exitSlot();
    virtual void libraryChanged(const QString &);
    virtual void loadFieldTypesSlot();
    virtual void loadParentSlot();
    virtual void loadSlot();
    virtual void nameChanged(const QString &);
    virtual void newPartSlot();
    virtual void newSlot();
    virtual void partIncludeChanged(const QString &);
    virtual void parentChanged(const QString &);
    virtual void partAccessChanged(int);
    virtual void partCardinalityChanged(int);
    virtual void partDefaultValueChanged(const QString &);
    virtual void partDescriptionChanged(const QString &);
    virtual void partNameChanged(const QString &);
    virtual void partTypeChanged(int);
    virtual void partVisibilityChanged(int);
    virtual void pointerFieldTypesChanged(int);
    virtual void resetFieldTypesSlot();
    virtual void saveAsSlot();
    virtual void saveSlot();
    virtual void structureChanged(int);
    virtual void upPartSlot();
    virtual void writeFieldContainerBaseSlot();
    virtual void writeFieldContainerSlot();

protected:
    QVBoxLayout* FieldContainerViewLayout;
    QHBoxLayout* Layout8;
    QVBoxLayout* GroupBox1Layout;
    QGridLayout* GroupBox17Layout;
    QVBoxLayout* GroupBox7Layout;
    QVBoxLayout* GroupBox3Layout;
    QGridLayout* partFrameLayout;
    QHBoxLayout* Layout3;
    QHBoxLayout* Layout7;
    QGridLayout* Layout6;
    QVBoxLayout* Layout4;
};

#endif // FIELDCONTAINERVIEW_H
