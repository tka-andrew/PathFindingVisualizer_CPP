#include "pathFindingAlgorithms.h"
#include "mainFrame.h"

#include <gtest/gtest.h>
#include <wx/wx.h>

TEST(ManhattanDistanceTest, Test01)
{
    std::array<int, 2> cell1{1, 2};
    std::array<int, 2> cell2{9, 3};
    int expected = 9;
    int result = getManhattanDistance(cell1, cell2);
    ASSERT_EQ(expected, result);
}

TEST(ManhattanDistanceTest, Test02)
{
    std::array<int, 2> cell1{2, 3};
    std::array<int, 2> cell2{5, 11};
    int expected = 11;
    int result = getManhattanDistance(cell1, cell2);
    ASSERT_EQ(expected, result);
}

TEST(ManhattanDistanceTest, Test03)
{
    std::array<int, 2> cell1{22, 8};
    std::array<int, 2> cell2{9, 3};
    int expected = 18;
    int result = getManhattanDistance(cell1, cell2);
    ASSERT_EQ(expected, result);
}

TEST(ManhattanDistanceTest, Test04)
{
    std::array<int, 2> cell1{20, 2};
    std::array<int, 2> cell2{10, 6};
    int expected = 14;
    int result = getManhattanDistance(cell1, cell2);
    ASSERT_EQ(expected, result);
}

// REFERENCE: https://www.remy.org.uk/tech.php?tech=1407951209
class TestApp : public wxApp
{
public:
    MainFrame *mainFrame;

    virtual bool OnInit()
    {
        mainFrame = new MainFrame("Path Finding Visualizer App", wxPoint(50, 50), wxSize(1440, 930));
        mainFrame->Show(true);
        return true;
    }
};

class DijkstraTest : public testing::Test
{
protected:
    TestApp *app;
    virtual void SetUp()
    {
        char appname[] = "wxUnitTest.exe";
        int argc = 1;
        char *argv[1] = {appname};
        app = new TestApp();
        wxApp::SetInstance(app);
        wxEntryStart(argc, argv);
        app->OnInit();
    }
    virtual void TearDown()
    {
        app->OnExit();
        wxEntryCleanup();
    }
};

// REFERENCE: https://www.youtube.com/watch?v=d_hZGBQrXcA&list=PL_dsdStdDXbo-zApdWB5XiF2aWpsqzV55&index=3
// Take note this is TEST_F() instead of TEST()
TEST_F(DijkstraTest, Test01)
{
    std::array<int, 2> startingPoint{0, 0};
    std::array<int, 2> destinationPoint{0, 4};
    int row = 40;
    int col = 60;
    auto pathFindingResult = dijkstraSingleTarget(startingPoint, destinationPoint, row, col, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 11;
    int expected_numOfCellCheckingOccurrence = 20;
    int expected_shortestDistance = 4;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
}

TEST_F(DijkstraTest, Test02)
{
    std::array<int, 2> startingPoint{10, 20};
    std::array<int, 2> destinationPoint{18, 7};
    int row = 40;
    int col = 60;
    auto pathFindingResult = dijkstraSingleTarget(startingPoint, destinationPoint, row, col, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 777;
    int expected_numOfCellCheckingOccurrence = 1599;
    int expected_shortestDistance = 21;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
}

TEST_F(DijkstraTest, Test03)
{
    std::array<int, 2> startingPoint{10, 20};
    std::array<int, 2> destinationPoint{27, 30};
    int row = 40;
    int col = 60;
    auto pathFindingResult = dijkstraSingleTarget(startingPoint, destinationPoint, row, col, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 1156;
    int expected_numOfCellCheckingOccurrence = 2345;
    int expected_shortestDistance = 27;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
}

TEST_F(DijkstraTest, Test04)
{
    std::array<int, 2> startingPoint{18, 31};
    std::array<int, 2> destinationPoint{12, 12};
    int row = 40;
    int col = 60;
    auto pathFindingResult = dijkstraSingleTarget(startingPoint, destinationPoint, row, col, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 1181;
    int expected_numOfCellCheckingOccurrence = 2427;
    int expected_shortestDistance = 25;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
}

class AStarTest : public testing::Test
{
protected:
    TestApp *app;
    virtual void SetUp()
    {
        char appname[] = "AStarTest01.exe";
        int argc = 1;
        char *argv[1] = {appname};
        app = new TestApp();
        wxApp::SetInstance(app);
        wxEntryStart(argc, argv);
        app->OnInit();
    }
    
    virtual void TearDown()
    {
        app->OnExit();
        wxEntryCleanup();
    }
};

TEST_F(AStarTest, Test01)
{
    std::array<int, 2> startingPoint{12, 10};
    std::array<int, 2> destinationPoint{6, 19};
    int row = 40;
    int col = 60;
    auto pathFindingResult = aStarSearch(startingPoint, destinationPoint, row, col, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 16;
    int expected_numOfCellCheckingOccurrence = 46;
    int expected_shortestDistance = 15;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
}

TEST_F(AStarTest, Test02)
{
    std::array<int, 2> startingPoint{8, 13};
    std::array<int, 2> destinationPoint{25, 22};
    int row = 40;
    int col = 60;
    auto pathFindingResult = aStarSearch(startingPoint, destinationPoint, row, col, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 180;
    int expected_numOfCellCheckingOccurrence = 386;
    int expected_shortestDistance = 16;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
}

TEST_F(AStarTest, Test03)
{
    std::array<int, 2> startingPoint{13, 37};
    std::array<int, 2> destinationPoint{24, 17};
    int row = 40;
    int col = 60;
    auto pathFindingResult = aStarSearch(startingPoint, destinationPoint, row, col, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 232;
    int expected_numOfCellCheckingOccurrence = 494;
    int expected_shortestDistance = 31;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
}

TEST_F(AStarTest, Test04)
{
    std::array<int, 2> startingPoint{30, 43};
    std::array<int, 2> destinationPoint{10, 24};
    int row = 40;
    int col = 60;
    auto pathFindingResult = aStarSearch(startingPoint, destinationPoint, row, col, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 40;
    int expected_numOfCellCheckingOccurrence = 118;
    int expected_shortestDistance = 39;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
}
