/****************************************************************************
** Form interface generated from reading ui file 'FieldContainerView.ui'
**
** Created: Wed Mar 28 15:00:05 2001
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
    QComboBox* pointerFieldTypesCombo;
    QGroupBox* GroupBox7;
    QMultiLineEdit* nodeDescriptionInput;
    QGroupBox* GroupBox3;
    QListBox* partListBox;
    QFrame* partFrame;
    QLineEdit* partNameInput;
    QLabel* TextLabel1_2;
    QLabel* TextLabel3_2;
    QComboBox* partTypeCombo;
    QLineEdit* partDescriptionInput;
    QLabel* TextLabel5;
    QLabel* TextLabel4_2;
    QLineEdit* partDefaultValueInput;
    QLabel* TextLabel1_3;
    QComboBox* partVisibilityCombo;
    QLabel* TextLabel2_2;
    QComboBox* partCardinalityCombo;
    QPushButton* newPart;
    QPushButton* deletePart;
    QPushButton* clonePart;
    QPushButton* upPart;
    QPushButton* downPart;
    QPushButton* load;
    QPushButton* save;
    QPushButton* PushButton16;
    QPushButton* loadParent;
    QPushButton* PushButton15;
    QPushButton* writeNodeCode;
    QPushButton* PushButton14;
    QPushButton* writeProcCode;
    QPushButton* saveAs;
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
    virtual void resetFieldTypesSlot();
    virtual void parentChanged(const QString &);
    virtual void partCardinalityChanged(int);
    virtual void partDefaultValueChanged(const QString &);
    virtual void partDescriptionChanged(const QString &);
    virtual void partNameChanged(const QString &);
    virtual void partTypeChanged(int);
    virtual void partVisibilityChanged(int);
    virtual void pointerFieldTypesChanged(int);
    virtual void saveAsSlot();
    virtual void saveSlot();
    virtual void upPartSlot();
    virtual void writeFieldContainerBaseSlot();
    virtual void writeFieldContainerSlot();

protected:
    QVBoxLayout* FieldContainerViewLayout;
    QHBoxLayout* Layout6;
    QVBoxLayout* GroupBox1Layout;
    QGridLayout* GroupBox17Layout;
    QVBoxLayout* GroupBox7Layout;
    QVBoxLayout* GroupBox3Layout;
    QGridLayout* partFrameLayout;
    QHBoxLayout* Layout3;
    QHBoxLayout* Layout8;
    QGridLayout* Layout7;
    QVBoxLayout* Layout4;
};

#endif // FIELDCONTAINERVIEW_H
