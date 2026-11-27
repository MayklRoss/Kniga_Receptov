#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include "recipemanager.hpp"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow();

public slots:
    void updateList();
    void selectCategory(QString category);
    void showRecipe();
    void addToWeek();
    void clearDay();

private:
    void updateMenuTable();

    RecipeManager m_manager;
    QVector<Recipe> m_currentRecipes;
    QString m_currentCategory;

    QLineEdit *m_searchEdit;
    QListWidget *m_listWidget;
    QTextEdit *m_detailsEdit;
    QTableWidget *m_menuTable;
};
