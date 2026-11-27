#include <QVector>
#include <QStringList>
#include "recipe.hpp"

class RecipeManager {
public:
    RecipeManager();

    QVector<Recipe> recipes;
    QStringList weekMenu;
    QStringList days;

    void addRecipe(QString name, QString category, QString ingredients, QString text);
    QVector<Recipe> findRecipes(QString searchText, QString category);
    void setDayMeal(int dayIndex, QString mealName);
};
