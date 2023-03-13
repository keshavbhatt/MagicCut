#ifndef FILTERABLESORTFILTERPROXYMODEL_H
#define FILTERABLESORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

/**
 * This class overrides the filterAcceptsRow() method of the QSortFilterProxyModel
 * to recursively filter child nodes.
 * The filterAcceptsRow() method determines whether a given row in the source model
 * should be included in the filtered model.
 * We are recursively calling filterAcceptsRow() for each child index of the current row,
 * and returning true if any child index matches the filter.
 *
 * @brief The FilterableSortFilterProxyModel class
 */
class FilterableSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit FilterableSortFilterProxyModel(QObject *parent = nullptr)
        : QSortFilterProxyModel(parent)
    {}

    /**
     * This overrided method recursively calls filterAcceptsRow() for each child index of the current row,
     * and returns true if any child index matches the filter.
     *
     * @brief filterAcceptsRow
     * @param sourceRow
     * @param sourceParent
     * @return true if any child index matches the filter
     */
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
    {
        if (!filterRegExp().isEmpty()) {
            QRegExp regExp = filterRegExp();
            const QAbstractItemModel *model = sourceModel();
            const int columnCount = model->columnCount(sourceParent);
            bool match = false;
            for (int i = 0; i < columnCount; ++i) {
                QModelIndex index = model->index(sourceRow, i, sourceParent);
                if (model->hasChildren(index)) {
                    if (filterAcceptsRow(0, index)) {
                        return true;
                    }
                }
                const QString data = model->data(index, filterRole()).toString();
                match = regExp.indexIn(data) != -1;
                if (match) {
                    return true;
                }
            }
            return false;
        }
        return true;
    }
};

#endif // FILTERABLESORTFILTERPROXYMODEL_H
