#include "pathFindingAlgorithms.h"
#include "mainFrame.h"

#include <gtest/gtest.h>
#include <wx/wx.h>

#include <climits>

// global variables
static const int gridRow = 40;
static const int gridCol = 60;

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
        char appname[] = "DijkstraTest.exe";
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
    auto pathFindingResult = dijkstraSingleTarget(startingPoint, destinationPoint, gridRow, gridCol, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 11;
    int expected_numOfCellCheckingOccurrence = 20;
    int expected_shortestDistance = 4;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(shortestDistance, expected_shortestDistance);
}

TEST_F(DijkstraTest, Test02)
{
    std::array<int, 2> startingPoint{10, 20};
    std::array<int, 2> destinationPoint{18, 7};
    auto pathFindingResult = dijkstraSingleTarget(startingPoint, destinationPoint, gridRow, gridCol, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 777;
    int expected_numOfCellCheckingOccurrence = 1599;
    int expected_shortestDistance = 21;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(shortestDistance, expected_shortestDistance);
}

TEST_F(DijkstraTest, Test03)
{
    std::array<int, 2> startingPoint{10, 20};
    std::array<int, 2> destinationPoint{27, 30};
    auto pathFindingResult = dijkstraSingleTarget(startingPoint, destinationPoint, gridRow, gridCol, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 1156;
    int expected_numOfCellCheckingOccurrence = 2345;
    int expected_shortestDistance = 27;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(shortestDistance, expected_shortestDistance);
}

TEST_F(DijkstraTest, Test04)
{
    std::array<int, 2> startingPoint{18, 31};
    std::array<int, 2> destinationPoint{12, 12};
    auto pathFindingResult = dijkstraSingleTarget(startingPoint, destinationPoint, gridRow, gridCol, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 1181;
    int expected_numOfCellCheckingOccurrence = 2427;
    int expected_shortestDistance = 25;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(shortestDistance, expected_shortestDistance);
}

TEST_F(DijkstraTest, ObstacleTest)
{
    std::array<int, 2> startingPoint{7, 37};
    std::array<int, 2> destinationPoint{18, 12};
    // set obstacles
    int rowTopLeft = 4;
    int colTopLeft = 18;
    int rowBottomRight = 26;
    int colBottomRight = 32;
    for (int j = rowTopLeft; j <= rowBottomRight; j++)
    {
        for (int k = colTopLeft; k <= colBottomRight; k++)
        {
            app->mainFrame->m_lp->grid->SetCellBackgroundColour(j, k, wxColour(0, 0, 0)); // black
        }
    }

    auto pathFindingResult = dijkstraSingleTarget(startingPoint, destinationPoint, gridRow, gridCol, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 1523;
    int expected_numOfCellCheckingOccurrence = 2991;
    int expected_shortestDistance = 44;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(shortestDistance, expected_shortestDistance);
}


TEST_F(DijkstraTest, UnreachableTest)
{
    std::array<int, 2> startingPoint{2, 2};
    std::array<int, 2> destinationPoint{2, 10};
    // set obstacles
    int rowTopLeft = 0;
    int colTopLeft = 4;
    int rowBottomRight = 39;
    int colBottomRight = 6;
    for (int j = rowTopLeft; j <= rowBottomRight; j++)
    {
        for (int k = colTopLeft; k <= colBottomRight; k++)
        {
            app->mainFrame->m_lp->grid->SetCellBackgroundColour(j, k, wxColour(0, 0, 0)); // black
        }
    }

    auto pathFindingResult = dijkstraSingleTarget(startingPoint, destinationPoint, gridRow, gridCol, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 160;
    int expected_numOfCellCheckingOccurrence = 276;
    int expected_shortestDistance = INT_MAX;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(shortestDistance, expected_shortestDistance);
}

class AStarTest : public testing::Test
{
protected:
    TestApp *app;
    virtual void SetUp()
    {
        char appname[] = "AStarTest.exe";
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
    auto pathFindingResult = aStarSearch(startingPoint, destinationPoint, gridRow, gridCol, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 16;
    int expected_numOfCellCheckingOccurrence = 46;
    int expected_shortestDistance = 15;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(shortestDistance, expected_shortestDistance);
}

TEST_F(AStarTest, Test02)
{
    std::array<int, 2> startingPoint{8, 13};
    std::array<int, 2> destinationPoint{25, 22};
    auto pathFindingResult = aStarSearch(startingPoint, destinationPoint, gridRow, gridCol, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 180;
    int expected_numOfCellCheckingOccurrence = 386;
    int expected_shortestDistance = 26;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(shortestDistance, expected_shortestDistance);
}

TEST_F(AStarTest, Test03)
{
    std::array<int, 2> startingPoint{13, 37};
    std::array<int, 2> destinationPoint{24, 17};
    auto pathFindingResult = aStarSearch(startingPoint, destinationPoint, gridRow, gridCol, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 232;
    int expected_numOfCellCheckingOccurrence = 494;
    int expected_shortestDistance = 31;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(shortestDistance, expected_shortestDistance);
}

TEST_F(AStarTest, Test04)
{
    std::array<int, 2> startingPoint{30, 43};
    std::array<int, 2> destinationPoint{10, 24};
    auto pathFindingResult = aStarSearch(startingPoint, destinationPoint, gridRow, gridCol, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 40;
    int expected_numOfCellCheckingOccurrence = 118;
    int expected_shortestDistance = 39;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(shortestDistance, expected_shortestDistance);
}

TEST_F(AStarTest, ObstacleTest)
{
    std::array<int, 2> startingPoint{14, 13};
    std::array<int, 2> destinationPoint{8, 37};
    // set obstacles
    int rowTopLeft = 6;
    int colTopLeft = 20;
    int rowBottomRight = 23;
    int colBottomRight = 29;
    for (int j = rowTopLeft; j <= rowBottomRight; j++)
    {
        for (int k = colTopLeft; k <= colBottomRight; k++)
        {
            app->mainFrame->m_lp->grid->SetCellBackgroundColour(j, k, wxColour(0, 0, 0)); // black
        }
    }

    auto pathFindingResult = aStarSearch(startingPoint, destinationPoint, gridRow, gridCol, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 145;
    int expected_numOfCellCheckingOccurrence = 307;
    int expected_shortestDistance = 36;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(shortestDistance, expected_shortestDistance);
}

TEST_F(AStarTest, UnreachableTest)
{
    std::array<int, 2> startingPoint{2, 2};
    std::array<int, 2> destinationPoint{2, 10};
    // set obstacles
    int rowTopLeft = 0;
    int colTopLeft = 4;
    int rowBottomRight = 39;
    int colBottomRight = 6;
    for (int j = rowTopLeft; j <= rowBottomRight; j++)
    {
        for (int k = colTopLeft; k <= colBottomRight; k++)
        {
            app->mainFrame->m_lp->grid->SetCellBackgroundColour(j, k, wxColour(0, 0, 0)); // black
        }
    }

    auto pathFindingResult = aStarSearch(startingPoint, destinationPoint, gridRow, gridCol, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 160;
    int expected_numOfCellCheckingOccurrence = 276;
    int expected_shortestDistance = INT_MAX;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(shortestDistance, expected_shortestDistance);
}

class GreedyBestFirstTest : public testing::Test
{
protected:
    TestApp *app;
    virtual void SetUp()
    {
        char appname[] = "GreedyBestFirstTest.exe";
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

TEST_F(GreedyBestFirstTest, Test01)
{
    std::array<int, 2> startingPoint{13, 12};
    std::array<int, 2> destinationPoint{5, 30};
    auto pathFindingResult = greedyBestFirstSearch(startingPoint, destinationPoint, gridRow, gridCol, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 27;
    int expected_numOfCellCheckingOccurrence = 79;
    int expected_shortestDistance = 26;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(shortestDistance, expected_shortestDistance);
}

TEST_F(GreedyBestFirstTest, Test02)
{
    std::array<int, 2> startingPoint{15, 19};
    std::array<int, 2> destinationPoint{28, 36};
    auto pathFindingResult = greedyBestFirstSearch(startingPoint, destinationPoint, gridRow, gridCol, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 31;
    int expected_numOfCellCheckingOccurrence = 91;
    int expected_shortestDistance = 30;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(shortestDistance, expected_shortestDistance);
}

TEST_F(GreedyBestFirstTest, ObstacleTest)
{
    std::array<int, 2> startingPoint{14, 13};
    std::array<int, 2> destinationPoint{8, 37};
    // set obstacles
    int rowTopLeft = 0;
    int colTopLeft = 20;
    int rowBottomRight = 12;
    int colBottomRight = 29;
    for (int j = rowTopLeft; j <= rowBottomRight; j++)
    {
        for (int k = colTopLeft; k <= colBottomRight; k++)
        {
            app->mainFrame->m_lp->grid->SetCellBackgroundColour(j, k, wxColour(0, 0, 0)); // black
        }
    }

    auto pathFindingResult = greedyBestFirstSearch(startingPoint, destinationPoint, gridRow, gridCol, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 66;
    int expected_numOfCellCheckingOccurrence = 151;
    int expected_shortestDistance = 40;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(shortestDistance, expected_shortestDistance);
}

TEST_F(GreedyBestFirstTest, UnreachableTest)
{
    std::array<int, 2> startingPoint{2, 2};
    std::array<int, 2> destinationPoint{2, 10};
    // set obstacles
    int rowTopLeft = 0;
    int colTopLeft = 4;
    int rowBottomRight = 39;
    int colBottomRight = 6;
    for (int j = rowTopLeft; j <= rowBottomRight; j++)
    {
        for (int k = colTopLeft; k <= colBottomRight; k++)
        {
            app->mainFrame->m_lp->grid->SetCellBackgroundColour(j, k, wxColour(0, 0, 0)); // black
        }
    }

    auto pathFindingResult = greedyBestFirstSearch(startingPoint, destinationPoint, gridRow, gridCol, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 160;
    int expected_numOfCellCheckingOccurrence = 276;
    int expected_shortestDistance = INT_MAX;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(shortestDistance, expected_shortestDistance);
}

class BFSTest : public testing::Test
{
protected:
    TestApp *app;
    virtual void SetUp()
    {
        char appname[] = "BFSTest.exe";
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

TEST_F(BFSTest, Test02)
{
    std::array<int, 2> startingPoint{12, 19};
    std::array<int, 2> destinationPoint{20, 24};
    auto pathFindingResult = bfs(startingPoint, destinationPoint, gridRow, gridCol, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 348;
    int expected_numOfCellCheckingOccurrence = 742;
    int expected_shortestDistance = 13;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(shortestDistance, expected_shortestDistance);
}

TEST_F(BFSTest, ObstacleTest)
{
    std::array<int, 2> startingPoint{14, 13};
    std::array<int, 2> destinationPoint{8, 37};
    // set obstacles
    int rowTopLeft = 0;
    int colTopLeft = 20;
    int rowBottomRight = 12;
    int colBottomRight = 29;
    for (int j = rowTopLeft; j <= rowBottomRight; j++)
    {
        for (int k = colTopLeft; k <= colBottomRight; k++)
        {
            app->mainFrame->m_lp->grid->SetCellBackgroundColour(j, k, wxColour(0, 0, 0)); // black
        }
    }

    auto pathFindingResult = bfs(startingPoint, destinationPoint, gridRow, gridCol, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 1124;
    int expected_numOfCellCheckingOccurrence = 2246;
    int expected_shortestDistance = 30;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(shortestDistance, expected_shortestDistance);
}

TEST_F(BFSTest, UnreachableTest)
{
    std::array<int, 2> startingPoint{2, 2};
    std::array<int, 2> destinationPoint{2, 10};
    // set obstacles
    int rowTopLeft = 0;
    int colTopLeft = 4;
    int rowBottomRight = 39;
    int colBottomRight = 6;
    for (int j = rowTopLeft; j <= rowBottomRight; j++)
    {
        for (int k = colTopLeft; k <= colBottomRight; k++)
        {
            app->mainFrame->m_lp->grid->SetCellBackgroundColour(j, k, wxColour(0, 0, 0)); // black
        }
    }

    auto pathFindingResult = bfs(startingPoint, destinationPoint, gridRow, gridCol, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 160;
    int expected_numOfCellCheckingOccurrence = 276;
    int expected_shortestDistance = INT_MAX;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(shortestDistance, expected_shortestDistance);
}

class BiBFSTest : public testing::Test
{
protected:
    TestApp *app;
    virtual void SetUp()
    {
        char appname[] = "BiBFSTest.exe";
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

TEST_F(BiBFSTest, ObstacleTest)
{
    std::array<int, 2> startingPoint{14, 13};
    std::array<int, 2> destinationPoint{8, 37};
    // set obstacles
    int rowTopLeft = 0;
    int colTopLeft = 20;
    int rowBottomRight = 12;
    int colBottomRight = 29;
    for (int j = rowTopLeft; j <= rowBottomRight; j++)
    {
        for (int k = colTopLeft; k <= colBottomRight; k++)
        {
            app->mainFrame->m_lp->grid->SetCellBackgroundColour(j, k, wxColour(0, 0, 0)); // black
        }
    }

    auto pathFindingResult = bidirectionalBFS(startingPoint, destinationPoint, gridRow, gridCol, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 733;
    int expected_numOfCellCheckingOccurrence = 1524;
    int expected_shortestDistance = 30;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(shortestDistance, expected_shortestDistance);
}

TEST_F(BiBFSTest, UnreachableTest)
{
    std::array<int, 2> startingPoint{2, 2};
    std::array<int, 2> destinationPoint{2, 10};
    // set obstacles
    int rowTopLeft = 0;
    int colTopLeft = 4;
    int rowBottomRight = 39;
    int colBottomRight = 6;
    for (int j = rowTopLeft; j <= rowBottomRight; j++)
    {
        for (int k = colTopLeft; k <= colBottomRight; k++)
        {
            app->mainFrame->m_lp->grid->SetCellBackgroundColour(j, k, wxColour(0, 0, 0)); // black
        }
    }

    auto pathFindingResult = bidirectionalBFS(startingPoint, destinationPoint, gridRow, gridCol, app->mainFrame);
    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int shortestDistance = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int expected_numOfCellsVisited = 165;
    int expected_numOfCellCheckingOccurrence = 292;
    int expected_shortestDistance = INT_MAX;
    
    EXPECT_EQ(numOfCellsVisited, expected_numOfCellsVisited);
    EXPECT_EQ(numOfCellCheckingOccurrence, expected_numOfCellCheckingOccurrence);
    EXPECT_EQ(shortestDistance, expected_shortestDistance);
}