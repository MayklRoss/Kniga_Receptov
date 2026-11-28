#include <QObject>

class TestRecipeManager : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();   
    void cleanupTestCase(); 
    void init();            
    void cleanup();       

    void testInitialDatabase();  
    void testFindAndFiltering(); 
    void testBubbleSort();       
    void testWeekMenu();        
};
