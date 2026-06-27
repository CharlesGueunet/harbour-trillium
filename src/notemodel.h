#ifndef NOTEMODEL_H
#define NOTEMODEL_H

#include <QAbstractListModel>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>

struct NoteItem
{
    QString noteId;
    QString title;
    QString type;
    QString mime;
    bool isProtected;
    QString dateCreated;
    QString dateModified;
    QString iconClass;
};

class NoteModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    enum NoteRoles {
        NoteIdRole = Qt::UserRole + 1,
        TitleRole,
        TypeRole,
        MimeRole,
        IsProtectedRole,
        DateCreatedRole,
        DateModifiedRole,
        IconClassRole
    };

    explicit NoteModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    int count() const;

    Q_INVOKABLE void loadNotes(const QJsonArray &jsonArray);
    Q_INVOKABLE void clear();
    Q_INVOKABLE QVariantMap getNote(int index) const;

signals:
    void countChanged();

private:
    QVector<NoteItem> m_notes;
};

#endif // NOTEMODEL_H
