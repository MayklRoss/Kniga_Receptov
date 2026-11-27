#include "mainwindow.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

MainWindow::MainWindow() {
    m_currentCategory = "Все";

    const QSize colSize(280, 400);
    const QSize btnSize(120, 30);

    QHBoxLayout *mainHLay = new QHBoxLayout(this);
    QVBoxLayout *col1Lay = new QVBoxLayout();
    QVBoxLayout *col2Lay = new QVBoxLayout();
    QVBoxLayout *col3Lay = new QVBoxLayout();

    this->setLayout(mainHLay);
    m_searchEdit = new QLineEdit(this);

    QHBoxLayout *catLay = new QHBoxLayout();
    QStringList categories = {"Все", "Завтрак", "Обед", "Ужин", "Десерт"};
    for (int i = 0; i < categories.size(); i++) {
        QString catName = categories[i];
        QPushButton *catBtn = new QPushButton(catName, this);
        catLay->addWidget(catBtn);
        connect(catBtn, &QPushButton::clicked, [this, catName]() {
            selectCategory(catName);
        });
    }

    m_listWidget = new QListWidget(this);
    m_listWidget->setFixedSize(QSize(colSize.width(), colSize.height() + 4));

    col1Lay->addWidget(m_searchEdit);
    col1Lay->addLayout(catLay);
    col1Lay->addWidget(m_listWidget);

    QLabel *infoLabel = new QLabel("Описание рецепта:", this);
    m_detailsEdit = new QTextEdit(this);
    m_detailsEdit->setReadOnly(true);
    m_detailsEdit->setFixedSize(colSize);

    QPushButton *toMenuBtn = new QPushButton("В меню", this);
    toMenuBtn->setFixedSize(QSize(colSize.width(), btnSize.height()));

    col2Lay->addWidget(infoLabel);
    col2Lay->addWidget(m_detailsEdit);
    col2Lay->addWidget(toMenuBtn);

    QLabel *menuLabel = new QLabel("Меню на неделю:", this);
    m_menuTable = new QTableWidget(7, 2, this);
    m_menuTable->setHorizontalHeaderLabels({"День недели", "Блюдо"});
    m_menuTable->setColumnWidth(0, 120);
    m_menuTable->setColumnWidth(1, 150); 
    m_menuTable->setFixedSize(colSize);

    QPushButton *clearBtn = new QPushButton("Очистить день", this);
    clearBtn->setFixedSize(QSize(colSize.width(), btnSize.height()));

    col3Lay->addWidget(menuLabel);
    col3Lay->addWidget(m_menuTable);
    col3Lay->addWidget(clearBtn);

    mainHLay->addLayout(col1Lay);
    mainHLay->addLayout(col2Lay);
    mainHLay->addLayout(col3Lay);

    setFixedSize(colSize.width() * 3 + 40, colSize.height() + btnSize.height() + 80);
    
    connect(m_searchEdit, &QLineEdit::textChanged, this, &MainWindow::updateList);
    connect(m_listWidget, &QListWidget::itemSelectionChanged, this, &MainWindow::showRecipe);
    connect(toMenuBtn, &QPushButton::clicked, this, &MainWindow::addToWeek);
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::clearDay);

    updateList();
    updateMenuTable();
    show();
}

void MainWindow::selectCategory(QString category) {
    m_currentCategory = category;
    updateList();
}

void MainWindow::updateList() {
    m_listWidget->clear();
    m_detailsEdit->clear();
    m_currentRecipes = m_manager.findRecipes(m_searchEdit->text(), m_currentCategory);
    for (int i = 0; i < m_currentRecipes.size(); i++) {
        m_listWidget->addItem(m_currentRecipes[i].name);
    }
}

void MainWindow::updateMenuTable() {
    for (int i = 0; i < 7; i++) {
        m_menuTable->setItem(i, 0, new QTableWidgetItem(m_manager.days[i]));
        m_menuTable->setItem(i, 1, new QTableWidgetItem(m_manager.weekMenu[i]));
    }
}

void MainWindow::showRecipe() {
    int row = m_listWidget->currentRow();
    if (row < 0) return;
    Recipe r = m_currentRecipes[row];
    m_detailsEdit->setText("Название: " + r.name + "\n\n" +
                           "Категория: " + r.category + "\n\n" +
                           "Ингредиенты:\n" + r.ingredients + "\n\n" +
                           "Как готовить:\n" + r.text);
}

void MainWindow::addToWeek() {
    int recipeRow = m_listWidget->currentRow();
    int dayRow = m_menuTable->currentRow();
    if (recipeRow < 0 || dayRow < 0) return;
    m_manager.setDayMeal(dayRow, m_currentRecipes[recipeRow].name);
    updateMenuTable();
}

void MainWindow::clearDay() {
    int row = m_menuTable->currentRow();
    if (row >= 0) {
        m_manager.setDayMeal(row, "Не выбрано");
        updateMenuTable();
    }
}
