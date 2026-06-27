#include "notemodel.h"
#include <QDebug>
#include <algorithm>

NoteModel::NoteModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int NoteModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_notes.count();
}

int NoteModel::count() const
{
    return m_notes.count();
}

QVariant NoteModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_notes.count()) {
        return QVariant();
    }

    const NoteItem &item = m_notes.at(index.row());

    switch (role) {
    case NoteIdRole:
        return item.noteId;
    case TitleRole:
        return item.title;
    case TypeRole:
        return item.type;
    case MimeRole:
        return item.mime;
    case IsProtectedRole:
        return item.isProtected;
    case DateCreatedRole:
        return item.dateCreated;
    case DateModifiedRole:
        return item.dateModified;
    case IconClassRole:
        return item.iconClass;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> NoteModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NoteIdRole] = "noteId";
    roles[TitleRole] = "title";
    roles[TypeRole] = "type";
    roles[MimeRole] = "mime";
    roles[IsProtectedRole] = "isProtected";
    roles[DateCreatedRole] = "dateCreated";
    roles[DateModifiedRole] = "dateModified";
    roles[IconClassRole] = "iconClass";
    return roles;
}

void NoteModel::loadNotes(const QJsonArray &jsonArray)
{
    beginResetModel();
    m_notes.clear();

    for (const QJsonValue &value : jsonArray) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            NoteItem item;
            item.noteId = obj.value(QStringLiteral("noteId")).toString();
            item.title = obj.value(QStringLiteral("title")).toString();
            item.type = obj.value(QStringLiteral("type")).toString();
            item.mime = obj.value(QStringLiteral("mime")).toString();
            item.isProtected = obj.value(QStringLiteral("isProtected")).toBool();
            item.dateCreated = obj.value(QStringLiteral("dateCreated")).toString();
            item.dateModified = obj.value(QStringLiteral("dateModified")).toString();
            
            // Parse iconClass from note properties or attributes
            item.iconClass = obj.value(QStringLiteral("iconClass")).toString();
            if (item.iconClass.isEmpty()) {
                QJsonArray attributes = obj.value(QStringLiteral("attributes")).toArray();
                for (const QJsonValue &attrValue : attributes) {
                    if (attrValue.isObject()) {
                        QJsonObject attrObj = attrValue.toObject();
                        if (attrObj.value(QStringLiteral("type")).toString() == QStringLiteral("label") &&
                            attrObj.value(QStringLiteral("name")).toString() == QStringLiteral("iconClass")) {
                            item.iconClass = attrObj.value(QStringLiteral("value")).toString();
                            break;
                        }
                    }
                }
            }

            m_notes.append(item);
        }
    }

    // Sort alphabetically by title
    std::sort(m_notes.begin(), m_notes.end(), [](const NoteItem &a, const NoteItem &b) {
        return a.title.localeAwareCompare(b.title) < 0;
    });

    endResetModel();
    emit countChanged();
}

void NoteModel::clear()
{
    beginResetModel();
    m_notes.clear();
    endResetModel();
    emit countChanged();
}

QVariantMap NoteModel::getNote(int index) const
{
    QVariantMap map;
    if (index >= 0 && index < m_notes.count()) {
        const NoteItem &item = m_notes.at(index);
        map[QStringLiteral("noteId")] = item.noteId;
        map[QStringLiteral("title")] = item.title;
        map[QStringLiteral("type")] = item.type;
        map[QStringLiteral("mime")] = item.mime;
        map[QStringLiteral("isProtected")] = item.isProtected;
        map[QStringLiteral("dateCreated")] = item.dateCreated;
        map[QStringLiteral("dateModified")] = item.dateModified;
        map[QStringLiteral("iconClass")] = item.iconClass;
    }
    return map;
}
