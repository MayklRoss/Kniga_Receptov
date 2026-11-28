#include "test_manager.hpp"
#include "../src/recipemanager.hpp"
#include <QtTest/QtTest>

void TestRecipeManager::initTestCase() {}
void TestRecipeManager::cleanupTestCase() {}
void TestRecipeManager::init() {}
void TestRecipeManager::cleanup() {}

void TestRecipeManager::testInitialDatabase() {
    RecipeManager manager;
    
    QVERIFY(manager.recipes.size() > 0);
    
    QCOMPARE(manager.days.size(), 7);
    QCOMPARE(manager.days[0], QString("Понедельник"));
    
    QCOMPARE(manager.weekMenu.size(), 7);
    QCOMPARE(manager.weekMenu[0], QString("Не выбрано"));
}

void TestRecipeManager::testFindAndFiltering() {
    RecipeManager manager;
    
    QVector<Recipe> breakfasts = manager.findRecipes("", "Завтрак");
    for (const auto& r : breakfasts) {
        QCOMPARE(r.category, QString("Завтрак"));
    }
    
    QVector<Recipe> foundBorsch = manager.findRecipes("Борщ", "Все");
    QVERIFY(foundBorsch.size() >= 1);
    QCOMPARE(foundBorsch[0].name, QString("Борщ классический"));
    
    QVector<Recipe> emptyResult = manager.findRecipes("НесуществующееБлюдо123", "Все");
    QVERIFY(emptyResult.isEmpty());
}

void TestRecipeManager::testBubbleSort() {
    RecipeManager manager;
    
    QVector<Recipe> dinners = manager.findRecipes("", "Обед");
    
    for (int i = 0; i < dinners.size() - 1; ++i) {
        QVERIFY(dinners[i].name <= dinners[i + 1].name);
    }
}

void TestRecipeManager::testWeekMenu() {
    RecipeManager manager;
    
    manager.setDayMeal(1, "Борщ классический");
    
    QCOMPARE(manager.weekMenu[1], QString("Борщ классический"));
    
    manager.setDayMeal(1, "Не выбрано");
    QCOMPARE(manager.weekMenu[1], QString("Не выбрано"));
    
    manager.setDayMeal(10, "Каша");
    QCOMPARE(manager.weekMenu.size(), 7);
}