// $Id$
/**
 * This file is part of OpenModelica.
 *
 * Copyright (c) 1998-CurrentYear, Open Source Modelica Consortium (OSMC),
 * c/o Linköpings universitet, Department of Computer and Information Science,
 * SE-58183 Linköping, Sweden.
 *
 * All rights reserved.
 *
 * THIS PROGRAM IS PROVIDED UNDER THE TERMS OF GPL VERSION 3 LICENSE OR
 * THIS OSMC PUBLIC LICENSE (OSMC-PL).
 * ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS PROGRAM CONSTITUTES RECIPIENT'S ACCEPTANCE
 * OF THE OSMC PUBLIC LICENSE OR THE GPL VERSION 3, ACCORDING TO RECIPIENTS CHOICE.
 *
 * The OpenModelica software and the Open Source Modelica
 * Consortium (OSMC) Public License (OSMC-PL) are obtained
 * from OSMC, either from the above address,
 * from the URLs: http://www.ida.liu.se/projects/OpenModelica or
 * http://www.openmodelica.org, and in the OpenModelica distribution.
 * GNU version 3 is obtained from: http://www.gnu.org/copyleft/gpl.html.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without
 * even the implied warranty of  MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE, EXCEPT AS EXPRESSLY SET FORTH
 * IN THE BY RECIPIENT SELECTED SUBSIDIARY LICENSE CONDITIONS OF OSMC-PL.
 *
 * See the full OSMC Public License conditions for more details.
 *
 * Main contributor 2010, Hubert Thierot, CEP - ARMINES (France)

     @file MOItem.h
     @brief Comments for file documentation.
     @author Hubert Thieriot, hubert.thieriot@mines-paristech.fr
     Company : CEP - ARMINES (France)
     http://www-cep.ensmp.fr/english/
     @version

  */
#if !defined(_MOITEM_H)
#define _MOITEM_H

#include <vector>
#include <QtCore/QObject>
#include <QtCore/QAbstractTableModel>
#include <QtCore/QTextStream>
#include <QtCore/QStringList>
#include <QtXml/QDomDocument>
#include <limits>


#include "Info.h"
#include "XMLTools.h"

class ProjectBase;


/**
* \class MOItem is a principal class in OMOptim. It is basic data container.
* Most of other data container inherit MOItem in OMOptim. It allows to create template vector with it but also
* facilitates displaying in table or tree view.
* MOItem is an abstract class.
*/
class MOItem : public QObject
{
    Q_OBJECT
public:

    enum FieldType
    {
        FOLDERPATH,
        FILEPATH,
        STRING,
        BOOL,
        INT,
        DOUBLE,
        LIST,
        GENERIC
    };


    /**
    * /enum Field : list of fields of data container.
    * \warning NAME should be present in all data containers inheriting MOItem.
    **/
    enum Field
    {
        NAME
    };

    // Constructor and destructor
    MOItem(QObject* parent =NULL);
    MOItem(const MOItem &);
    MOItem(QDomElement & domEl);

    virtual ~MOItem(void);

    virtual void update(QDomElement & domEl);
    // Constructor from saved string
    MOItem(QString,ProjectBase*);

    virtual QString getClassName() const =0;

    //Name
    virtual void setName(QString);
    virtual QString name() const;

    //All fields
    virtual QVariant getFieldValue(int, int role = Qt::UserRole) const;
    virtual QVariant getFieldValue(const QString &, int role = Qt::UserRole) const;
    virtual bool setFieldValue(int, QVariant);
    virtual bool setFieldValue(QString, QVariant);

    virtual int getFieldIndex(const QString &_fieldName,int role= Qt::DisplayRole) const;

    virtual QString getFieldName(int iField,int role = Qt::DisplayRole) const=0;
    static QString sFieldName(int field, int role);
    virtual QString getFieldDescription(int iField) const;
    virtual MOItem::FieldType getFieldType(int iField) const;

    void setProtectedFields(QList<int> protectedFields);
    void setIsProtectedField(int iField, bool isProtected);
    bool isProtectedField(int);
    bool protectAllFields();
    void setEditableFields(QList<int> editableFields);
    virtual bool isListField(int) const{return false;}
    virtual QMap<int,QString> fieldList(int iField) const{return QMap<int,QString>();}

    static const int nbFields = 1;
    virtual unsigned getNbFields() const=0;
    virtual bool check(QString &error);
    virtual QString toSavingString();
    virtual QDomElement toXmlData(QDomDocument & doc);
    virtual QString toCSV() const;
    virtual QString getStrToolTip();
    void checkUniqueItemName( QStringList & list);



signals:
    void sendInfo(Info);

protected:
    QString _name;
    QList<int> _filledFields; /// list of fields index that have been set
    QList<int> _protectedFields; /// list of fields that are protected from editing by the user (e.g. through GUI)

};



#endif
