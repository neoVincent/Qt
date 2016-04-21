#ifndef CUSTOMCLASS_H
#define CUSTOMCLASS_H

#include <QObject>
#include <QString>

struct CustomClass
{
private:
    Q_GADGET

    Q_PROPERTY(int id MEMBER m_id)
    Q_PROPERTY(QString name MEMBER m_name)

public:
    int m_id;
    QString m_name;
};


inline bool operator == (const CustomClass& lhs, const CustomClass& rhs)
{
    return (lhs.m_id == rhs.m_id && lhs.m_name == rhs.m_name);
}

inline bool operator != (const CustomClass& lhs, const CustomClass& rhs)
{
    return !(lhs == rhs);
}

Q_DECLARE_METATYPE(CustomClass)

#endif // CUSTOMCLASS_H
