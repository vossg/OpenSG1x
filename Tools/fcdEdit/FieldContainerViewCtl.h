#ifndef NODEVIEWCTL_H
#define NODEVIEWCTL_H

#include "FieldContainerView.h"
#include "FieldContainer.h"

class Field;

class FieldContainerViewCtl : public FieldContainerView
{ 
    Q_OBJECT;

		FieldContainer     _fieldContainer;
		
		Field *_activePart;
		int   _activePartIndex;

		bool _lineUpdate;

		void updateList(void);
		void updateActiveListItem(void);

		void updateFieldContainerView(void);
		void updateActivePartView(void);

		void loadFieldContainer(const char *fileNam);
		
		char *_procGroup;

		void sync(void);

public:

		FieldContainerViewCtl( const char *file = 0 );
    ~FieldContainerViewCtl();

public slots:

		void aboutSlot();
    void activePartChanged(int);
    void clonePartSlot();
    void deletePartSlot();
		void downPartSlot();		
    void exitSlot();
		void libraryChanged(const QString &);
		void loadFieldTypesSlot();
		void loadParentSlot();
    void loadSlot();
    void nameChanged(const QString &);
    void newPartSlot();
		void newSlot();
    void resetFieldTypesSlot();
    void parentChanged(const QString &);
		void partCardinalityChanged(int);
    void partTypeChanged(int);
    void partDefaultValueChanged(const QString &);
    void partDescriptionChanged(const QString &);
    void partNameChanged(const QString &);
		void partVisibilityChanged(int);		
		void pointerFieldTypesChanged(int); 
		void saveAsSlot();
    void saveSlot();
		void upPartSlot();
    void writeFieldContainerBaseSlot();
    void writeFieldContainerSlot();

};

#endif // NODEVIEWCTL_H
